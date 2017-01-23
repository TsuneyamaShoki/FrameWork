
#pragma once

//! Include
#include "../../Extern/xna/Xna.h"
#include "DrTypeCommons.h"

class DrVector3;
class DrVector4;
class DrQuaternion;

//! [class] DrMatrix
class DrMatrix : public XMFLOAT4X4
{
public:
	//! staticMethod
	static DrMatrix CreateTranslate(FLOAT x, FLOAT y, FLOAT z);
	static DrMatrix CreateTranslate(const DrVector3& translate);
	static DrMatrix CreateRotate(const DrQuaternion& q);
	static DrMatrix CreateScale(FLOAT x, FLOAT y, FLOAT z);
	static DrMatrix CreateScale(const DrVector3& scale);
	static DrMatrix CreateLookAt(const DrVector3& eye, const DrVector3& at, const DrVector3& up);
	//! staticMember
	static const DrMatrix identity;

	//! コンストラクタ
	DrMatrix(XMFLOAT4X4& float4x4) :XMFLOAT4X4(float4x4){};
	DrMatrix(){ *this = DrMatrix::identity; };
	DrMatrix(XMMATRIX& matrix){ *this = matrix; }
	DrMatrix(DrVector3& pos, DrQuaternion& rotate);
	DrMatrix(DrVector3& pos, DrQuaternion& rotate, DrVector3& scale);

#pragma region //! operator
	using oprator = XMFLOAT4X4;
	DrMatrix& operator = (const XMMATRIX& matrix);
	DrMatrix  operator *  (const DrMatrix& matrix)const;
	DrMatrix& operator *= (const DrMatrix& matrix);
	DrBool operator == (const DrMatrix&);
	DrBool operator != (const DrMatrix&);
#pragma endregion

	//! XMMATRIX化
	XMMATRIX  ToXMMATRIX()const;

	//! Quaternion取得
	DrQuaternion ToQuaternion()const;

	//! Transpose
	DrMatrix& Transpose();
	
	//! Inverse
	DrMatrix& Inverse();

	//! Transpose取得
	DrMatrix Transposed()const;
	
	//! Inverse取得
	DrMatrix Inversed();

	//! Transform取得
	DrVector3 TransformCoord(const DrVector3&);
	DrVector3 TransformVector(const DrVector3&);
	DrVector3 TransformPoint(const DrVector3&);
	DrVector4 TransformVector(const DrVector4&);
};