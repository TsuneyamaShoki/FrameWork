#pragma once

//! Include
#include "DrTypeArray.h"
#include "DrFileUtility.h"
//! [Class] DrNameObject
class DrNamed
{
private:
	DrString m_name;		//名前
	DR_HASH m_hashCode;		//名前から計算したハッシュコード
public:
	//! 名前を取得
	virtual DrString GetName();
	
	//! 名前を設定
	virtual void SetName(DrString str);

	//! クラスの名前を取得
	virtual DrString ClassName();

	//ハッシュコードの取得
	DR_HASH GetHashCode();
};
