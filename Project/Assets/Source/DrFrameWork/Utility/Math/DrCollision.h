
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
//! �T�|�[�g���Ă���R���W����
//
// @�_�Ɠ_(2D)             CollisionPointAndPoint()
// @�_�ƃ��C(2D)           CollisionRayAndPoint()
// @�����Ɠ_(2D)           CollisionLineAndPoint()
// @�����Ɛ���(2D)         CollisionLineAndLine()
// @�~�Ɠ_                 CollisionSphereAndPoint2D()
// @�~�Ɖ~                 CollisionSphereAndSphere2D()
// @�~�ƃ��C               CollisionSphereAndRay2D()
// @�~�Ɛ���               CollisionSphereAndLine2D()
// @�����ƎO�p�`(2D)       CollisionLineAndTriangle() 
// @�O�p�`�ƎO�p�`(2D)     CollisionTriangleAndTriangle() 
// @AABB�Ɠ_ (2D)          CollisionAABBAndPoint()
// @AABB��AABB             CollisionAABBAndAABB()
// @AABB�ƃ��C             CollisionAABBAndRay()
// @AABB�Ɛ���             CollisionAABBAndLine()
// @AABB�Ɖ~               CollisionAABBAndSphere()
//
// @�_�Ɠ_(3D)             CollisionPointAndPoint()
// @���Ɠ_(3D)             CollisionRayAndPoint()
// @�����Ɠ_(3D)           CollisionLineAndPoint()
// @�����Ɛ���(3D)         CollisionLineAndLine()
// @���Ɠ_                 CollisionSphereAndPoint()
// @���Ƌ�                 CollisionSphereAndSphere()
// @���ƃ��C               CollisionSphereAndRay()
// @���Ɛ���               CollisionSphereAndLine()
// @���ʂƃ��C             CollisionRayAndPlane()
// @�����ƎO�p�`           CollisionLineAndTriangle() 
// @�O�p�`�ƎO�p�`(3D)     CollisionTriangleAndTriangle() 
// @AABB�Ɠ_               CollisionAABBAndPoint()
// @AABB��AABB             CollisionAABBAndAABB()
// @AABB�ƃ��C             CollisionAABBAndRay()
// @AABB�Ɛ���             CollisionAABBAndLine()
// @AABB�Ƌ�               CollisionAABBAndSphere()
// @OBB�Ɠ_                CollisionOBBAndPoint()
// @OBB�Ƌ�                CollisionOBBAndSphere()
// @OBB�ƃ��C              CollisionOBBAndRay()
// @OBB�Ɛ���              CollisionOBBAndLine()
// @OBB��OBB               CollisionOBBAndOBB()
// @OBB��AABB              CollisionOBBAndAABB()

//----------------------------------------------------------
//! �_�Ɠ_
//  @ref �Փ˓_�͓_�Ɠ�����
//  @return �Փ� true 
//----------------------------------------------------------
template <typename T>
DrBool CollisionPpintAndPoint(const T& p0, const T& p1,
								DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! ���C(������)�Ɠ_
//  @ref �Փ˓_�͓_�Ɠ�����
//----------------------------------------------------------
template< typename T>
DrBool CollisionRayAndPoint(const DrRay<T>& ray, const T& point,
							DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! �����Ɠ_
//  @ref �Փ˓_�͓_1�Ɠ�����
//----------------------------------------------------------
template< typename T>
DrBool CollisionLineAndPoint(const DrLine<T>& line, const T& point,
								DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! �����Ɛ����@�̏Փ˔���
//  @param  line0       ����1
//  @param  line1       ����2
//  @param  tolerance   �덷���e�͈�  (optin)
//  @param  pOut        �Փ˓_�����߂�(option)
//  @return �Փ� true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionLineAndLine(const DrLine<T> &line0,const DrLine<T> &line1,
							DrF32 tolerance = DEFAULT_TOLERANCE, T*     pOut = nullptr);

//----------------------------------------------------------
//! �~or���Ɠ_
//  @return �Փ� true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionSphereAndPoint(const DrSphere<T>& sphere, const T& point);

//----------------------------------------------------------
//! �~�Ɖ~ or ���Ƌ�
//  @return �Փ� true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionSphereAndSphere(const DrSphere<T>& sphere0, const DrSphere<T>& sphere1);

//----------------------------------------------------------
//! �~�Ɠ_
//  @return �Փ� true 
//----------------------------------------------------------
//  @return �Փ� true 
DrBool CollisionSphere2DAndPoint(const DrCircle& circle, const DrVector2& point);

//----------------------------------------------------------
//! ���ƃ��C�̏Փ˔���
//  @param  sphere      ��
//  @param  ray         ���C(�����ɑ�����)
//  @param  tolerance   �덷���e�͈�  (optin)
//  @param  pOut1       �ߌi�̏Փ˓_�����߂�(option)
//  @param  pOut2       ���i�̏Փ˓_�����߂�(option)
//  @return �Փ� true 
//----------------------------------------------------------
template< typename T>
DrBool CollisionSphereAndRay(const DrSphere<T>& sphere,	const DrLine<T>& ray,
	DrF32 tolerance = DEFAULT_TOLERANCE, T* pOut0 = nullptr, T* pOut1 = nullptr);

//----------------------------------------------------------
//! ���Ɛ����̏Փ˔���
//  @param  circle      �~
//  @param  ray         ���C(�����ɑ�����)
//  @param  tolerance   �덷���e�͈�  (optin)
//  @param  pOut1       �ߌi�̏Փ˓_�����߂�(option)
//  @param  pOut2       ���i�̏Փ˓_�����߂�(option)
//  @return �Փ� true 
//----------------------------------------------------------
DrBool CollisionSphereAndRay2D(const DrCircle& circle,
	const DrLine2D& ray,
	//�덷���e�͈�
	DrF32 tolerance = DEFAULT_TOLERANCE,
	DrVector2* pOut0 = nullptr,
	DrVector2* pOut1 = nullptr);

//----------------------------------------------------------
//! �~�Ɖ~
//  @return �Փ� true 
//----------------------------------------------------------
DrBool CollisionSphereAndSphere2D(const DrCircle& c0,
	const DrCircle& c1);
//----------------------------------------------------------
//! ���Ɠ_
//  @return �Փ� true 
//----------------------------------------------------------
DrBool CollisionSphereAndPoint3D(const DrSphere3D& s0,
	const DrVector3& p0);

//----------------------------------------------------------
//! ���Ƌ�
//----------------------------------------------------------
DrBool CollisionSphereAndSphere3D(const DrSphere3D& s0,
	const DrSphere3D& s1);

//----------------------------------------------------------
//! ���܂��͉~�Ɛ����̏Փ˔���
//  @param  s           �~����
//  @param  line        ����
//  @param  tolerance   �덷���e�͈�  (optin)
//----------------------------------------------------------
template<typename T>
DrBool CollisionSphereAndLine(const DrSphere<T>& s,
	const DrLine<T>& line,
	//�덷���e�͈�
	DrF32 tolerance = DEFAULT_TOLERANCE);
//----------------------------------------------------------
//! �~�Ɛ����̏Փ˔���
//  @param  circle      �~
//  @param  line        ����
//  @param  tolerance   �덷���e�͈�  (optin)
//----------------------------------------------------------
DrBool CollisionSphereAndLine2D(const DrCircle& circle,
	const DrLine2D& line,
	//�덷���e�͈�
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! ���ʂƃ��C�̏Փ˔���
//  @param  normal      �ʂ̃x�N�g��
//  @param  ray         ���C
//  @param  tolerance   �덷���e�͈�  (optin)
//----------------------------------------------------------
template<typename T>
DrBool CollisionRayAndPlane(const T& normal,
	const DrRay<T>& ray,
	//�덷���e�͈�
	DrF32 tolerance = DEFAULT_TOLERANCE);
//----------------------------------------------------------
//! �����ƎO�p�`
//  @param  triangle    �O�p�`
//  @param  line        ����
//  @param  tolerance   �덷���e�͈�  (optin)
//  @param  pOut        �����_
//----------------------------------------------------------
template<typename T>
DrBool CollisionLineAndTriangle(const DrTriangle<T>&,
	const DrLine<T>& line,
	//�덷���e�͈�
	DrF32 tolerance = DEFAULT_TOLERANCE,
	T* pOut = nullptr);

//----------------------------------------------------------
//! �O�p�`�ƎO�p�`
//  @param  triangle0   �O�p�`1
//  @param  triangle1   �O�p�`2
//  @param  tolerance   �덷���e�͈�  (optin)
//  @param  pOut        �����_
//----------------------------------------------------------
template<typename T>
DrBool CollisionTriangleAndTriangle(const DrTriangle<T>& triangle0,
	const DrTriangle<T>& triangle1,
	//�덷���e�͈�
	DrF32 tolerance = DEFAULT_TOLERANCE);


//----------------------------------------------------------
//! AABB �Ɓ@AABB
//  @param  aabb0          AABB
//  @param  aabb1          AABB
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndAABB(const DrAABB<T>& aabb0,
	const DrAABB<T>& aabb1);

//----------------------------------------------------------
//! AABB �Ɓ@Ray
//  @param  aabb           AABB
//  @param  ray            ���C
//  @prama  tolerance      �덷���e�͈�
//  @param  pOut           �Փ˓_(option)
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndRay(const DrAABB<T>& aabb,
	const DrRay<T>& ray,
	DrF32 tolerance = DEFAULT_TOLERANCE,
	T * pOut = nullptr);
//----------------------------------------------------------
//! AABB�@�� ����
//  @param  aabb           AABB
//  @param  line           ����
//  @prama  tolerance      �덷���e�͈�
//  @param  pOut           �Փ˓_(option)
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndLine(const DrAABB<T>& aabb,
	const DrSphere<T>& line,
	DrF32 tolerance = DEFAULT_TOLERANCE,
	T * pOut = nullptr);

//----------------------------------------------------------
//! AABB�@�� �_
//  @param  aabb           AABB
//  @param  point          �_
//  @prama  tolerance      �덷���e�͈�
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndPoint(const DrAABB<T>& aabb,
	const T& point);
//----------------------------------------------------------
//! AABB�@�� �~or��
//  @param  aabb           AABB
//  @param  sphere         ��
//----------------------------------------------------------
template<typename T>
DrBool CollisionAABBAndSphere(const DrAABB<T>& aabb,
	const DrSphere<T>& sphere);

//----------------------------------------------------------
//! OBB�@�� �_
//  @param  obb            OBB
//  @param  pt             �_
//  @prama  tolerance      �덷���e�͈�
//----------------------------------------------------------
DrBool CollisionOBBAndPoint(const DrOBB& obb,
	const DrVector3& pt,
	DrF32 tolerance = DEFAULT_TOLERANCE);
//----------------------------------------------------------
//! OBB�@�� ��
//  @param  obb            OBB
//  @param  sphere         ��
//----------------------------------------------------------
DrBool CollisionOBBAndSphere(const DrOBB& obb,
	const DrSphere3D& sphere);

//----------------------------------------------------------
//! OBB�@�� Ray
//  @param  obb            OBB
//  @param  ray            ���C
//  @prama  tolerance      �덷���e�͈�
//----------------------------------------------------------
DrBool CollisionOBBAndRay(const DrOBB& obb,
	const DrRay3D& ray,
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! OBB�@�� ����
//  @param  obb            OBB
//  @param  line           ����
//  @prama  tolerance      �덷���e�͈�
//----------------------------------------------------------
DrBool CollisionOBBAndLine(const DrOBB& obb,
	const DrLine3D& line,
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! OBB�@�� OBB
//  @param  obb            OBB 1
//  @param  obb            OBB 2
//----------------------------------------------------------
DrBool CollisionOBBAndOBB(const DrOBB& obb0,
	const DrOBB& obb1,
	DrF32 tolerance = DEFAULT_TOLERANCE);

//----------------------------------------------------------
//! OBB�@�� AABB
//  @param  obb            OBB 
//  @param  aabb           AABB 
//----------------------------------------------------------
DrBool CollisionOBBAndAABB(const DrOBB& obb,
	const DrAABB3D& aabb,
	DrF32 tolerance = DEFAULT_TOLERANCE);
