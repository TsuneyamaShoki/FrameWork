
//! Include
#include "DrQuaternion.h"
#include "DrVector.h"
#include "DrMatrix.h"
#include "DrMathCommons.h"

//! static Member
const DrQuaternion DrQuaternion::identity = DrQuaternion(0, 0, 0, 1);

#pragma region //! operator

DrQuaternion  DrQuaternion::operator * (const DrQuaternion& quaternion)const
{
	return DrQuaternion(XMQuaternionMultiply(ToXMVECTOR(), quaternion.ToXMVECTOR()));
}

DrQuaternion& DrQuaternion::operator *=(const DrQuaternion& quaternion)
{
	return *this = *this * quaternion;
}

#pragma endregion

//! Method
XMVECTOR DrQuaternion::ToXMVECTOR()const
{
	return XMLoadFloat4(this);
}

DrMatrix DrQuaternion::ToMatrix()const
{
	return DrMatrix::CreateRotate(*this);
}

DrVector3 DrQuaternion::ToEuler()const
{
	DrVector3 result;

	DrF32& yAxis = result.y;    //  y axis
	DrF32& zAxis = result.z;    //  z axis
	DrF32& xAxis = result.x;    //  x axis

	DrF32 sqx = x*x;
	DrF32 sqy = y*y;
	DrF32 sqz = z*z;
	DrF32 sqw = w*w;

	DrF32 unit = sqx + sqy + sqz + sqw;
	DrF32 test = x*y + z*w;
	if (test > 0.499f * unit)
	{
		// singularity at north pole
		yAxis = 2.0f * (DrF32)atan2f(x, w);
		zAxis = (DrF32)DR_PI / 2.0f;
		xAxis = 0.0f;
	}
	else if (test < -0.499*unit)
	{
		// singularity at south pole
		yAxis = -2.0f * (DrF32)atan2f(x, w);
		zAxis = -(DrF32)DR_PI / 2.0f;
		xAxis = 0.0f;
	}
	else
	{
		yAxis = (DrF32)atan2f((2.0f*y*w - 2.0f*x*z),
			(sqx - sqy - sqz + sqw));
		zAxis = (DrF32)asinf(2.0f*test / unit);
		xAxis = (DrF32)atan2f((2.0f*x*w - 2.0f*y*z),
			(-sqx + sqy - sqz + sqw));
	}

	return DrToDegree(result);
}

const DrQuaternion& DrQuaternion::Euler(DrF32 x, DrF32 y, DrF32 z)
{
	return *this = CreateByEuler(x, y, z);
}

const DrQuaternion& DrQuaternion::Euler(const DrVector3& v)
{
	return *this = CreateByEuler(v.x, v.y, v.z);
}

const DrQuaternion& DrQuaternion::AngleAxis(const DrVector3& axis, DrF32 angle)
{
	return *this = CreateByAngleAxis(axis, angle);
}

//! static Method
DrQuaternion DrQuaternion::CreateByEuler(DrF32 x, DrF32 y, DrF32 z)
{
	return
		CreateByAngleAxis(DrVector3::right, DrToRadian(x)) *
		CreateByAngleAxis(DrVector3::up, DrToRadian(y)) *
		CreateByAngleAxis(DrVector3::front, DrToRadian(z));
}

DrQuaternion DrQuaternion::CreateByEuler(const DrVector3& Euler)
{
	DrF32 x = Euler.x;
	DrF32 y = Euler.y;
	DrF32 z = Euler.z;
	return CreateByEuler(x, y, z);
}

DrQuaternion DrQuaternion::CreateByAngleAxis(const DrVector3& axis, DrF32 angle)
{
	return DrQuaternion(XMQuaternionRotationMatrix(XMMatrixRotationAxis(axis.ToXMVECTOR(), angle)));
}