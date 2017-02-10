
#pragma once

//! Include
#include "../DrMainUtility.h"

// [class] DrBinary
class DrBinary : public DrNamed
{
protected:
	DrByte* m_bin;
	DrInt m_size;
public:

	//! Constructor
	DrBinary();
	DrBinary(const DrBinary& bin);
	DrBinary(DrString filename);

	//! Destructor
	virtual~DrBinary();

	//=================================================
	//! Load
	// �o�C�i���t�@�C����ǂݍ���
	// @pram filename	�ǂݍ��ݑΏۂ̃o�C�i���̃t�@�C���p�X
	// @return true is Success
	DrBool Load(DrString filename);

	//=================================================
	//! UnLoad
	// �o�C�i���t�@�C�����J������B���̃��\�b�h�͖����I�ɌĂԕK�v�͂Ȃ��B
	// @pram filename	�ǂݍ��ݑΏۂ̃o�C�i���̃t�@�C���p�X
	// @return true is Success
	void UnLoad();

	//=================================================
	//! GetBinary
	// �o�C�i���\�[�X�f�[�^���擾����
	// @return Binary Pointer
	DrByte* GetBinary()const;

	//=================================================
	//! GetBinary
	// �o�C�i���\�[�X�f�[�^���擾����
	// @return Binary Pointer
	DrInt	GetSize()const;

	//=================================================
	//! Deep Copy
	DrBinary operator = (const DrBinary& bin);

	//Seek
	DrByte*	SeekString(const DrChar* target,
		DrInt startIndex = 0,
		DrInt* outIndex = nullptr);

	DrByte* SeekNumber(DrInt startIndex = 0,
		DrInt* outIndex = nullptr);
};