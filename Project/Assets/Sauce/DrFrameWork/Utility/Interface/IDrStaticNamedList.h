
#pragma once
#include "../Main/DrTypeArray.h"
//! [class] Staticのリストを作成するインターフェイス
template<class T>
class IDrStaticNameObjectList
{
#pragma region //private

private:
	static DrList<T*> m_objectList;
	//! リストにオブジェクトを追加する
	static DrBool AddObject(T* object)
	{
		DrDebugLog("StaticNameObjectList Add Name Object List \n\t name = \"%s\" \n\t hash = %x\n", object->GetName().c_str(), object->GetHashCode());
		m_objectList.push_back(object);

		return DR_TRUE;
	}

	//! リストからオブジェクトを破棄する
	static DrBool RemoveObject(T * object)
	{
		m_objectList.remove(object);
		return DR_TRUE;
	}

#pragma endregion
public:
	//! コンストラクタ
	IDrStaticNameObjectList()
	{
		AddObject(static_cast<T*>(this));
	}

	//! デストラクタ
	virtual ~IDrStaticNameObjectList()
	{
		RemoveObject((T*) this);
	}

	//! オブジェクトの名前でリストから取得する
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

	//! オブジェクトの名前でリストからオブジェクトを削除する
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

//! インターフェースを継承したクラスのcppに追加する必要がある。
#define DR_INSTANTIATE_NAME_OBJ_LIST( type )\
	DrList<type*> IDrStaticNameObjectList<type>::m_objectList;