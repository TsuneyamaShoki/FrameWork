
#pragma once

//! Include
#include "../Utility/DrMainUtility.h"


#pragma region //! DrBoundaryTagBlock [typedef DrBBlock]

//! this[�擪]m_pointer[�^�p������][�I�[]
//! [Class] DrBoundaryTagBrock
class DrBoundaryTagBlock
{
public:
	//! �g�p�����ǂ����̃t���O
	DrBool m_isOccupied;
	//! �f�[�^���T�C�Y
	DrUint m_size;
	//! �擪�|�C���^
	DrByte* m_pointer;
	//! endTag�ւ̃|�C���^
	DrUint* m_endTagPointer;

	//DrBoundaryTagBrock�̑o�������X�g
	DrBoundaryTagBlock *m_prev, *m_next;

	//! �R���X�g���N�^
	DrBoundaryTagBlock();
	DrBoundaryTagBlock(DrByte* p,DrUint size);

	//! �o�������X�g�֓����B
	DrBoundaryTagBlock* Regist(DrBoundaryTagBlock* nbp);
	//! �o�������X�g���甲����B
	DrBoundaryTagBlock* Remove();

	//! �^�p�T�C�Y���擾
	DrUint GetDataSize();
	//! ���g����L����S�Ẵf�[�^�T�C�Y���擾
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

	//! �^�p��������
	DrUint m_operationSize;

	//! ���m�ۃ�����
	DrUint m_allocatorSize;

	//! ��������
	DrUint m_divideNum;

	//! �m�ۃ������̐擪�|�C���^
	DrByte* m_leadPointer;

	//! �t���[���X�g�u���b�N�z��̐擪�|�C���^
	DrBBlock* m_freeList;

	//! �A�N�e�B�u���X�g�u���b�N�z��擪�f�[�^
	DrBBlock* m_activeList;

	//! �t���[���X�g�r�b�g(���J�e�S��)
	DrUint m_freeListBitFLI;
	//! �t���[���X�g�r�b�g(���J�e�S��)
	DrByte* m_freeListBitSLI;
	DrBool* m_freeListBit;
	DrBool* m_activeListBit;
	DrInt m_bns;	//! sizeof(DrBlock)+sizeof(uint)
	DrInt m_bbs;	//! sizeof(DrBlock)

	//! ������
	void Init(DrUint allMemSize, DrUint maxExpectDivideNum = 1);

	//�������؂�o��
	DrByte* DivideMemory(DrUint size);

	//���������
	void ReleaseMemory(DrByte* p);

	//! Getter
	int GetMSB(DrUint value);						//! 2^x<=value�ƂȂ�x��Ԃ�(Most Significant Bit)
	int GetLSB(DrUint value);						//! 2^x>=value�ƂȂ�x��Ԃ�(LSI)
	DrByte GetSLI(DrUint size, DrByte fli);			//! ���J�e�S���[�C���f�b�N�X(SLI)��Ԃ�
	DrByte GetFreeListSLI(DrByte fli, DrByte sli);	//! ��fli���̏��sli��Ԃ�(���J�e�S�����T��)
	DrByte GetFreeListFLI(DrByte fli);				//! �w��Fli����ʂ�Fli��Ԃ�(���J�e�S�����T��)
	DrByte GetFIndex(DrUint size);					//! ����T�C�Y���������Ă��郊�X�g�C���f�b�N�X��Ԃ�
	DrByte GetFIndex(DrByte fli, DrByte sli);		//! fli,sli���烊�X�g�C���f�b�N�X�����߂�
	int GetBitCount(DrUint value);					//! �����Ă���r�b�g�����J�E���g����(32bit ulong)
#pragma endregion
protected:
public:
	//! �������擾
	template<class T> T* GetMemory(DrUint size = sizeof(T)) 
	{
		return (T*)DivideMemory(size);
	}

	//! ���������
	template<class T> void DeleteMemory(T* p)
	{
		p->~T();
		ReleaseMemory((byte*)p);
	}

	//! �������S�J��
	void Clear();

	DrTLSFMemoryAllocator();
	virtual ~DrTLSFMemoryAllocator();
};
