#pragma once

//! Include
#include "../Main/DrTypeCommons.h"

//! Pi
#define DR_PI (3.14159265359f)

//! InlineFunction

//! degree -> radian
template<typename T>
inline T DrToRadian(const T& degree)
{
	return degree * DR_PI / 180.0f;
}

//! radian -> degree
template<typename T>
inline T DrToDegree(const T& radian)
{
	return radian * 180.0f / DR_PI;
}

//! 値を min ~ max　に設定
template<typename T>
inline T DrClamp(const T& value, const T& min, const T& max)
{
	return value < min ? min : value > max ? max : value;
}

//! a と bの大きい方を取得
template<typename T>
inline T DrMax(const T& a, const T& b)
{
	return a > b ? a : b;
}

//! a と bの小さいほうを取得
template<typename T>
inline T DrMin(const T& a, const T& b)
{
	return a < b ? a : b;
}

//! a と b を t で線形補完する
template<typename T>
inline T DrLerp(const T& a, const T&b, DrF32 t)
{
	return a * (1.0f - t) + b * t;
}

//! a と b を t で3次補完する
template<typename T>
inline T DrQubic(const T& a, const T&b, DrF32 t)
{
	return DrLerp(a, b, t * t * (3.0f - 2.0f * t));
}

//! ガウス関数
inline DrF32 Gaussian(float x, float mean, float deviation)
{
	return
		(1.0f / sqrt(2.0f * DR_PI * deviation * deviation))
		* expf((-((x - mean) * (x - mean))) / (2.0f * deviation * deviation));
}
