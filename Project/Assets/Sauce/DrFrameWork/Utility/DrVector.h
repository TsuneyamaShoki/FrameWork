#pragma once

#include "../../Extern/xna/Xna.h"
#include "DrTypeCommons.h"

//! ProtoType
class DrVector2;
class DrVector3;
class DrVector4;
class DrQuaternion;
class DrMatrix;

//! [Class] DrVector2 : XMFLOAT2
class DrVector2 : public XMFLOAT2
{
public:
	// ! staticMenber
	static const DrVector2 zero;
	static const DrVector2 one;
	static const DrVector2 up;
	static const DrVector2 down;
	static const DrVector2 left;
	static const DrVector2 right;

#pragma region //oprator
	using oprator = XMFLOAT2;

	DrVector2(DrF32 _x = 0, DrF32 _y = 0) :XMFLOAT2(_x, _y){};
	DrVector2(XMFLOAT2 vector2) :XMFLOAT2(vector2){};
	DrVector2(XMFLOAT3 vector3) :XMFLOAT2(vector3.x, vector3.y){};
	DrVector2(XMFLOAT4 vector4) :XMFLOAT2(vector4.x, vector4.y){};
	DrVector2(XMVECTOR vector) :XMFLOAT2(vector.m128_f32[0], vector.m128_f32[1]){};

	DrVector2& operator= (const XMVECTOR& Float2);

	DrVector2  operator+ (const XMFLOAT2& Float2)const;
	DrVector2  operator- (const XMFLOAT2& Float2)const;
	DrVector2  operator* (DrF32 Float)const;
	DrVector2  operator/ (DrF32 Float)const;

	DrVector2& operator+= (const XMFLOAT2& Float2);
	DrVector2& operator-= (const XMFLOAT2& Float2);
	DrVector2& operator*= (DrF32 Float);
	DrVector2& operator/= (DrF32 Float);

	DrBool operator==(const DrVector2& value)const;
	DrBool operator!=(const DrVector2& value)const;
	DrBool operator>=(const DrVector2& value)const;
	DrBool operator<=(const DrVector2& value)const;
	DrBool operator>(const DrVector2& value)const;
	DrBool operator<(const DrVector2& value)const;
#pragma endregion

	// ! XMVECTORŽæ“¾
	XMVECTOR  ToXMVECTOR() const;
	
	// ! ’·‚³Žæ“¾
	DrF32 Length() const;
	
	// ! ³‹K‰»Žæ“¾
	DrVector2  Normalized() const;

	// ! “àÏ
	static DrF32 Dot(DrVector2 v0,DrVector2 v1);

	// ! ŠOÏ
	static DrVector2 Closs(DrVector2 v0,DrVector2 v1);

};

//! [Class] DrVector3 : XMFLOAT3
class DrVector3 : public XMFLOAT3
{
public:
	// ! staticMember
	static const DrVector3 zero;
	static const DrVector3 one;
	static const DrVector3 up;
	static const DrVector3 down;
	static const DrVector3 left;
	static const DrVector3 right;
	static const DrVector3 front;
	static const DrVector3 back;

#pragma region //Oprator
	using oprator = XMFLOAT3;

	DrVector3(DrF32 _x = 0, DrF32 _y = 0, DrF32 _z = 0) :XMFLOAT3(_x, _y, _z){};
	DrVector3(XMFLOAT2 vector2) :XMFLOAT3(vector2.x, vector2.y, 0){};
	DrVector3(XMFLOAT3 vector3) :XMFLOAT3(vector3.x, vector3.y, vector3.z){};
	DrVector3(XMFLOAT4 vector4) :XMFLOAT3(vector4.x, vector4.y, vector4.z){};
	DrVector3(XMVECTOR vector) :XMFLOAT3(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2]){};

	DrVector3& operator= (const XMVECTOR& Float3);

	DrVector3  operator+ (const XMFLOAT3& Float3)const;
	DrVector3  operator- (const XMFLOAT3& Float3)const;
	DrVector3  operator* (const XMFLOAT3&)const;
	DrVector3  operator/ (const XMFLOAT3&)const;
	DrVector3  operator* (DrF32 Float)const;
	DrVector3  operator/ (DrF32 Float)const;


	DrVector3& operator+= (const XMFLOAT3& Float3);
	DrVector3& operator-= (const XMFLOAT3& Float3);
	DrVector3& operator*= (DrF32 Float);
	DrVector3& operator/= (DrF32 Float);
	DrVector3& operator*= (const XMFLOAT3& Float);
	DrVector3& operator/= (const XMFLOAT3& Float);

	DrVector3  operator*(const DrMatrix& mat)const;
	DrVector3& operator*=(const DrMatrix& mat);

	DrBool operator==(const DrVector3& value)const;
	DrBool operator!=(const DrVector3& value)const;
	DrBool operator>=(const DrVector3& value)const;
	DrBool operator<=(const DrVector3& value)const;
	DrBool operator>(const DrVector3& value)const;
	DrBool operator<(const DrVector3& value)const;
#pragma endregion

	// ! TransformCoodŽæ“¾
	DrVector3& TransformCood(const DrMatrix& mat)const;
	
	// ! XMVECTORŽæ“¾
	XMVECTOR  ToXMVECTOR()const;
	
	// ! ’·‚³Žæ“¾
	DrF32 Length()const;
	
	// ! ³‹K‰»Žæ“¾
	DrVector3  Normalized()const;

	// ! “àÏŽæ“¾
	static DrF32 Dot(DrVector3 v0,DrVector3 v1);
	
	// ! ŠOÏŽæ“¾
	static DrVector3 Cross(DrVector3 v0,DrVector3 v1);

	// ! Šp“xŽæ“¾
	static DrF32 CrossingAngle(DrVector3 v0, DrVector3 v1);
};

//! [Class] DrVector4 : XMFLOAT4
class DrVector4 : public XMFLOAT4
{
public:

	using oprator = XMFLOAT4;

	DrVector4(DrF32 _x = 0, DrF32 _y = 0, DrF32 _z = 0, DrF32 _w = 0) :XMFLOAT4(_x, _y, _z, _w){};
	DrVector4(XMFLOAT2 vector2) :XMFLOAT4(vector2.x, vector2.y, 0, 0){};
	DrVector4(XMFLOAT3 vector3) :XMFLOAT4(vector3.x, vector3.y, vector3.z, 0){};
	DrVector4(XMFLOAT4 vector4) :XMFLOAT4(vector4.x, vector4.y, vector4.z, vector4.w){};
	DrVector4(XMVECTOR vector) :XMFLOAT4(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2], vector.m128_f32[3]){};

	DrVector4& operator= (const XMVECTOR& Float4);
	DrVector4& operator= (const XMFLOAT3& Float3);

	DrVector4  operator+ (const XMFLOAT4& Float4)const;
	DrVector4  operator- (const XMFLOAT4& Float4)const;
	DrVector4  operator* (DrF32 Float)const;
	DrVector4  operator/ (DrF32 Float)const;

	DrVector4& operator+= (const XMFLOAT4& Float4);
	DrVector4& operator-= (const XMFLOAT4& Float4);
	DrVector4& operator*= (DrF32 Float);
	DrVector4& operator/= (DrF32 Float);

	DrVector4  operator * (const DrMatrix& mat);
	DrVector4& operator *=(const DrMatrix& mat);

	DrBool operator==(const DrVector4& value)const;
	DrBool operator!=(const DrVector4& value)const;
	DrBool operator>=(const DrVector4& value)const;
	DrBool operator<=(const DrVector4& value)const;
	DrBool operator>(const DrVector4& value)const;
	DrBool operator<(const DrVector4& value)const;

	XMVECTOR  ToXMVECTOR()const;
	DrF32 Length()const;
	DrVector4& Normalize();
	DrVector4  Normalized()const;


	static DrF32 Dot(DrVector4 v0,
		DrVector4 v1);

	static DrVector4 Closs(DrVector4 v0,
		DrVector4 v1);

	static const DrVector4 zero;
	static const DrVector4 one;
	static const DrVector4 up;
	static const DrVector4 down;
	static const DrVector4 left;
	static const DrVector4 right;
	static const DrVector4 front;
	static const DrVector4 back;
};