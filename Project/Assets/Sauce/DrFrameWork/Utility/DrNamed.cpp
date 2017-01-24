
//! Include
#include "DrNamed.h"


//! 名前を取得
DrString DrNamed::GetName()
{
	return m_name;
}

//! 名前を設定
void DrNamed::SetName(DrString str)
{
	m_name = str;
	m_hashCode = DrNUtlity::StringToHash(str);
}

//! クラスの名前を取得
DrString DrNamed::ClassName()
{
	DrString& str = DrString(typeid(*this).name());
	str = str.substr(str.rfind(" ") + 1);
	return str;
}

//ハッシュコードの取得
DR_HASH DrNamed::GetHashCode()
{
	return m_hashCode;
}