
//! Include
#include "DrNamed.h"


//! ���O���擾
DrString DrNamed::GetName()
{
	return m_name;
}

//! ���O��ݒ�
void DrNamed::SetName(DrString str)
{
	m_name = str;
	m_hashCode = DrNUtlity::StringToHash(str);
}

//! �N���X�̖��O���擾
DrString DrNamed::ClassName()
{
	DrString& str = DrString(typeid(*this).name());
	str = str.substr(str.rfind(" ") + 1);
	return str;
}

//�n�b�V���R�[�h�̎擾
DR_HASH DrNamed::GetHashCode()
{
	return m_hashCode;
}