
//! Include
#include "DrMatrix.h"
#include "DrVector.h"
#include "DrQuaternion.h"

//! staticMember
const DrMatrix DrMatrix::identity = XMFLOAT4X4(1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

#pragma region //! コンストラクタ

//! 位置と回転から行列を生成するコンストラクタ
DrMatrix::DrMatrix(DrVector3& p, DrQuaternion& q)
{
	*this = CreateRotate(q) * CreateTranslate(p);
}

//! 位置と回転と拡縮から行列を生成するコンストラクタ
DrMatrix::DrMatrix(DrVector3& p, DrQuaternion& q, DrVector3& scale)
{
	*this = CreateScale(scale) * CreateRotate(q) * CreateTranslate(p);
}

#pragma endregion

#pragma region //! operator

//! XNA行列からの変換用
DrMatrix&  DrMatrix::operator =(const XMMATRIX& i)
{
	memcpy(m, i.m, sizeof(FLOAT)* 16);
	return *this;
}

//! 行列の掛け算計算はXNAVECTORのsimdを利用する
DrMatrix  DrMatrix::operator *(const DrMatrix& matrix)const
{
	return DrMatrix(ToXMMATRIX() * matrix.ToXMMATRIX());
}

DrMatrix& DrMatrix::operator*= (const DrMatrix& matrix)
{
	return (*this = *this * matrix);
}

DrBool DrMatrix::operator==(const DrMatrix& matrix)
{
	return  m[0][0] == matrix.m[0][0] &&
		m[0][1] == matrix.m[0][1] &&
		m[0][2] == matrix.m[0][2] &&
		m[0][3] == matrix.m[0][3] &&
		m[1][0] == matrix.m[1][0] &&
		m[1][1] == matrix.m[1][1] &&
		m[1][2] == matrix.m[1][2] &&
		m[1][3] == matrix.m[1][3] &&
		m[2][0] == matrix.m[2][0] &&
		m[2][1] == matrix.m[2][1] &&
		m[2][2] == matrix.m[2][2] &&
		m[2][3] == matrix.m[2][3] &&
		m[3][0] == matrix.m[3][0] &&
		m[3][1] == matrix.m[3][1] &&
		m[3][2] == matrix.m[3][2] &&
		m[3][3] == matrix.m[3][3];
}

DrBool DrMatrix::operator!=(const DrMatrix& matrix)
{
	return !(*this == matrix);
}

#pragma endregion

//! Method

XMMATRIX  DrMatrix::ToXMMATRIX()const
{
	return XMLoadFloat4x4(this);
}
DrQuaternion DrMatrix::ToQuaternion()const
{
	// 最大成分を検索
	float elem[4]; // 0:x, 1:y, 2:z, 3:w
	elem[0] = _11 - _22 - _33 + 1.0f;
	elem[1] = -_11 + _22 - _33 + 1.0f;
	elem[2] = -_11 - _22 + _33 + 1.0f;
	elem[3] = _11 + _22 + _33 + 1.0f;

	unsigned biggestIndex = 0;
	for (int i = 1; i < 4; i++) {
		if (elem[i] > elem[biggestIndex])
			biggestIndex = i;
	}

	if (elem[biggestIndex] < 0.0f)
		return DrQuaternion(); // 引数の行列に間違いあり！

	// 最大要素の値を算出
	DrQuaternion q;
	float v = sqrtf(elem[biggestIndex]) * 0.5f;

	float mult = 0.25f / v;
	switch (biggestIndex) {
	case 0: // x
		q.x = v;
		q.y = (_12 + _21) * mult;
		q.z = (_31 + _13) * mult;
		q.w = (_32 - _23) * mult;
		break;
	case 1: // y
		q.x = (_12 + _21) * mult;
		q.y = v;
		q.z = (_23 + _32) * mult;
		q.w = (_13 - _31) * mult;
		break;
	case 2: // z
		q.x = (_31 + _13) * mult;
		q.y = (_23 + _32) * mult;
		q.z = v;
		q.w = (_21 - _12) * mult;
		break;
	case 3: // w
		q.x = (_32 - _23) * mult;
		q.y = (_13 - _31) * mult;
		q.z = (_21 - _12) * mult;
		q.w = v;
		break;
	}
	return q;
}
DrMatrix& DrMatrix::Transpose()
{
	return *this = Transposed();
}
DrMatrix& DrMatrix::Inverse()
{
	return *this = Inversed();
}
DrMatrix DrMatrix::Transposed()const
{
	return XMMatrixTranspose(ToXMMATRIX());
}
DrMatrix DrMatrix::Inversed()
{
	return XMMatrixInverse(nullptr, ToXMMATRIX());
}

//! static Method

DrMatrix DrMatrix::CreateTranslate(FLOAT x, FLOAT y, FLOAT z)
{
	return DrMatrix(XMMatrixTranslation(x, y, z));
}
DrMatrix DrMatrix::CreateTranslate(const DrVector3& offset)
{
	return DrMatrix::CreateTranslate(offset.x, offset.y, offset.z);
}
DrMatrix DrMatrix::CreateRotate(const DrQuaternion& q)
{
	return DrMatrix(XMMatrixRotationQuaternion(q.ToXMVECTOR()));
}
DrMatrix DrMatrix::CreateScale(FLOAT x, FLOAT y, FLOAT z)
{
	return DrMatrix(XMMatrixScaling(x, y, z));
}
DrMatrix DrMatrix::CreateScale(const DrVector3& scale)
{
	return DrMatrix::CreateScale(scale.x, scale.y, scale.z);
}
DrMatrix DrMatrix::CreateLookAt(const DrVector3& eye, const DrVector3& at, const DrVector3& up)
{
	return DrMatrix(XMMatrixLookAtLH(eye.ToXMVECTOR(), at.ToXMVECTOR(), up.ToXMVECTOR()));
}
DrVector3 DrMatrix::TransformCoord(const DrVector3& v)
{
	return XMVector3TransformCoord(v.ToXMVECTOR(), ToXMMATRIX());
}
DrVector3 DrMatrix::TransformVector(const DrVector3& v)
{
	return DrVector3(XMVector3Transform(v.ToXMVECTOR(), ToXMMATRIX()));
}
DrVector3 DrMatrix::TransformPoint(const DrVector3& v)
{
	DrVector3 result;
	result.x = v.x * m[0][0] +
		v.y * m[1][0] +
		v.z * m[2][0] +
		m[3][0];

	result.y = v.x * m[0][1] +
		v.y * m[1][1] +
		v.z * m[2][1] +
		m[3][1];

	result.z = v.x * m[0][2] +
		v.y * m[1][2] +
		v.z * m[2][2] +
		m[3][2];

	return result;
}
DrVector4 DrMatrix::TransformVector(const DrVector4& v)
{
	return DrVector4(XMVector4Transform(v.ToXMVECTOR(), ToXMMATRIX()));;
}
