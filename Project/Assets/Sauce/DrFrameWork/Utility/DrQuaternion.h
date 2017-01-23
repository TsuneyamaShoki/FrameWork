
#pragma once
//! Include
#include "../../Extern/xna/Xna.h"
#include "DrTypeCommons.h"
class DrQuaternion;
class DrMatrix;
class DrVector3;
class DrVector4;

//! [class] DrQuaternion
class DrQuaternion : public XMFLOAT4
{
public:
	//! static method
	static DrQuaternion CreateByEuler(const DrVector3& Euler);
	static DrQuaternion CreateByEuler(DrF32 x, DrF32 y, DrF32 z);
	static DrQuaternion CreateByAngleAxis(const DrVector3& axis, DrF32 angle);

	//! static member
	static const DrQuaternion identity;

#pragma region //operator
	using oprator = XMFLOAT4;
	DrQuaternion& operator = (DrMatrix matrix);
	DrQuaternion  operator * (const DrQuaternion& quaternion)const;
	DrQuaternion& operator *=(const DrQuaternion& quaternion);
#pragma endregion

	//! Constructor
	DrQuaternion(FLOAT _x = 0, FLOAT _y = 0, FLOAT _z = 0, FLOAT _w = 1) :XMFLOAT4(_x, _y, _z, _w){};
	DrQuaternion(XMFLOAT4 vector4) : XMFLOAT4(vector4.x, vector4.y, vector4.z, vector4.w){};
	DrQuaternion(XMVECTOR vector) : XMFLOAT4(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2], vector.m128_f32[3]){};

	//! public method
	XMVECTOR  ToXMVECTOR()const;    // simd‚É•ÏŠ·
	DrMatrix  ToMatrix()const;      // Rotate Matrix‚É•ÏŠ·
	DrVector3 ToEuler()const;       // EulerŠp‚É•ÏŠ·

	const DrQuaternion& Euler(DrF32, DrF32, DrF32);
	const DrQuaternion& Euler(const DrVector3&);
	const DrQuaternion& AngleAxis(const DrVector3& axis, DrF32 angle);
};