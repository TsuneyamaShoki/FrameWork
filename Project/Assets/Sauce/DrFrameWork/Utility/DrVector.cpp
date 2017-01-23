
#include "DrVector.h"
 
#pragma region // ! DrVector2

// ! staticMember
const DrVector2 DrVector2::zero = DrVector2(0, 0);
const DrVector2 DrVector2::one = DrVector2(1, 1);
const DrVector2 DrVector2::up = DrVector2(0, 1);
const DrVector2 DrVector2::down = DrVector2(0, -1);
const DrVector2 DrVector2::left = DrVector2(-1, 0);
const DrVector2 DrVector2::right = DrVector2(1, 0);

// ! オペレータ
DrVector2& DrVector2::operator = (const XMVECTOR& Float2)
{
	this->x = Float2.m128_f32[0];
	this->y = Float2.m128_f32[1];
	return *this;
}
DrVector2  DrVector2::operator+ (const XMFLOAT2& Float2)const
{
	return DrVector2(x + Float2.x, y + Float2.y);
}
DrVector2  DrVector2::operator- (const XMFLOAT2& Float2)const
{
	return DrVector2(x - Float2.x, y - Float2.y);
}
DrVector2  DrVector2::operator* (FLOAT Float)const
{
	return DrVector2(x*Float, y*Float);
}
DrVector2  DrVector2::operator/ (FLOAT Float)const
{
	return DrVector2(x / Float, y / Float);
}
DrVector2& DrVector2::operator+= (const XMFLOAT2& Float2)
{
	return *this = *this + Float2;
}
DrVector2& DrVector2::operator-= (const XMFLOAT2& Float2)
{
	return *this = *this - Float2;
}
DrVector2& DrVector2::operator*= (FLOAT Float)
{
	return *this = *this * Float;
}
DrVector2& DrVector2::operator/= (FLOAT Float)
{
	return *this = *this / Float;
}
DrBool DrVector2::operator==(const DrVector2& value)const
{
	return x == value.x &&
		y == value.y;
}
DrBool DrVector2::operator!=(const DrVector2& value)const
{
	return !(*this == value);
}
DrBool DrVector2::operator>=(const DrVector2& value)const
{
	return x >= value.x && y >= value.y;
}
DrBool DrVector2::operator<=(const DrVector2& value)const
{
	return x <= value.x && y <= value.y;
}
DrBool DrVector2::operator>(const DrVector2& value)const
{
	return x > value.x && y > value.y;
}
DrBool DrVector2::operator<(const DrVector2& value)const
{
	return x < value.x && y < value.y;
}

// ! XMVECTOR取得
XMVECTOR DrVector2::ToXMVECTOR()const
{
	return XMLoadFloat2(this);
}

// ! 長さ取得
FLOAT DrVector2::Length()const
{
	XMVECTOR vLength = XMVector2Length(ToXMVECTOR());
	return (vLength.m128_f32[0] + vLength.m128_f32[1]);
}

// ! 正規化取得
DrVector2 DrVector2::Normalized()const
{
	return DrVector2(XMVector2Normalize(ToXMVECTOR()));
}

// ! 内積
FLOAT DrVector2::Dot(DrVector2 v0, DrVector2 v1)
{
	return XMVector2Dot(v0.ToXMVECTOR(), v1.ToXMVECTOR()).m128_f32[0];
}

// ! 外積
DrVector2 DrVector2::Closs(DrVector2 v0, DrVector2 v1)
{
	return DrVector2(XMVector2Cross(v0.ToXMVECTOR(), v1.ToXMVECTOR()));
}
#pragma endregion

#pragma region // ! DrVector3

// ! staticMember
const DrVector3 DrVector3::zero = DrVector3(0, 0, 0);
const DrVector3 DrVector3::one = DrVector3(1, 1, 1);
const DrVector3 DrVector3::up = DrVector3(0, 1, 0);
const DrVector3 DrVector3::down = DrVector3(0, -1, 0);
const DrVector3 DrVector3::left = DrVector3(-1, 0, 0);
const DrVector3 DrVector3::right = DrVector3(1, 0, 0);
const DrVector3 DrVector3::front = DrVector3(0, 0, 1);
const DrVector3 DrVector3::back = DrVector3(0, 0, -1);

// ! operator
DrVector3& DrVector3::operator = (const XMVECTOR& Float3)
{
	this->x = Float3.m128_f32[0];
	this->y = Float3.m128_f32[1];
	this->z = Float3.m128_f32[2];
	return *this;
}

DrVector3  DrVector3::operator+ (const XMFLOAT3& Float3)const
{
	return DrVector3(x + Float3.x, y + Float3.y, z + Float3.z);
}
DrVector3  DrVector3::operator- (const XMFLOAT3& Float3)const
{
	return DrVector3(x - Float3.x, y - Float3.y, z - Float3.z);
}
DrVector3  DrVector3::operator* (FLOAT Float)const
{
	return DrVector3(x * Float, y * Float, z * Float);
}
DrVector3  DrVector3::operator/ (FLOAT Float)const
{
	return DrVector3(x / Float, y / Float, z / Float);
}

DrVector3 DrVector3::operator/ (const XMFLOAT3& v)const
{
	return DrVector3(x / v.x, y / v.y, z / v.z);
}

DrVector3 DrVector3::operator* (const XMFLOAT3& v)const
{
	return DrVector3(x * v.x, y * v.y, z * v.z);
}

DrVector3& DrVector3::operator+= (const XMFLOAT3& Float3)
{
	return *this = *this + Float3;
}
DrVector3& DrVector3::operator-= (const XMFLOAT3& Float3)
{
	return *this = *this - Float3;
}
DrVector3& DrVector3::operator*= (FLOAT Float)
{
	return *this = *this * Float;
}
DrVector3& DrVector3::operator/= (FLOAT Float)
{
	return *this = *this / Float;
}
DrVector3& DrVector3::operator*= (const XMFLOAT3& v)
{
	return *this = *this * v;
}
DrVector3& DrVector3::operator/= (const XMFLOAT3& v)
{
	return *this = *this / v;
}

DrVector3  DrVector3::operator*(const DrMatrix& mat)const
{
	return DrVector3(XMVector3Transform(ToXMVECTOR(), mat.ToXMMATRIX()));
}
DrVector3& DrVector3::operator*=(const DrMatrix& mat)
{
	return *this = *this * mat;
}

DrBool DrVector3::operator==(const DrVector3& value)const
{
	return	abs(x - value.x) < 0.00001f  &&
		abs(y - value.y) < 0.00001f &&
		abs(z - value.z) < 0.00001f;
}
DrBool DrVector3::operator!=(const DrVector3& value)const
{
	return !(*this == value);
}
DrBool DrVector3::operator>=(const DrVector3& value)const
{
	return x >= value.x && y >= value.y && z >= value.z;
}
DrBool DrVector3::operator<=(const DrVector3& value)const
{
	return x <= value.x && y <= value.y && z <= value.z;
}
DrBool DrVector3::operator>(const DrVector3& value)const
{
	return x > value.x && y > value.y && z > value.z;
}
DrBool DrVector3::operator<(const DrVector3& value)const
{
	return x < value.x && y < value.y && z >value.z;
}


DrVector3& DrVector3::TransformCood(const DrMatrix& mat)const
{
	return 	XMVector3TransformCoord(ToXMVECTOR(), mat.ToXMMATRIX());
}

XMVECTOR DrVector3::ToXMVECTOR()const
{
	return XMLoadFloat3(this);
}

FLOAT DrVector3::Length()const
{
	XMVECTOR vLength = XMVector3Length(ToXMVECTOR());
	return (vLength.m128_f32[0]);
}

DrVector3 DrVector3::Normalized()const
{
	return DrVector3(XMVector3Normalize(ToXMVECTOR()));
}

FLOAT DrVector3::Dot(DrVector3 v0, DrVector3 v1)
{
	return XMVector3Dot(v0.ToXMVECTOR(), v1.ToXMVECTOR()).m128_f32[0];
}

DrVector3 DrVector3::Cross(DrVector3 v0,DrVector3 v1)
{
	return DrVector3(XMVector3Cross(v0.ToXMVECTOR(), v1.ToXMVECTOR()));
}

DrF32 DrVector3::CrossingAngle(DrVector3 v0, DrVector3 v1)
{
	float d = v0.Length() * v1.Length();

	if (d == 0)return 0;

	DrF32 c = Dot(v0, v1) / d;

	if (c >= 1.0) return 0;
	if (c <= -1.0) return DR_PI;

	return acos(c);
}
#pragma endregion

#pragma region // ! DrVector4

// ! staticMembers
const DrVector4 DrVector4::zero = DrVector4(0, 0, 0);
const DrVector4 DrVector4::one = DrVector4(1, 1, 1);
const DrVector4 DrVector4::up = DrVector4(0, 1, 0);
const DrVector4 DrVector4::down = DrVector4(0, -1, 0);
const DrVector4 DrVector4::left = DrVector4(-1, 0, 0);
const DrVector4 DrVector4::right = DrVector4(1, 0, 0);
const DrVector4 DrVector4::front = DrVector4(0, 0, 1);
const DrVector4 DrVector4::back = DrVector4(0, 0, -1);

// ! operators
DrVector4& DrVector4::operator = (const XMVECTOR& Float4)
{
	this->x = Float4.m128_f32[0];
	this->y = Float4.m128_f32[1];
	this->z = Float4.m128_f32[2];
	this->w = Float4.m128_f32[3];
	return *this;
}
DrVector4& DrVector4::operator= (const XMFLOAT3& Float3)
{
	this->x = Float3.x;
	this->y = Float3.y;
	this->z = Float3.z;
	this->w = 0;
	return *this;
}
DrVector4  DrVector4::operator+ (const XMFLOAT4& Float4)const
{
	return DrVector4(x + Float4.x, y + Float4.y, z + Float4.z, w + Float4.w);
}
DrVector4  DrVector4::operator- (const XMFLOAT4& Float4)const
{
	return DrVector4(x - Float4.x, y - Float4.y, z - Float4.z, w - Float4.w);
}
DrVector4  DrVector4::operator* (FLOAT Float)const
{
	return DrVector4(x * Float, y * Float, z * Float, w * Float);
}
DrVector4  DrVector4::operator/ (FLOAT Float)const
{
	return DrVector4(x / Float, y / Float, z / Float, w / Float);
}
DrVector4& DrVector4::operator+= (const XMFLOAT4& Float4)
{
	x += Float4.x;
	y += Float4.y;
	z += Float4.z;
	w += Float4.w;
	return *this;
}
DrVector4& DrVector4::operator-= (const XMFLOAT4& Float4)
{
	x -= Float4.x;
	y -= Float4.y;
	z -= Float4.z;
	w -= Float4.w;
	return *this;
}
DrVector4& DrVector4::operator*= (FLOAT Float)
{
	x *= Float;
	y *= Float;
	z *= Float;
	w *= Float;
	return *this;
}
DrVector4& DrVector4::operator/= (FLOAT Float)
{
	x /= Float;
	y /= Float;
	z /= Float;
	w /= Float;
	return *this;
}
DrVector4  DrVector4::operator*(const DrMatrix& mat)
{
	return DrVector4(XMVector4Transform(ToXMVECTOR(), mat.ToXMMATRIX()));
}
DrVector4& DrVector4::operator*=(const DrMatrix& mat)
{
	return *this = *this * mat;
}
DrBool DrVector4::operator==(const DrVector4& value)const
{
	return	x == value.x &&
		y == value.y &&
		z == value.z &&
		w == value.w;
}
DrBool DrVector4::operator!=(const DrVector4& value)const
{
	return !(*this == value);
}
DrBool DrVector4::operator>=(const DrVector4& value)const
{
	return x >= value.x && y >= value.y && z >= value.z;
}
DrBool DrVector4::operator<=(const DrVector4& value)const
{
	return x <= value.x && y <= value.y && z <= value.z;
}
DrBool DrVector4::operator>(const DrVector4& value)const
{
	return x > value.x && y > value.y && z > value.z;
}
DrBool DrVector4::operator<(const DrVector4& value)const
{
	return x < value.x && y < value.y && z >value.z;
}

//! XMVECTOR取得
XMVECTOR DrVector4::ToXMVECTOR()const
{
	return XMLoadFloat4(this);
}

//! 長さ取得
FLOAT DrVector4::Length()const
{
	XMVECTOR vLength = XMVector2Length(ToXMVECTOR());
	return (vLength.m128_f32[0] +
		vLength.m128_f32[1] +
		vLength.m128_f32[2] +
		vLength.m128_f32[3]);
}

//! 正規化取得
DrVector4 DrVector4::Normalized()const
{
	return DrVector4(XMVector4Normalize(ToXMVECTOR()));
}

// ! 内責取得
FLOAT DrVector4::Dot(DrVector4 v0,DrVector4 v1)
{
	return XMVector4Dot(v0.ToXMVECTOR(), v1.ToXMVECTOR()).m128_f32[0];
}

// ! 外積取得
DrVector4 DrVector4::Closs(DrVector4 v0,DrVector4 v1)
{
	return DrVector3(XMVector3Cross(v0.ToXMVECTOR(), v1.ToXMVECTOR()));
}

#pragma endregion