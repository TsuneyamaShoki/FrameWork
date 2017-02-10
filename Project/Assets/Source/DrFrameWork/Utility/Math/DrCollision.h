
#pragma once

//! Include
#include "../DrMainUtility.h"

//! Global
static const DrF32 DEFAULT_TOLERANCE = FLT_EPSILON;

class DrCircle;
class DrSphere3D;
class DrVector2;
class DrVector3;
class DrLine2D;
class DrLine3D;
class DrRay3D;
class DrOBB;
class DrAABB3D;

//
//! サポートしているコリジョン
//
// @点と点(2D)             CollisionPointAndPoint()
// @点とレイ(2D)           CollisionRayAndPoint()
// @線分と点(2D)           CollisionLineAndPoint()
// @線分と線分(2D)         CollisionLineAndLine()
// @円と点                 CollisionSphereAndPoint2D()
// @円と円                 CollisionSphereAndSphere2D()
// @円とレイ               CollisionSphereAndRay2D()
// @円と線分               CollisionSphereAndLine2D()
// @線分と三角形(2D)       CollisionLineAndTriangle() 
// @三角形と三角形(2D)     CollisionTriangleAndTriangle() 
// @AABBと点 (2D)          CollisionAABBAndPoint()
// @AABBとAABB             CollisionAABBAndAABB()
// @AABBとレイ             CollisionAABBAndRay()
// @AABBと線分             CollisionAABBAndLine()
// @AABBと円               CollisionAABBAndSphere()
//
// @点と点(3D)             CollisionPointAndPoint()
// @線と点(3D)             CollisionRayAndPoint()
// @線分と点(3D)           CollisionLineAndPoint()
// @線分と線分(3D)         CollisionLineAndLine()
// @球と点                 CollisionSphereAndPoint()
// @球と球                 CollisionSphereAndSphere()
// @球とレイ               CollisionSphereAndRay()
// @球と線分               CollisionSphereAndLine()
// @平面とレイ             CollisionRayAndPlane()
// @線分と三角形           CollisionLineAndTriangle() 
// @三角形と三角形(3D)     CollisionTriangleAndTriangle() 
// @AABBと点               CollisionAABBAndPoint()
// @AABBとAABB             CollisionAABBAndAABB()
// @AABBとレイ             CollisionAABBAndRay()
// @AABBと線分             CollisionAABBAndLine()
// @AABBと球               CollisionAABBAndSphere()
// @OBBと点                CollisionOBBAndPoint()
// @OBBと球                CollisionOBBAndSphere()
// @OBBとレイ              CollisionOBBAndRay()
// @OBBと線分              CollisionOBBAndLine()
// @OBBとOBB               CollisionOBBAndOBB()
// @OBBとAABB              CollisionOBBAndAABB()

//----------------------------------------------------------
//! 点と点
//  @ref 衝突点は点と等しい
//  @return 衝突 true 
//----------------------------------------------------------
template <typename T>
DrBool CollisionPpintAndPoint(const T& p0, const T& p1,
								DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! レイ(無限線)と点
//  @ref 衝突点は点と等しい
//----------------------------------------------------------
template< typename T>
DrBool CollisionRayAndPoint(const DrRay<T>& ray, const T& point,
							DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! 線分と点
//  @ref 衝突点は点1と等しい
//----------------------------------------------------------
template< typename T>
DrBool CollisionLineAndPoint(const DrLine<T>& line, const T& point,
								DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! 線分と線分　の衝突判定
//  @param  line0       線分1
//  @param  line1       線分2
//  @param  tolerance   誤差許容範囲  (optin)
//  @param  pOut        衝突点を求める(option)
//  @return 衝突 true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionLineAndLine(const DrLine<T> &line0,const DrLine<T> &line1,
							DrF32 tolerance = DEFAULT_TOLERANCE, T*     pOut = nullptr);

//----------------------------------------------------------
//! 円or球と点
//  @return 衝突 true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionSphereAndPoint(const DrSphere<T>& sphere, const T& point);

//----------------------------------------------------------
//! 円と円 or 球と球
//  @return 衝突 true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionSphereAndSphere(const DrSphere<T>& sphere0, const DrSphere<T>& sphere1);

//----------------------------------------------------------
//! 円と点
//  @return 衝突 true 
//----------------------------------------------------------
//  @return 衝突 true 
DrBool CollisionSphere2DAndPoint(const DrCircle& circle, const DrVector2& point);

//----------------------------------------------------------
//! 球とレイの衝突判定
//  @param  sphere      球
//  @param  ray         レイ(無限に続く線)
//  @param  tolerance   誤差許容範囲  (optin)
//  @param  pOut1       近景の衝突点を求める(option)
//  @param  pOut2       遠景の衝突点を求める(option)
//  @return 衝突 true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionSphereAndRay(const DrSphere<T>& sphere,	const DrLine<T>& ray,
	DrF32 tolerance = DEFAULT_TOLERANCE, T* pOut0 = nullptr, T* pOut1 = nullptr);

//----------------------------------------------------------
//! 球と線分の衝突判定
//  @param  circle      円
//  @param  ray         レイ(無限に続く線)
//  @param  tolerance   誤差許容範囲  (optin)
//  @param  pOut1       近景の衝突点を求める(option)
//  @param  pOut2       遠景の衝突点を求める(option)
//  @return 衝突 true 
//----------------------------------------------------------
DrBool CollisionSphereAndRay2D(const DrCircle& circle,
	const DrLine2D& ray,
	//誤差許容範囲
	DrF32 tolerance = DEFAULT_TOLERANCE,
	DrVector2* pOut0 = nullptr,
	DrVector2* pOut1 = nullptr);

//----------------------------------------------------------
//! 円と円
//  @return 衝突 true 
//----------------------------------------------------------
DrBool CollisionSphereAndSphere2D(const DrCircle& c0,
	const DrCircle& c1);
//----------------------------------------------------------
//! 球と点
//  @return 衝突 true 
//----------------------------------------------------------
DrBool CollisionSphereAndPoint3D(const DrSphere3D& s0,
	const DrVector3& p0);

//----------------------------------------------------------
//! 球と球
//----------------------------------------------------------
DrBool CollisionSphereAndSphere3D(const DrSphere3D& s0,
	const DrSphere3D& s1);

//----------------------------------------------------------
//! 球または円と線分の衝突判定
//  @param  s           円か球
//  @param  line        線分
//  @param  tolerance   誤差許容範囲  (optin)
//----------------------------------------------------------
template<typename T>
DrBool CollisionSphereAndLine(const DrSphere<T>& s,
	const DrLine<T>& line,
	//誤差許容範囲
	DrF32 tolerance = DEFAULT_TOLERANCE);
//----------------------------------------------------------
//! 円と線分の衝突判定
//  @param  circle      円
//  @param  line        線分
//  @param  tolerance   誤差許容範囲  (optin)
//----------------------------------------------------------
DrBool CollisionSphereAndLine2D(const DrCircle& circle,
	const DrLine2D& line,
	//誤差許容範囲
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! 平面とレイの衝突判定
//  @param  normal      面のベクトル
//  @param  ray         レイ
//  @param  tolerance   誤差許容範囲  (optin)
//----------------------------------------------------------
template<typename T>
DrBool CollisionRayAndPlane(const T& normal,
	const DrRay<T>& ray,
	//誤差許容範囲
	DrF32 tolerance = DEFAULT_TOLERANCE);
//----------------------------------------------------------
//! 線分と三角形
//  @param  triangle    三角形
//  @param  line        線分
//  @param  tolerance   誤差許容範囲  (optin)
//  @param  pOut        交差点
//----------------------------------------------------------
template<typename T>
DrBool CollisionLineAndTriangle(const DrTriangle<T>&,
	const DrLine<T>& line,
	//誤差許容範囲
	DrF32 tolerance = DEFAULT_TOLERANCE,
	T* pOut = nullptr);

//----------------------------------------------------------
//! 三角形と三角形
//  @param  triangle0   三角形1
//  @param  triangle1   三角形2
//  @param  tolerance   誤差許容範囲  (optin)
//  @param  pOut        交差点
//----------------------------------------------------------
template<typename T>
DrBool CollisionTriangleAndTriangle(const DrTriangle<T>& triangle0,
	const DrTriangle<T>& triangle1,
	//誤差許容範囲
	DrF32 tolerance = DEFAULT_TOLERANCE);


//----------------------------------------------------------
//! AABB と　AABB
//  @param  aabb0          AABB
//  @param  aabb1          AABB
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndAABB(const DrAABB<T>& aabb0,
	const DrAABB<T>& aabb1);

//----------------------------------------------------------
//! AABB と　Ray
//  @param  aabb           AABB
//  @param  ray            レイ
//  @prama  tolerance      誤差許容範囲
//  @param  pOut           衝突点(option)
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndRay(const DrAABB<T>& aabb,
	const DrRay<T>& ray,
	DrF32 tolerance = DEFAULT_TOLERANCE,
	T * pOut = nullptr);
//----------------------------------------------------------
//! AABB　と 線分
//  @param  aabb           AABB
//  @param  line           線分
//  @prama  tolerance      誤差許容範囲
//  @param  pOut           衝突点(option)
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndLine(const DrAABB<T>& aabb,
	const DrSphere<T>& line,
	DrF32 tolerance = DEFAULT_TOLERANCE,
	T * pOut = nullptr);

//----------------------------------------------------------
//! AABB　と 点
//  @param  aabb           AABB
//  @param  point          点
//  @prama  tolerance      誤差許容範囲
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndPoint(const DrAABB<T>& aabb,
	const T& point);
//----------------------------------------------------------
//! AABB　と 円or球
//  @param  aabb           AABB
//  @param  sphere         球
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndSphere(const DrAABB<T>& aabb,
	const DrSphere<T>& sphere);

//----------------------------------------------------------
//! OBB　と 点
//  @param  obb            OBB
//  @param  pt             点
//  @prama  tolerance      誤差許容範囲
//----------------------------------------------------------
DrBool CollisionOBBAndPoint(const DrOBB& obb,
	const DrVector3& pt,
	DrF32 tolerance = DEFAULT_TOLERANCE);
//----------------------------------------------------------
//! OBB　と 球
//  @param  obb            OBB
//  @param  sphere         球
//----------------------------------------------------------
DrBool CollisionOBBAndSphere(const DrOBB& obb,
	const DrSphere3D& sphere);

//----------------------------------------------------------
//! OBB　と Ray
//  @param  obb            OBB
//  @param  ray            レイ
//  @prama  tolerance      誤差許容範囲
//----------------------------------------------------------
DrBool CollisionOBBAndRay(const DrOBB& obb,
	const DrRay3D& ray,
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! OBB　と 線分
//  @param  obb            OBB
//  @param  line           線分
//  @prama  tolerance      誤差許容範囲
//----------------------------------------------------------
DrBool CollisionOBBAndLine(const DrOBB& obb,
	const DrLine3D& line,
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! OBB　と OBB
//  @param  obb            OBB 1
//  @param  obb            OBB 2
//----------------------------------------------------------
DrBool CollisionOBBAndOBB(const DrOBB& obb0,
	const DrOBB& obb1,
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! OBB　と AABB
//  @param  obb            OBB 
//  @param  aabb           AABB 
//----------------------------------------------------------
DrBool CollisionOBBAndAABB(const DrOBB& obb,
	const DrAABB3D& aabb,
	DrF32 tolerance = DEFAULT_TOLERANCE);
