
#pragma once
#include "DrTypeCmn.h"

template<typename Type>
class DrArrayType2
{
public:
	union
	{
		Type m[2];
		struct
		{
			Type x, y;
		};
	};

#pragma region //コンストラクタ
	DrArrayType2(Type _x = 0, Type _y = 0)
	{
		x = (Type)_x;
		y = (Type)_y;
	}
	template<typename T>
	DrArrayType2(T* _array)
	{
		x = (Type)_array[0];
		y = (Type)_array[1];
	}
	template<typename T>
	DrArrayType2(const T & v)
	{
		x = (Type)v.x;
		y = (Type)v.y;
	}

#pragma endregion

#pragma region //オペレーター
	inline Type& operator[](int n)
	{
		return m[n];
	}

	template<typename T>
	inline DrArrayType2<Type>& operator = (const T& v)
	{
		x = (Type)v.x;
		y = (Type)v.y;
		return *this;
	}
	template<typename T>
	inline DrArrayType2<Type> operator+ (const T& n)
	{
		return DrArrayType2<Type>(x + (Type)n.x, y + (Type)n.y);
	}
	template<typename T>
	inline DrArrayType2<Type> operator- (const T& n)
	{
		return DrArrayType2<Type>(x - (Type)n.x, y - (Type)n.y);
	}
	template<typename T>
	inline DrArrayType2<Type> operator* (const T& n)
	{
		return DrArrayType2(x*(Type)n.x, y * (Type)n.y);
	}

	inline DrArrayType2<Type> operator* (Type n)
	{
		return DrArrayType2(x*(Type)n, y*(Type)n);
	}
	template<typename T>
	inline DrArrayType2<Type> operator/ (const T& n)
	{
		return DrArrayType2(x / (Type)n.x, y / (Type)n.y);
	}

	inline DrArrayType2<Type> operator/ (Type n)
	{
		return DrArrayType2(x / (Type)n, y / (Type)n);
	}

	template<typename T>
	inline DrArrayType2<Type>& operator+= (const T& n)
	{
		x += (Type)n.x;
		y += (Type)n.y;
		return *this;
	}
	template<typename T>
	inline DrArrayType2<Type>& operator-= (const T& n)
	{
		x -= (Type)n.x;
		y -= (Type)n.y;
		return *this;
	}
	template<typename T>
	inline DrArrayType2<Type>& operator*= (const T& n)
	{
		x *= (Type)n.x;
		y *= (Type)n.y;
		return *this;
	}

	inline DrArrayType2<Type>& operator*= (Type n)
	{
		x *= (Type)n;
		y *= (Type)n;
		return *this;
	}
	template<typename T>
	inline DrArrayType2<Type>& operator/= (const T& n)
	{
		x /= (Type)n.x;
		y /= (Type)n.y;
		return *this;
	}

	inline DrArrayType2<Type>& operator/= (Type n)
	{
		x /= (Type)n;
		y /= (Type)n;
		return *this;
	}

	DrBool operator ==(const DrArrayType2<Type>& b)
	{
		return x == b.x && y == b.y;
	}

	DrBool operator !=(const DrArrayType2<Type>& b)
	{
		return !(*this == b);
	}

#pragma endregion

	inline Type	 Sum()
	{
		return x + y;
	}
};

template<typename Type>
class DrArrayType3
{
public:

	union
	{
		Type m[3];
		struct
		{
			Type x, y, z;
		};
	};

#pragma region //コンストラクタ
	DrArrayType3(Type _x = 0,
		Type _y = 0,
		Type _z = 0)
	{
		x = (Type)_x;
		y = (Type)_y;
		z = (Type)_z;
	}

	DrArrayType3(DrArrayType2<Type> n, Type _z)
	{
		x = n.x;
		y = n.y;
		z = _z;
	}

	template<typename T>
	DrArrayType3(T* _array)
	{
		x = (Type)_array[0];
		y = (Type)_array[1];
		z = (Type)_array[2];
	}
	template<typename T>
	DrArrayType3(const T & n)
	{
		*this = n;
	}

#pragma endregion

#pragma region オペレータ

	inline Type& operator[](int n)
	{
		return m[n];
	}

	template<typename T>
	inline DrArrayType3<Type>& operator = (const T& n)
	{
		x = (Type)n.x;
		y = (Type)n.y;
		z = (Type)n.z;
		return *this;
	}
	template<typename T>
	inline DrArrayType3<Type> operator+ (const T& n)
	{
		return DrArrayType3<Type>(x + (Type)n.x, y + (Type)n.y, z + (Type)n.z);
	}
	template<typename T>
	inline DrArrayType3<Type> operator- (const T& n)
	{
		return DrArrayType3<Type>(x - (Type)n.x, y - (Type)n.y, z - (Type)n.z);
	}
	template<typename T>
	inline DrArrayType3<Type> operator* (const T& n)
	{
		return DrArrayType3(x*(Type)n.x, y * (Type)n.y, z*(Type)n.z);
	}

	inline DrArrayType3<Type> operator* (Type n)
	{
		return DrArrayType3(x*(Type)n, y*(Type)n, z*(Type)n);
	}
	template<typename T>
	inline DrArrayType3<Type> operator/ (const T& n)
	{
		return DrArrayType3(x / (Type)n.x, y / (Type)n.y, z / (Type)n.z);
	}

	inline DrArrayType3<Type> operator/ (Type n)
	{
		return DrArrayType3(x / (Type)n, y / (Type)n, z / (Type)n);
	}

	template<typename T>
	inline DrArrayType3<Type>& operator+= (const T& n)
	{
		x += (Type)n.x;
		y += (Type)n.y;
		z += (Type)n.z;
		return *this;
	}
	template<typename T>
	inline DrArrayType3<Type>& operator-= (const T& n)
	{
		x -= (Type)n.x;
		y -= (Type)n.y;
		z -= (Type)n.z;
		return *this;
	}
	template<typename T>
	inline DrArrayType3<Type>& operator*= (const T& n)
	{
		x *= (Type)n.x;
		y *= (Type)n.y;
		z *= (Type)n.z;
		return *this;
	}

	inline DrArrayType3<Type>& operator*= (Type n)
	{
		x *= (Type)n;
		y *= (Type)n;
		z *= (Type)n;
		return *this;
	}
	template<typename T>
	inline DrArrayType3<Type>& operator/= (const T& n)
	{
		x /= (Type)n.x;
		y /= (Type)n.y;
		z /= (Type)n.z;
		return *this;
	}

	inline DrArrayType3<Type>& operator/= (Type n)
	{
		x /= (Type)n;
		y /= (Type)n;
		z /= (Type)n;
		return *this;
	}

	DrBool operator ==(const DrArrayType3<Type>& b)
	{
		return x == b.x && y == b.y && z == b.z;
	}

	DrBool operator !=(const DrArrayType3<Type>& b)
	{
		return !(*this == b);
	}

#pragma endregion

	inline Type	 Sum()
	{
		return x + y + z;
	}

	inline Type Length()
	{
		return (Type)pow((x * x) + (y * y) + (z * z), 0.5);
	}

	inline void Normalize()
	{
		Type length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	static DrArrayType3<Type> Cross(const DrArrayType3<Type>& a, const DrArrayType3<Type>& b)
	{
		return DrArrayType3<Type>((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
	}

	static Type Dot(const DrArrayType3<Type>& a, const DrArrayType3<Type>& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
};

template<typename Type>
class DrArrayType4
{
public:

	union
	{
		Type m[4];
		struct
		{
			Type x, y, z, w;
		};
	};

#pragma region //コンストラクタ
	DrArrayType4(Type _x = 0,
		Type _y = 0,
		Type _z = 0,
		Type _w = 0)
	{
		x = (Type)_x;
		y = (Type)_y;
		z = (Type)_z;
		w = (Type)_w;
	}

	DrArrayType4(DrArrayType3<Type> n, Type _w)
	{
		x = n.x;
		y = n.y;
		z = n.z;
		w = _w;
	}

	DrArrayType4(DrArrayType2<Type> n, Type _z, Type _w)
	{
		x = n.x;
		y = n.y;
		z = _z;
		w = _w;
	}

	template<typename T>
	DrArrayType4(T* _array)
	{
		x = (Type)_array[0];
		y = (Type)_array[1];
		z = (Type)_array[2];
		w = (Type)_array[3];
	}
	template<typename T>
	DrArrayType4(const T & n)
	{
		*this = n;
	}
#pragma endregion

#pragma region オペレータ
	inline Type& operator[](int n)
	{
		return m[n];
	}

	template<typename T>
	inline DrArrayType4<Type>& operator = (const T& n)
	{
		x = (Type)n.x;
		y = (Type)n.y;
		z = (Type)n.z;
		w = (Type)n.w;
		return *this;
	}
	template<typename T>
	inline DrArrayType4<Type> operator+ (const T& n)
	{
		return DrArrayType4<Type>(x + (Type)n.x, y + (Type)n.y, z + (Type)n.z, w + (Type)n.w);
	}
	template<typename T>
	inline DrArrayType4<Type> operator- (const T& n)
	{
		return DrArrayType4<Type>(x - (Type)n.x, y - (Type)n.y, z - (Type)n.z, w + (Type)n.w);
	}
	template<typename T>
	inline DrArrayType4<Type> operator* (const T& n)
	{
		return DrArrayType4(x*(Type)n.x, y * (Type)n.y, z*(Type)n.z, w + (Type)n.w);
	}

	inline DrArrayType4<Type> operator* (Type n)
	{
		return DrArrayType4(x*(Type)n, y*(Type)n, z*(Type)n, w*(Type)n);
	}
	template<typename T>
	inline DrArrayType4<Type> operator/ (const T& n)
	{
		return DrArrayType4(x / (Type)n.x, y / (Type)n.y, z / (Type)n.z, w / (Type)n.z);
	}

	inline DrArrayType4<Type> operator/ (Type n)
	{
		return DrArrayType4(x / (Type)n, y / (Type)n, z / (Type)n, w / (Type)n);
	}

	template<typename T>
	inline DrArrayType4<Type>& operator+= (const T& n)
	{
		x += (Type)n.x;
		y += (Type)n.y;
		z += (Type)n.z;
		w += (Type)n.w;
		return *this;
	}
	template<typename T>
	inline DrArrayType4<Type>& operator-= (const T& n)
	{
		x -= (Type)n.x;
		y -= (Type)n.y;
		z -= (Type)n.z;
		w -= (Type)n.w;
		return *this;
	}
	template<typename T>
	inline DrArrayType4<Type>& operator*= (const T& n)
	{
		x *= (Type)n.x;
		y *= (Type)n.y;
		z *= (Type)n.z;
		w *= (Type)n.w;
		return *this;
	}

	inline DrArrayType4<Type>& operator*= (Type n)
	{
		x *= (Type)n;
		y *= (Type)n;
		z *= (Type)n;
		w *= (Type)n;
		return *this;
	}
	template<typename T>
	inline DrArrayType4<Type>& operator/= (const T& n)
	{
		x /= (Type)n.x;
		y /= (Type)n.y;
		z /= (Type)n.z;
		w /= (Type)n.w;
		return *this;
	}

	inline DrArrayType4<Type>& operator/= (Type n)
	{
		x /= (Type)n;
		y /= (Type)n;
		z /= (Type)n;
		w /= (Type)n;
		return *this;
	}

	DrBool operator == (const DrArrayType4<Type>& b)
	{
		return x == b.x && y == b.y && z == b.z && w == b.w;
	}
#pragma endregion

	inline Type	 Sum()
	{
		return x + y + z + w;
	}
};

typedef DrArrayType2<DrS8>          DrS8_2;
typedef DrArrayType2<DrS8>          DrU8_2;
typedef DrArrayType2<DrShort>       DrShort2;
typedef DrArrayType2<DrUshort>      DrUShort2;
typedef DrArrayType2<DrInt>         DrInt2;
typedef DrArrayType2<DrUint>        DrUint2;
typedef DrArrayType2<DrS64>         DrS64_2;
typedef DrArrayType2<DrU64>         DrU64_2;
typedef DrArrayType2<DrF32>         DrFloat2;
typedef DrArrayType2<DrF64>         DrDouble2;

typedef DrArrayType3<DrInt>         DrInt3;
typedef DrArrayType3<DrUint>        DrUint3;
typedef DrArrayType3<DrShort>       DrShort3;
typedef DrArrayType3<DrUshort>      DrUShort3;
typedef DrArrayType3<DrS64>         DrS64_3;
typedef DrArrayType3<DrU64>         DrU64_3;
typedef DrArrayType3<DrS8>          DrS8_3;
typedef DrArrayType3<DrS8>          DrU8_3;
typedef DrArrayType3<DrF32>         DrFloat3;
typedef DrArrayType3<DrF64>         DrDouble3;

typedef DrArrayType4<DrInt>         DrInt4;
typedef DrArrayType4<DrUint>        DrUint4;
typedef DrArrayType4<DrShort>       DrShort4;
typedef DrArrayType4<DrUshort>      DrUShort4;
typedef DrArrayType4<DrS64>         DrS64_4;
typedef DrArrayType4<DrU64>         DrU64_4;
typedef DrArrayType4<DrS8>          DrS8_4;
typedef DrArrayType4<DrS8>          DrU8_4;
typedef DrArrayType4<DrF32>         DrFloat4;
typedef DrArrayType4<DrF64>         DrDouble4;