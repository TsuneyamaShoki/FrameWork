
#pragma once

//! Include
#include "../../Utility/DrMainUtility.h"

//! [class] ���W�X�^�ԍ����������Ă���I�u�W�F�N�g
class DrRegisterResource
{
protected:
	DrInt m_registerIndex;

public:
	DrRegisterResource() : m_registerIndex(0){}

	DrInt GetRegisterIndex()const{ return m_registerIndex; }
	void  SetRegisterIndex(DrInt registerIndex){ m_registerIndex = registerIndex; }
};