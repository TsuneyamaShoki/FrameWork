
#pragma once

#include "DrTypeArray.h"

#ifdef _TS_DEBUG
#define DrDebugLog(...)\
	{\
	TSUT::DrLog(__VA_ARGS__); \
	TSUT::DrLog("\t file::%s \n\t func::%s \n\t line::%d\n", TSUT::PassToFileName(__FILE__).c_str(), __FUNCTION__, __LINE__); \
	}
#else
#define DrDebugLog(...)
#endif
// lapping new & app log
#define DrNew(...) \
	new __VA_ARGS__; \
{\
	DrDebugLog("DrNew\n"); \
}

// lapping delete & app log
#define DrDelete(ptr)\
	delete (ptr); \
{\
	DrDebugLog("DrDelete\n"); \
}

#pragma region //! SafeDelete ...

template <typename T>
inline void DrSafeDelete(T*& p)
{
	if (p != nullptr) 
	{
		delete (p);
		(p) = nullptr;
	}
}

template <typename T>
inline void DrSafeDeleteArray(T*& p)
{
	if (p != nullptr)
	{
		delete[](p);
		(p) = nullptr;
	}
}

template <typename T>
inline void DrSafeRelease(T*& p)
{
	if (p != nullptr)
	{
		(p)->Release();
		(p) = nullptr;
	}
}

#pragma endregion

//! 指定されたクラスか調べる
template<class Info, class T>
DrBool  AsType(const T& _data)
{
	printf("%s\n%s", typeid(Info).name(), typeid(_data).name());
	return typeid(Info).name() == typeid(_data).name();
}

//! 指定されたクラスか調べる
template<class Info, class T>
DrBool  AsTypePtr(const T* _data)
{
	return typeid(Info) == typeid(*_data);
}