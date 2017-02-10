
#include <assert.h>
#include "DrTLSFMemoryAllocator.h"


#pragma region //! DrBoundaryTagBrock

//! �R���X�g���N�^
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
		//! endTagPointer�́Ap����size������ɂ���I�[�^�O���w���B
		m_endTagPointer = (DrUint*)(p + size);
		*m_endTagPointer = sizeof(DrBoundaryTagBlock)+size + sizeof(DrUint);
	}
	else
		m_endTagPointer = nullptr;
}

//! �o�������X�g�֓����
DrBoundaryTagBlock* DrBoundaryTagBlock::Regist(DrBoundaryTagBlock* nbp)
{
	nbp->m_next = m_next;
	nbp->m_prev = this;
	nbp->m_prev->m_next = nbp->m_next->m_prev = nbp;
	return this;
}
//! �o�������X�g�𔲂���
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

//! ������
void DrTLSFMemoryAllocator::Init(DrUint allMemSize, DrUint maxExpectDivideNum/*=-1*/)
{
	//! ��������
	m_divideNum = maxExpectDivideNum;
	if (m_divideNum == -1)
		m_divideNum = allMemSize / pow(2, m_divisionCategoryNo);

	//! �^�p��������
	//! �w��ʂ�}����x�L�搔�ŌŒ�(allMemSize<=allSize=2^k)
	int k = GetMSB(allMemSize - 1) + 1;
	m_operationSize = pow(2, k);

	//! �萔�ݒ�
	m_bns = sizeof(DrBBlock)+sizeof(DrUint);
	m_bbs = sizeof(DrBBlock);

	//! ���m�ۃ�����=�^�p��������+�Ǘ��^�O��*�\�z�ő啪������+������Ԃ̊Ǘ��^�O��
	m_allocatorSize = m_operationSize + m_bns*maxExpectDivideNum + m_bns * 3;

	//! �������m��
	m_leadPointer = new DrByte[m_allocatorSize];
	memset(m_leadPointer, 0, m_allocatorSize);

	//! �����`�����N��FLI��SLI
	DrByte fli = GetMSB(m_allocatorSize - 1);
	DrByte sli = GetSLI(m_allocatorSize - 1, fli);

	//! �u���b�N���X�g��
	DrByte bNum = fli*pow(2, m_divisionCategoryNo) + sli;

	//! �u���b�N���X�g�m��
	m_freeList = new DrBBlock[bNum];
	m_activeList = new DrBBlock[bNum];

	//! �u���b�N���X�g�r�b�g�m��
	m_freeListBitFLI = 0;				//�t���[���X�g�r�b�g(���J�e�S��)������
	m_freeListBitSLI = new DrByte[fli + 1];	//�t���[���X�g�r�b�g(���J�e�S��)������
	m_freeListBit = new bool[bNum];		//�t���[���X�g�r�b�g
	m_activeListBit = new bool[bNum];	//�A�N�e�B�u���X�g�r�b�g
	memset(m_freeListBitSLI, 0, sizeof(DrByte)*(fli + 1));
	memset(m_freeListBit, 0, sizeof(bool)*bNum);
	memset(m_activeListBit, 0, sizeof(bool)*bNum);

	//! �n�߂̃_�~�[
	DrByte* b = m_leadPointer;
	DrBBlock* bbp = new(b)DrBBlock(b + m_bbs, 0);
	bbp->m_isOccupied = true;
	m_activeList[0].Regist(bbp);
	m_activeListBit[0] = true;

	//! �I���̃_�~�[
	bbp = new(b + m_allocatorSize - m_bns) DrBBlock(b + m_allocatorSize - m_bns + m_bbs, 0);
	bbp->m_isOccupied = true;
	m_activeList[0].Regist(bbp);
	m_activeListBit[0] = true;

	//! �n�߂̓t���[���X�g�Ɉ�����傫�ȃu���b�N������
	bbp = new(m_leadPointer + m_bns) DrBBlock(m_leadPointer + m_bns + m_bbs, m_allocatorSize - m_bns * 3);
	bbp->m_isOccupied = false;
	m_freeList[bNum - 1].Regist(bbp);
	//! �t���[���X�g�r�b�g�𗧂Ă�
	m_freeListBit[bNum - 1] = true;
	//! (���J�e�S��)(���J�e�S��)�̍ŏ��̃t���[���X�g�r�b�g�𗧂Ă�
	m_freeListBitFLI = (1 << fli);
	m_freeListBitSLI[fli] = (1 << sli);
}

//! ���������
void DrTLSFMemoryAllocator::ReleaseMemory(DrByte* p)
{
	//! �O���E���g�E����̃u���b�N
	DrBBlock *b0, *b1, *b2;
	//! �O���E���g�E����̃f�[�^�|�C���^
	DrByte *p0, *p1, *p2;
	//! �O���E���g�E����̏I���|�C���^
	DrUint *c0, *c1, *c2;

	//! ���g�̐ݒ�
	p1 = (DrByte*)p;
	b1 = (DrBBlock*)(p1 - m_bbs);
	c1 = (DrUint*)b1->m_endTagPointer;

	//! �O���̐ݒ�
	c0 = (DrUint*)((DrByte*)b1 - sizeof(DrUint));
	b0 = (DrBBlock*)((DrByte*)b1 - (*c0));
	p0 = b0->m_pointer;

	//! ����̐ݒ�
	b2 = (DrBBlock*)((DrByte*)b1 + b1->GetAllSize());
	p2 = (DrByte*)b2->m_pointer;
	c2 = (DrUint*)b2->m_endTagPointer;

	//! �|�C���^�̐��������`�F�b�N
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

	//! b1���A�N�e�B�u���X�g����O��
	DrUint aIndex = GetFIndex(b1->GetAllSize());
	b1->Remove();
	//�A�N�e�B�u���X�g������������r�b�g��false��
	if (m_activeList[aIndex].m_next == &m_activeList[aIndex])
		m_activeListBit[aIndex] = false;

	//���}�[�W
	if (b0->m_isOccupied == false)
	{
		//b0���t���[���X�g����O��
		DrByte fli = GetMSB(b0->GetAllSize() - 1);
		DrByte sli = GetSLI(b0->GetAllSize() - 1, fli);
		DrUint fIndex = GetFIndex(b0->GetAllSize());
		b0->Remove();
		//�t���[���X�g������������r�b�g��false��
		if (m_freeList[fIndex].m_next == &m_freeList[fIndex])
		{
			//�t���[���X�g�r�b�g
			m_freeListBit[fIndex] = false;
			//�t���[���X�g�r�b�g(���J�e�S��)
			m_freeListBitSLI[fli] &= ~(1 << sli);
			//�t���[���X�g�r�b�g(���J�e�S��)
			if (m_freeListBitSLI[fli] == 0)
				m_freeListBitFLI &= ~(1 << fli);
		}

		//b0�̐ݒ�
		b0->m_size += b1->GetAllSize();
		b0->m_endTagPointer = b1->m_endTagPointer;
		*(b0->m_endTagPointer) = b0->m_size + m_bns;

		//�Ȍ�b0��b1�Ƃ��Ĉ���
		b1 = b0;
	}
	//�E�}�[�W
	if (b2->m_isOccupied == false)
	{
		//b2���t���[���X�g����O��
		DrByte fli = GetMSB(b2->GetAllSize() - 1);
		DrByte sli = GetSLI(b2->GetAllSize() - 1, fli);
		DrUint fIndex = GetFIndex(b2->GetAllSize());
		b2->Remove();
		//�t���[���X�g������������r�b�g��false��		
		if (m_freeList[fIndex].m_next == &m_freeList[fIndex])
		{
			//�t���[���X�g�r�b�g
			m_freeListBit[fIndex] = false;
			//�t���[���X�g�r�b�g(���J�e�S��)
			m_freeListBitSLI[fli] &= ~(1 << sli);
			//�t���[���X�g�r�b�g(���J�e�S��)
			if (m_freeListBitSLI[fli] == 0)
				m_freeListBitFLI &= ~(1 << fli);
		}

		//b1�̐ݒ�
		b1->m_size += b2->GetAllSize();
		b1->m_endTagPointer = b2->m_endTagPointer;
		*(b1->m_endTagPointer) = b1->m_size + m_bns;

		//�Ȍ�b2�͈����Ȃ�
	}

	//b1��K�؂ȃt���[���X�g�֓����
	DrByte fli = GetMSB(b1->GetDataSize() - 1);
	DrByte sli = GetSLI(b1->GetDataSize() - 1, fli);
	DrUint fIndex = GetFIndex(b1->GetDataSize());
	m_freeList[fIndex].Regist(b1);
	m_freeListBit[fIndex] = true;
	//�t���[���X�g�r�b�g(���J�e�S��)
	m_freeListBitSLI[fli] |= (1 << sli);
	//�t���[���X�g�r�b�g(���J�e�S��)
	m_freeListBitFLI |= (1 << fli);

	//b1�̐ݒ�
	b1->m_isOccupied = false;

	//�c�[����0�N���A
	memset(b1->m_pointer, 0, b1->GetDataSize());
}

//! �m�ۂ��Ă��郁������S�폜����B�f�X�g���N�^�͌Ă΂�Ȃ��B
void DrTLSFMemoryAllocator::Clear()
{
	//!���ׂẴ��������J��
	memset(m_leadPointer, 0, m_operationSize);
	DrSafeDeleteArray(m_leadPointer);
	DrSafeDeleteArray(m_freeList);
	DrSafeDeleteArray(m_activeList);
	DrSafeDeleteArray(m_freeListBitSLI);
	DrSafeDeleteArray(m_freeListBit);
	DrSafeDeleteArray(m_activeListBit);
	//!�ď�����
	Init(m_operationSize, m_divideNum);
}

//! �f�X�g���N�^
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

//! �������؂�o��
DrByte* DrTLSFMemoryAllocator::DivideMemory(DrUint size)
{
	//! �ő�̃T�C�Y��FLI(������z���Ă͂����Ȃ�)
	DrInt mFLI = GetMSB(m_allocatorSize - 1);

	//! �m�ۃT�C�Y��fIndex
	DrByte fIndex = 0;
	DrUint fli = GetMSB(size + m_bns - 1);
	DrUint sli = GetSLI(size + m_bns - 1, fli);
	assert(0 < fli && fli <= mFLI);
	assert(0 <= sli && sli < pow(2, m_divisionCategoryNo));

	//�t���[���X�g�������o��
	//�����t���[���X�g���ɂ���m�ۃT�C�Y���傫�ȃu���b�N��T��
	fIndex = GetFIndex(fli, sli);
	if (!m_freeListBit[fIndex])
	{
		//�t���[���X�g���Ȃ���Ώ���֒T���ɂ���
		//�܂���fli���ŏ���̃t���[���X�g�����݂��邩�𒲂ׂ�
		sli = GetFreeListSLI(fli, sli);

		//���sli������������
		if (0 <= sli && sli < pow(2, m_divisionCategoryNo))
			fIndex = GetFIndex(fli, sli);
		//��fli���ɏ��sli��������Ȃ�������
		//���fli�ɒT���ɂ���
		else
		{
			DrByte nFLI = fli;
			fli = GetFreeListFLI(fli);
			sli = GetFreeListSLI(fli, 0);
			fIndex = GetFIndex(fli, sli);
		}
	}

	//fIndex�`�F�b�N
	assert(0 < fli && fli <= mFLI);
	assert(0 <= sli && sli < pow(2, m_divisionCategoryNo));
	assert(m_freeListBit[fIndex]);
	assert(&m_freeList[fIndex] != m_freeList[fIndex].m_next);

	//���X(�����O)�̃������u���b�N
	DrBBlock* bbp = m_freeList[fIndex].m_next;
	//�t���[���X�g�̃������̕����傫���Ȃ���΂Ȃ�Ȃ�
	assert(size + m_bns <= bbp->GetAllSize());

	//�t���[���X�g����O��
	bbp->Remove();
	//�t���[���X�g������������r�b�g��false��
	if (m_freeList[fIndex].m_next == &m_freeList[fIndex])
	{
		m_freeListBit[fIndex] = false;
		m_freeListBitSLI[fli] &= ~(1 << sli);
		if (m_freeListBitSLI[fli] == 0)
			m_freeListBitFLI &= ~(1 << fli);
	}

	//�W���X�g���̋���
	//�t���[���X�g�̃������Ɠ����T�C�Y�������Ȃ��
	if (size + m_bns == bbp->GetAllSize())
	{
		//bbp��Ԃ�
		//�A�N�e�B�u���X�g�֒ǉ�
		m_activeList[fIndex].Regist(bbp);
		bbp->m_isOccupied = true;
		m_activeListBit[fIndex] = true;

		memset(bbp->m_pointer, 0, bbp->GetDataSize());

		return bbp->m_pointer;
	}

	//�T�C�Y����������ɏ��Ȃ��Ƃ��^�O���͎c��Ȃ��ƕ����ł��Ȃ�
	if (bbp->GetAllSize() - (size + m_bns) > m_bns){
		//����([���X�̃������`�����N]->[�c��̕���������bbp][�V�����m�ۂ���size���̃�����nbp])
		//�����������̓W�J�ʒu
		DrByte* nbpPos = (DrByte*)bbp + bbp->GetAllSize() - size - m_bns;
		//�����������W�J
		DrBBlock* nbp = new(nbpPos)DrBBlock(nbpPos + m_bbs, size);

		//�c�胁�����̐ݒ�
		//��������������̕��̑S�T�C�Y�𒴂��Ă���
		assert(bbp->m_size >= nbp->GetDataSize() + m_bns);
		//�T�C�Y�ݒ�
		bbp->m_size -= (nbp->GetDataSize() + m_bns);
		bbp->m_endTagPointer = (DrUint*)(bbp->m_pointer + bbp->m_size);
		*bbp->m_endTagPointer = m_bns + bbp->m_size;
		//�������̃T�C�Y���}�C�i�X�łȂ�(���m�ۃ������𒴂��Ȃ�)
		assert(bbp->m_size < m_allocatorSize);

		//�A�N�e�B�u���X�g�֒ǉ�
		DrUint nIndex = GetFIndex(nbp->GetAllSize());
		m_activeList[nIndex].Regist(nbp);
		nbp->m_isOccupied = true;
		m_activeListBit[nIndex] = true;

		//�t���[���X�g�֒ǉ�
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
		//! �t���[���X�g�r�b�g(���J�e�S��)
		m_freeListBitSLI[fli] |= (1 << sli);
		//! �t���[���X�g�r�b�g(���J�e�S��)
		m_freeListBitFLI |= (1 << fli);

		//! 0�N���A���ĕԂ�
		memset(bbp->m_pointer, 0, bbp->GetDataSize());
		memset(nbp->m_pointer, 0, nbp->GetDataSize());

		return nbp->m_pointer;
	}
}

//! Getter
//! 2^x<=value�ƂȂ�x��Ԃ�(Most Significant Bit)
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
//2^x>=value�ƂȂ�x��Ԃ�(LSI)
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
//! ���J�e�S���[�C���f�b�N�X(SLI)��Ԃ�
DrByte DrTLSFMemoryAllocator::GetSLI(DrUint size, DrByte fli)
{
	// �ŏ�ʃr�b�g�����̃r�b�g�񂾂���L���ɂ���}�X�N
	DrUint mask = ~(0xffffffff << fli);
	// �E�ւ̃V�t�g�����Z�o
	DrUint rs = fli - m_divisionCategoryNo;
	// ����size�Ƀ}�X�N�������āA�E�փV�t�g�����SLI��
	DrByte sli = (size & mask) >> rs;
	return sli;
}
//! ��fli���̏��sli��Ԃ�(���J�e�S�����T��)
DrByte DrTLSFMemoryAllocator::GetFreeListSLI(DrByte fli, DrByte sli)
{
	//�����t���[���X�g�o�C�g(fli����4byte)
	DrByte rb = m_freeListBitSLI[fli];

	//sli�ȏオ�����Ă���}�X�N
	DrByte sb = 0xffffffff << sli;

	//�����t���[���X�g�r�b�g��sli�ȏ�ɗ����Ă���r�b�g�����邩
	DrByte rsb = rb & sb;
	if (rsb == 0){
		return -1;//��fli���ɏ��sli�͖���
	}

	//��fli���̏��sli��Ԃ�
	return GetLSB(rsb);
}
//! �w��Fli����ʂ�Fli��Ԃ�(���J�e�S�����T��)
DrByte DrTLSFMemoryAllocator::GetFreeListFLI(DrByte fli)
{
	//fli�ȏオ�����Ă���}�X�N
	DrUint fb = 0xffffffff << fli;

	//�S�̃t���[���X�g�r�b�gFLI��fli�ȏ�ɗ����Ă���r�b�g�����邩
	DrUint rfb = m_freeListBitFLI & fb;
	if (rfb == 0){
		return -1;//��ʂ�Fli�������i�G���[�j
	}

	//���fli��Ԃ�
	return GetLSB(rfb);
}
//! fli,sli���烊�X�g�C���f�b�N�X�����߂�
DrByte DrTLSFMemoryAllocator::GetFIndex(DrByte fli, DrByte sli)
{
	return fli*pow(2, m_divisionCategoryNo) + sli - 1;
}
//! Todo:����T�C�Y���������Ă��郊�X�g�C���f�b�N�X��Ԃ�
DrByte DrTLSFMemoryAllocator::GetFIndex(DrUint size)
{
	return 0;
}
//! �����Ă���r�b�g�����J�E���g����(32bit ulong)
int DrTLSFMemoryAllocator::GetBitCount(DrUint value)
{
	DrInt count = (value & 0x55555555) + ((value >> 1) & 0x55555555);
	count = (count & 0x33333333) + ((count >> 2) & 0x33333333);
	count = (count & 0x0f0f0f0f) + ((count >> 4) & 0x0f0f0f0f);
	count = (count & 0x00ff00ff) + ((count >> 8) & 0x00ff00ff);
	return (count & 0x0000ffff) + ((count >> 16) & 0x0000ffff);
}

#pragma endregion