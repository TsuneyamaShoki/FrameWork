
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
	// バイナリファイルを読み込む
	// @pram filename	読み込み対象のバイナリのファイルパス
	// @return true is Success
	DrBool Load(DrString filename);

	//=================================================
	//! UnLoad
	// バイナリファイルを開放する。このメソッドは明示的に呼ぶ必要はない。
	// @pram filename	読み込み対象のバイナリのファイルパス
	// @return true is Success
	void UnLoad();

	//=================================================
	//! GetBinary
	// バイナリソースデータを取得する
	// @return Binary Pointer
	DrByte* GetBinary()const;

	//=================================================
	//! GetBinary
	// バイナリソースデータを取得する
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