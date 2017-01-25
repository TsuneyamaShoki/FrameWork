
#pragma once
#include "../Main/DrTypeArray.h"
//! [class] Static�̃��X�g���쐬����C���^�[�t�F�C�X
template<class T>
class IDrStaticNameObjectList
{
#pragma region //private

private:
	static DrList<T*> m_objectList;
	//! ���X�g�ɃI�u�W�F�N�g��ǉ�����
	static DrBool AddObject(T* object)
	{
		DrDebugLog("StaticNameObjectList Add Name Object List \n\t name = \"%s\" \n\t hash = %x\n", object->GetName().c_str(), object->GetHashCode());
		m_objectList.push_back(object);

		return DR_TRUE;
	}

	//! ���X�g����I�u�W�F�N�g��j������
	static DrBool RemoveObject(T * object)
	{
		m_objectList.remove(object);
		return DR_TRUE;
	}

#pragma endregion
public:
	//! �R���X�g���N�^
	IDrStaticNameObjectList()
	{
		AddObject(static_cast<T*>(this));
	}

	//! �f�X�g���N�^
	virtual ~IDrStaticNameObjectList()
	{
		RemoveObject((T*) this);
	}

	//! �I�u�W�F�N�g�̖��O�Ń��X�g����擾����
	static T* Find(DrString name)
	{
		DR_HASH hash = TSUT::StringToHash(name);

		for each(auto var in m_objectList)
		{
			if (hash == var->GetHashCode())
			{
				return var;
			}
		}
		DrDebugLog("StaticNameObjectList Fail Find Name Object List \n\t name = \"%s\"\n", name.c_str());
		return nullptr;
	}

	//! �I�u�W�F�N�g�̖��O�Ń��X�g����I�u�W�F�N�g���폜����
	static DrBool RemoveObjectByName(DrString name)
	{
		auto object = this->Find(name);
		if (object == nullptr)
		{
			return TS_FALSE;
		}
		RemoveObject(object);
	}
};

//! �C���^�[�t�F�[�X���p�������N���X��cpp�ɒǉ�����K�v������B
#define DR_INSTANTIATE_NAME_OBJ_LIST( type )\
	DrList<type*> IDrStaticNameObjectList<type>::m_objectList;