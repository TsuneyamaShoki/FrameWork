#pragma once

//! Include
#include "DrTypeArray.h"
#include "DrFileUtility.h"
//! [Class] DrNameObject
class DrNamed
{
private:
	DrString m_name;		//���O
	DR_HASH m_hashCode;		//���O����v�Z�����n�b�V���R�[�h
public:
	//! ���O���擾
	virtual DrString GetName();
	
	//! ���O��ݒ�
	virtual void SetName(DrString str);

	//! �N���X�̖��O���擾
	virtual DrString ClassName();

	//�n�b�V���R�[�h�̎擾
	DR_HASH GetHashCode();
};
