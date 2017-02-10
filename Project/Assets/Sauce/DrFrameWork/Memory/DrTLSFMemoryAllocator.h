
#pragma once

//! Include
#include "../Utility/DrMainUtility.h"


#pragma region //! DrBoundaryTagBlock [typedef DrBBlock]

//! this[先頭]m_pointer[運用メモリ][終端]
//! [Class] DrBoundaryTagBrock
class DrBoundaryTagBlock
{
public:
	//! 使用中かどうかのフラグ
	DrBool m_isOccupied;
	//! データ部サイズ
	DrUint m_size;
	//! 先頭ポインタ
	DrByte* m_pointer;
	//! endTagへのポインタ
	DrUint* m_endTagPointer;

	//DrBoundaryTagBrockの双方向リスト
	DrBoundaryTagBlock *m_prev, *m_next;

	//! コンストラクタ
	DrBoundaryTagBlock();
	DrBoundaryTagBlock(DrByte* p,DrUint size);

	//! 双方向リストへ入れる。
	DrBoundaryTagBlock* Regist(DrBoundaryTagBlock* nbp);
	//! 双方向リストから抜ける。
	DrBoundaryTagBlock* Remove();

	//! 運用サイズを取得
	DrUint GetDataSize();
	//! 自身が占有する全てのデータサイズを取得
	DrUint GetAllSize();
};

typedef DrBoundaryTagBlock DrBBlock;

#pragma endregion

//! http://1st.geocities.jp/shift486909/program/MemoryAllocator3.html
//! http://marupeke296.com/ALG_No2_TLSFMemoryAllocator.html
//! [Class] DrTLSFMemoryAllocator
class DrTLSFMemoryAllocator
{
#pragma region //private:
private:
	static const DrInt m_divisionCategoryNo = 2;

	//! 運用総メモリ
	DrUint m_operationSize;

	//! 総確保メモリ
	DrUint m_allocatorSize;

	//! 総分割数
	DrUint m_divideNum;

	//! 確保メモリの先頭ポインタ
	DrByte* m_leadPointer;

	//! フリーリストブロック配列の先頭ポインタ
	DrBBlock* m_freeList;

	//! アクティブリストブロック配列先頭データ
	DrBBlock* m_activeList;

	//! フリーリストビット(第二カテゴリ)
	DrUint m_freeListBitFLI;
	//! フリーリストビット(第一カテゴリ)
	DrByte* m_freeListBitSLI;
	DrBool* m_freeListBit;
	DrBool* m_activeListBit;
	DrInt m_bns;	//! sizeof(DrBlock)+sizeof(uint)
	DrInt m_bbs;	//! sizeof(DrBlock)

	//! 初期化
	void Init(DrUint allMemSize, DrUint maxExpectDivideNum = 1);

	//メモリ切り出し
	DrByte* DivideMemory(DrUint size);

	//メモリ解放
	void ReleaseMemory(DrByte* p);

	//! Getter
	int GetMSB(DrUint value);						//! 2^x<=valueとなるxを返す(Most Significant Bit)
	int GetLSB(DrUint value);						//! 2^x>=valueとなるxを返す(LSI)
	DrByte GetSLI(DrUint size, DrByte fli);			//! 第二カテゴリーインデックス(SLI)を返す
	DrByte GetFreeListSLI(DrByte fli, DrByte sli);	//! 同fli内の上位sliを返す(第二カテゴリ内探索)
	DrByte GetFreeListFLI(DrByte fli);				//! 指定Fliより上位のFliを返す(第一カテゴリ内探索)
	DrByte GetFIndex(DrUint size);					//! あるサイズが所属しているリストインデックスを返す
	DrByte GetFIndex(DrByte fli, DrByte sli);		//! fli,sliからリストインデックスを求める
	int GetBitCount(DrUint value);					//! 立っているビット数をカウントする(32bit ulong)
#pragma endregion
protected:
public:
	//! メモリ取得
	template<class T> T* GetMemory(DrUint size = sizeof(T)) 
	{
		return (T*)DivideMemory(size);
	}

	//! メモリ解放
	template<class T> void DeleteMemory(T* p)
	{
		p->~T();
		ReleaseMemory((byte*)p);
	}

	//! メモリ全開放
	void Clear();

	DrTLSFMemoryAllocator();
	virtual ~DrTLSFMemoryAllocator();
};
