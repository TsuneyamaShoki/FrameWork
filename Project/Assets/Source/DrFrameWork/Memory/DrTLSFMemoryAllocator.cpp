
#include <assert.h>
#include "DrTLSFMemoryAllocator.h"


#pragma region //! DrBoundaryTagBrock

//! コンストラクタ
DrBoundaryTagBlock::DrBoundaryTagBlock() :
m_isOccupied(false), m_size(0), m_pointer(nullptr), m_endTagPointer(nullptr)
{
	m_prev = m_next = this;
}
DrBoundaryTagBlock::DrBoundaryTagBlock(DrByte* p, DrUint size) :
m_isOccupied(false), m_pointer(p)
{
	m_prev = m_next = this;
	m_size = size;
	if (m_pointer != nullptr)
	{
		//! endTagPointerは、pからsize分後方にある終端タグを指す。
		m_endTagPointer = (DrUint*)(p + size);
		*m_endTagPointer = sizeof(DrBoundaryTagBlock)+size + sizeof(DrUint);
	}
	else
		m_endTagPointer = nullptr;
}

//! 双方向リストへ入れる
DrBoundaryTagBlock* DrBoundaryTagBlock::Regist(DrBoundaryTagBlock* nbp)
{
	nbp->m_next = m_next;
	nbp->m_prev = this;
	nbp->m_prev->m_next = nbp->m_next->m_prev = nbp;
	return this;
}
//! 双方向リストを抜ける
DrBoundaryTagBlock* DrBoundaryTagBlock::Remove()
{
	m_prev->m_next = m_next;
	m_next->m_prev = m_prev;
	m_prev = m_next = this;
	return this;
}

//! Getter
DrUint DrBoundaryTagBlock::GetAllSize()
{
	return *m_endTagPointer;
}
DrUint DrBoundaryTagBlock::GetDataSize()
{
	return m_size;
}

#pragma endregion

#pragma region //! DrTLSFMemoryAllocator

//! 初期化
void DrTLSFMemoryAllocator::Init(DrUint allMemSize, DrUint maxExpectDivideNum/*=-1*/)
{
	//! 総分割数
	m_divideNum = maxExpectDivideNum;
	if (m_divideNum == -1)
		m_divideNum = allMemSize / pow(2, m_divisionCategoryNo);

	//! 運用総メモリ
	//! 指定量を抑えるベキ乗数で固定(allMemSize<=allSize=2^k)
	int k = GetMSB(allMemSize - 1) + 1;
	m_operationSize = pow(2, k);

	//! 定数設定
	m_bns = sizeof(DrBBlock)+sizeof(DrUint);
	m_bbs = sizeof(DrBBlock);

	//! 総確保メモリ=運用総メモリ+管理タグ分*予想最大分割数分+初期状態の管理タグ分
	m_allocatorSize = m_operationSize + m_bns*maxExpectDivideNum + m_bns * 3;

	//! メモリ確保
	m_leadPointer = new DrByte[m_allocatorSize];
	memset(m_leadPointer, 0, m_allocatorSize);

	//! 初期チャンクのFLIとSLI
	DrByte fli = GetMSB(m_allocatorSize - 1);
	DrByte sli = GetSLI(m_allocatorSize - 1, fli);

	//! ブロックリスト数
	DrByte bNum = fli*pow(2, m_divisionCategoryNo) + sli;

	//! ブロックリスト確保
	m_freeList = new DrBBlock[bNum];
	m_activeList = new DrBBlock[bNum];

	//! ブロックリストビット確保
	m_freeListBitFLI = 0;				//フリーリストビット(第一カテゴリ)初期化
	m_freeListBitSLI = new DrByte[fli + 1];	//フリーリストビット(第二カテゴリ)初期化
	m_freeListBit = new bool[bNum];		//フリーリストビット
	m_activeListBit = new bool[bNum];	//アクティブリストビット
	memset(m_freeListBitSLI, 0, sizeof(DrByte)*(fli + 1));
	memset(m_freeListBit, 0, sizeof(bool)*bNum);
	memset(m_activeListBit, 0, sizeof(bool)*bNum);

	//! 始めのダミー
	DrByte* b = m_leadPointer;
	DrBBlock* bbp = new(b)DrBBlock(b + m_bbs, 0);
	bbp->m_isOccupied = true;
	m_activeList[0].Regist(bbp);
	m_activeListBit[0] = true;

	//! 終末のダミー
	bbp = new(b + m_allocatorSize - m_bns) DrBBlock(b + m_allocatorSize - m_bns + m_bbs, 0);
	bbp->m_isOccupied = true;
	m_activeList[0].Regist(bbp);
	m_activeListBit[0] = true;

	//! 始めはフリーリストに一つだけ大きなブロックがある
	bbp = new(m_leadPointer + m_bns) DrBBlock(m_leadPointer + m_bns + m_bbs, m_allocatorSize - m_bns * 3);
	bbp->m_isOccupied = false;
	m_freeList[bNum - 1].Regist(bbp);
	//! フリーリストビットを立てる
	m_freeListBit[bNum - 1] = true;
	//! (第一カテゴリ)(第二カテゴリ)の最初のフリーリストビットを立てる
	m_freeListBitFLI = (1 << fli);
	m_freeListBitSLI[fli] = (1 << sli);
}

//! メモリ解放
void DrTLSFMemoryAllocator::ReleaseMemory(DrByte* p)
{
	//! 前方・自身・後方のブロック
	DrBBlock *b0, *b1, *b2;
	//! 前方・自身・後方のデータポインタ
	DrByte *p0, *p1, *p2;
	//! 前方・自身・後方の終末ポインタ
	DrUint *c0, *c1, *c2;

	//! 自身の設定
	p1 = (DrByte*)p;
	b1 = (DrBBlock*)(p1 - m_bbs);
	c1 = (DrUint*)b1->m_endTagPointer;

	//! 前方の設定
	c0 = (DrUint*)((DrByte*)b1 - sizeof(DrUint));
	b0 = (DrBBlock*)((DrByte*)b1 - (*c0));
	p0 = b0->m_pointer;

	//! 後方の設定
	b2 = (DrBBlock*)((DrByte*)b1 + b1->GetAllSize());
	p2 = (DrByte*)b2->m_pointer;
	c2 = (DrUint*)b2->m_endTagPointer;

	//! ポインタの正当性をチェック
	assert(m_leadPointer <= (DrByte*)b0 && (DrByte*)b0 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)p0 && (DrByte*)p0 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)c0 && (DrByte*)c0 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)b1 && (DrByte*)b1 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)p1 && (DrByte*)p1 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)c1 && (DrByte*)c1 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)b2 && (DrByte*)b2 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)p2 && (DrByte*)p2 <= m_leadPointer + m_allocatorSize);
	assert(m_leadPointer <= (DrByte*)c2 && (DrByte*)c2 <= m_leadPointer + m_allocatorSize);
	assert((DrByte*)b0 <= p0 && p0 <= (DrByte*)c0);
	assert((DrByte*)b1 <= p1 && p1 <= (DrByte*)c1);
	assert((DrByte*)b2 <= p2 && p2 <= (DrByte*)c2);
	assert((DrByte*)c0 <= (DrByte*)b1);
	assert((DrByte*)c1 <= (DrByte*)b2);

	//! b1をアクティブリストから外す
	DrUint aIndex = GetFIndex(b1->GetAllSize());
	b1->Remove();
	//アクティブリストが無かったらビットをfalseに
	if (m_activeList[aIndex].m_next == &m_activeList[aIndex])
		m_activeListBit[aIndex] = false;

	//左マージ
	if (b0->m_isOccupied == false)
	{
		//b0をフリーリストから外す
		DrByte fli = GetMSB(b0->GetAllSize() - 1);
		DrByte sli = GetSLI(b0->GetAllSize() - 1, fli);
		DrUint fIndex = GetFIndex(b0->GetAllSize());
		b0->Remove();
		//フリーリストが無かったらビットをfalseに
		if (m_freeList[fIndex].m_next == &m_freeList[fIndex])
		{
			//フリーリストビット
			m_freeListBit[fIndex] = false;
			//フリーリストビット(第二カテゴリ)
			m_freeListBitSLI[fli] &= ~(1 << sli);
			//フリーリストビット(第一カテゴリ)
			if (m_freeListBitSLI[fli] == 0)
				m_freeListBitFLI &= ~(1 << fli);
		}

		//b0の設定
		b0->m_size += b1->GetAllSize();
		b0->m_endTagPointer = b1->m_endTagPointer;
		*(b0->m_endTagPointer) = b0->m_size + m_bns;

		//以後b0をb1として扱う
		b1 = b0;
	}
	//右マージ
	if (b2->m_isOccupied == false)
	{
		//b2をフリーリストから外す
		DrByte fli = GetMSB(b2->GetAllSize() - 1);
		DrByte sli = GetSLI(b2->GetAllSize() - 1, fli);
		DrUint fIndex = GetFIndex(b2->GetAllSize());
		b2->Remove();
		//フリーリストが無かったらビットをfalseに		
		if (m_freeList[fIndex].m_next == &m_freeList[fIndex])
		{
			//フリーリストビット
			m_freeListBit[fIndex] = false;
			//フリーリストビット(第二カテゴリ)
			m_freeListBitSLI[fli] &= ~(1 << sli);
			//フリーリストビット(第一カテゴリ)
			if (m_freeListBitSLI[fli] == 0)
				m_freeListBitFLI &= ~(1 << fli);
		}

		//b1の設定
		b1->m_size += b2->GetAllSize();
		b1->m_endTagPointer = b2->m_endTagPointer;
		*(b1->m_endTagPointer) = b1->m_size + m_bns;

		//以後b2は扱えない
	}

	//b1を適切なフリーリストへ入れる
	DrByte fli = GetMSB(b1->GetDataSize() - 1);
	DrByte sli = GetSLI(b1->GetDataSize() - 1, fli);
	DrUint fIndex = GetFIndex(b1->GetDataSize());
	m_freeList[fIndex].Regist(b1);
	m_freeListBit[fIndex] = true;
	//フリーリストビット(第二カテゴリ)
	m_freeListBitSLI[fli] |= (1 << sli);
	//フリーリストビット(第一カテゴリ)
	m_freeListBitFLI |= (1 << fli);

	//b1の設定
	b1->m_isOccupied = false;

	//残骸処理0クリア
	memset(b1->m_pointer, 0, b1->GetDataSize());
}

//! 確保しているメモリを全削除する。デストラクタは呼ばれない。
void DrTLSFMemoryAllocator::Clear()
{
	//!すべてのメモリを開放
	memset(m_leadPointer, 0, m_operationSize);
	DrSafeDeleteArray(m_leadPointer);
	DrSafeDeleteArray(m_freeList);
	DrSafeDeleteArray(m_activeList);
	DrSafeDeleteArray(m_freeListBitSLI);
	DrSafeDeleteArray(m_freeListBit);
	DrSafeDeleteArray(m_activeListBit);
	//!再初期化
	Init(m_operationSize, m_divideNum);
}

//! デストラクタ
DrTLSFMemoryAllocator::~DrTLSFMemoryAllocator()
{
	Clear();
	memset(m_leadPointer, 0, m_operationSize);
	DrSafeDeleteArray(m_leadPointer);
	DrSafeDeleteArray(m_freeList);
	DrSafeDeleteArray(m_activeList);
	DrSafeDeleteArray(m_freeListBitSLI);
	DrSafeDeleteArray(m_freeListBit);
	DrSafeDeleteArray(m_activeListBit);
}

//! メモリ切り出し
DrByte* DrTLSFMemoryAllocator::DivideMemory(DrUint size)
{
	//! 最大のサイズのFLI(これを越えてはいけない)
	DrInt mFLI = GetMSB(m_allocatorSize - 1);

	//! 確保サイズのfIndex
	DrByte fIndex = 0;
	DrUint fli = GetMSB(size + m_bns - 1);
	DrUint sli = GetSLI(size + m_bns - 1, fli);
	assert(0 < fli && fli <= mFLI);
	assert(0 <= sli && sli < pow(2, m_divisionCategoryNo));

	//フリーリストから一つ取り出す
	//所属フリーリスト内にある確保サイズより大きなブロックを探す
	fIndex = GetFIndex(fli, sli);
	if (!m_freeListBit[fIndex])
	{
		//フリーリストがなければ上方へ探しにいく
		//まず同fli内で上方のフリーリストが存在するかを調べる
		sli = GetFreeListSLI(fli, sli);

		//上位sliが見つかったら
		if (0 <= sli && sli < pow(2, m_divisionCategoryNo))
			fIndex = GetFIndex(fli, sli);
		//同fli内に上位sliが見つからなかったら
		//上位fliに探しにいく
		else
		{
			DrByte nFLI = fli;
			fli = GetFreeListFLI(fli);
			sli = GetFreeListSLI(fli, 0);
			fIndex = GetFIndex(fli, sli);
		}
	}

	//fIndexチェック
	assert(0 < fli && fli <= mFLI);
	assert(0 <= sli && sli < pow(2, m_divisionCategoryNo));
	assert(m_freeListBit[fIndex]);
	assert(&m_freeList[fIndex] != m_freeList[fIndex].m_next);

	//元々(分割前)のメモリブロック
	DrBBlock* bbp = m_freeList[fIndex].m_next;
	//フリーリストのメモリの方が大きくなければならない
	assert(size + m_bns <= bbp->GetAllSize());

	//フリーリストから外す
	bbp->Remove();
	//フリーリストが無かったらビットをfalseに
	if (m_freeList[fIndex].m_next == &m_freeList[fIndex])
	{
		m_freeListBit[fIndex] = false;
		m_freeListBitSLI[fli] &= ~(1 << sli);
		if (m_freeListBitSLI[fli] == 0)
			m_freeListBitFLI &= ~(1 << fli);
	}

	//ジャスト時の挙動
	//フリーリストのメモリと同じサイズだったならば
	if (size + m_bns == bbp->GetAllSize())
	{
		//bbpを返す
		//アクティブリストへ追加
		m_activeList[fIndex].Regist(bbp);
		bbp->m_isOccupied = true;
		m_activeListBit[fIndex] = true;

		memset(bbp->m_pointer, 0, bbp->GetDataSize());

		return bbp->m_pointer;
	}

	//サイズ分割した後に少なくともタグ分は残らないと分割できない
	if (bbp->GetAllSize() - (size + m_bns) > m_bns){
		//分割([元々のメモリチャンク]->[残りの分割メモリbbp][新しく確保するsize分のメモリnbp])
		//分割メモリの展開位置
		DrByte* nbpPos = (DrByte*)bbp + bbp->GetAllSize() - size - m_bns;
		//分割メモリ展開
		DrBBlock* nbp = new(nbpPos)DrBBlock(nbpPos + m_bbs, size);

		//残りメモリの設定
		//分割元が分割先の分の全サイズを超えている
		assert(bbp->m_size >= nbp->GetDataSize() + m_bns);
		//サイズ設定
		bbp->m_size -= (nbp->GetDataSize() + m_bns);
		bbp->m_endTagPointer = (DrUint*)(bbp->m_pointer + bbp->m_size);
		*bbp->m_endTagPointer = m_bns + bbp->m_size;
		//分割元のサイズがマイナスでない(総確保メモリを超えない)
		assert(bbp->m_size < m_allocatorSize);

		//アクティブリストへ追加
		DrUint nIndex = GetFIndex(nbp->GetAllSize());
		m_activeList[nIndex].Regist(nbp);
		nbp->m_isOccupied = true;
		m_activeListBit[nIndex] = true;

		//フリーリストへ追加
		//fIndex=GetFIndex(bbp->GetAllSize());
		fli = GetMSB(bbp->GetAllSize() - 1);
		sli = GetSLI(bbp->GetAllSize() - 1, fli);
		fIndex = GetFIndex(fli, sli);
		assert(0 < fli && fli <= mFLI);
		assert(0 <= sli && sli < pow(2, m_divisionCategoryNo));
		//assert(0<fIndex && fIndex<=mFLI*pow(2,m_divisionCategoryNo));

		m_freeList[fIndex].Regist(bbp);
		bbp->m_isOccupied = false;
		m_freeListBit[fIndex] = true;
		//! フリーリストビット(第二カテゴリ)
		m_freeListBitSLI[fli] |= (1 << sli);
		//! フリーリストビット(第一カテゴリ)
		m_freeListBitFLI |= (1 << fli);

		//! 0クリアして返す
		memset(bbp->m_pointer, 0, bbp->GetDataSize());
		memset(nbp->m_pointer, 0, nbp->GetDataSize());

		return nbp->m_pointer;
	}
}

//! Getter
//! 2^x<=valueとなるxを返す(Most Significant Bit)
int DrTLSFMemoryAllocator::GetMSB(DrUint value)
{
	if (value == 0) return -1;
	value |= (value >> 1);
	value |= (value >> 2);
	value |= (value >> 4);
	value |= (value >> 8);
	value |= (value >> 16);
	return GetBitCount(value) - 1;
}
//2^x>=valueとなるxを返す(LSI)
int DrTLSFMemoryAllocator::GetLSB(DrUint value)
{
	if (value == 0) return false;
	value |= (value << 1);
	value |= (value << 2);
	value |= (value << 4);
	value |= (value << 8);
	value |= (value << 16);
	return 32 - GetBitCount(value);
}
//! 第二カテゴリーインデックス(SLI)を返す
DrByte DrTLSFMemoryAllocator::GetSLI(DrUint size, DrByte fli)
{
	// 最上位ビット未満のビット列だけを有効にするマスク
	DrUint mask = ~(0xffffffff << fli);
	// 右へのシフト数を算出
	DrUint rs = fli - m_divisionCategoryNo;
	// 引数sizeにマスクをかけて、右へシフトすればSLIに
	DrByte sli = (size & mask) >> rs;
	return sli;
}
//! 同fli内の上位sliを返す(第二カテゴリ内探索)
DrByte DrTLSFMemoryAllocator::GetFreeListSLI(DrByte fli, DrByte sli)
{
	//部分フリーリストバイト(fli内の4byte)
	DrByte rb = m_freeListBitSLI[fli];

	//sli以上が立っているマスク
	DrByte sb = 0xffffffff << sli;

	//部分フリーリストビットのsli以上に立っているビットがあるか
	DrByte rsb = rb & sb;
	if (rsb == 0){
		return -1;//同fli内に上位sliは無い
	}

	//同fli内の上位sliを返す
	return GetLSB(rsb);
}
//! 指定Fliより上位のFliを返す(第一カテゴリ内探索)
DrByte DrTLSFMemoryAllocator::GetFreeListFLI(DrByte fli)
{
	//fli以上が立っているマスク
	DrUint fb = 0xffffffff << fli;

	//全体フリーリストビットFLIのfli以上に立っているビットがあるか
	DrUint rfb = m_freeListBitFLI & fb;
	if (rfb == 0){
		return -1;//上位のFliが無い（エラー）
	}

	//上位fliを返す
	return GetLSB(rfb);
}
//! fli,sliからリストインデックスを求める
DrByte DrTLSFMemoryAllocator::GetFIndex(DrByte fli, DrByte sli)
{
	return fli*pow(2, m_divisionCategoryNo) + sli - 1;
}
//! Todo:あるサイズが所属しているリストインデックスを返す
DrByte DrTLSFMemoryAllocator::GetFIndex(DrUint size)
{
	return 0;
}
//! 立っているビット数をカウントする(32bit ulong)
int DrTLSFMemoryAllocator::GetBitCount(DrUint value)
{
	DrInt count = (value & 0x55555555) + ((value >> 1) & 0x55555555);
	count = (count & 0x33333333) + ((count >> 2) & 0x33333333);
	count = (count & 0x0f0f0f0f) + ((count >> 4) & 0x0f0f0f0f);
	count = (count & 0x00ff00ff) + ((count >> 8) & 0x00ff00ff);
	return (count & 0x0000ffff) + ((count >> 16) & 0x0000ffff);
}

#pragma endregion