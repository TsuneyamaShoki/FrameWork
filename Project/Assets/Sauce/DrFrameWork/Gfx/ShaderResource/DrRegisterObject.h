
#pragma once

//! Include
#include "../../Utility/DrMainUtility.h"

//! [class] レジスタ番号を所持しているオブジェクト
class DrRegisterResource
{
protected:
	DrInt m_registerIndex;

public:
	DrRegisterResource() : m_registerIndex(0){}

	DrInt GetRegisterIndex()const{ return m_registerIndex; }
	void  SetRegisterIndex(DrInt registerIndex){ m_registerIndex = registerIndex; }
};