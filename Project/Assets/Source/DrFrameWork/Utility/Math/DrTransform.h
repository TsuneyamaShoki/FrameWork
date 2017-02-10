
#pragma once

//! Include
#include "../Main/DrNamed.h"
#include "DrVector.h"
#include "DrQuaternion.h"
#include "DrMatrix.h"

//! [class]
class DrTransForm : public DrNamed
{
protected:
	DrTransForm* m_parent = nullptr;       //! 親へのポインタ
	DrTransForm* m_firstChild = nullptr;   //! 第一子へのポインタ
	DrTransForm* m_subling = nullptr;      //! 兄弟へのポインタ

	//! 親子関係を解除する
	//  このメソッドは関連する親子関係の全情報を書き換えることがある。
	DrBool RemoveOfParantChild();
public:
	DrVector3 m_localPosition;
	DrQuaternion m_localRotate;
	DrVector3 m_localScale;

#pragma region //! Constructor

	//! 規定のコンストラクタ
	DrTransForm():m_parent(nullptr), m_localScale(1, 1, 1){};

	//! 初期化された規定のTransformを作成
	//  translate  位置
	//  quaternion 回転成分
	//	scale      拡縮(デフォルトは1,1,1)
	DrTransForm(const DrVector3& translate,
		const DrQuaternion quaternion,
		const DrVector3 scale = DrVector3::one)
		:m_parent(nullptr),
		m_localPosition(translate),
		m_localRotate(quaternion),
		m_localScale(scale){};

	//! コピーコンストラクタ
	DrTransForm(const DrMatrix& m);

#pragma endregion

	//!デストラクタ
	virtual ~DrTransForm();

	//! TransformをWorldSpaceMatrixで取得する
	DrMatrix ToWorldMatrix();
	DrMatrix ToLocalMatrix();
	DrMatrix ToLocalTRSMatrix();

	//! ワールド取得系
	DrVector3 GetWorldPos();
	DrQuaternion GetWorldRotate();
	DrVector3 GetWorldScale();

	//! 親のTransformを取得する
	//  親がいない場合はNULLが返る
	DrTransForm* GetParent()const;

	DrTransForm * GetFirstChild()const;
	DrTransForm*  GetSubling()const;

	//! 親を設定する。このメソッドで設定されたTransformは
	DrBool SetParent(__inout DrTransForm* transform);

	//! 子ノードを追加する。このメソッドで設定されたTransformは
	DrBool AddChild(DrTransForm* transform);

	//! 探索系
	//! 名前で探索し一致するTransformを取得する
	DrTransForm* FindChildByName(const DrString&);
	//! ハッシュで探索し一致するTransformを取得する
	DrTransForm* FindChildByhash(DR_HASH);
	//! クラス名で探索し一致するTransformを取得する
	DrTransForm* FindChildByClassName(const DrString& name);

	//! 対matrixとのoperator
	DrTransForm& operator = (const DrMatrix& m);
	DrTransForm  operator * (const DrMatrix& m);
	DrTransForm& operator *= (const DrMatrix& m);

	//! RootTransformを取得する
	DrTransForm* GetRootTransform()
	{
		DrTransForm * p = this;
		while (p->m_parent) p = p->m_parent;
		return p;
	};
};
