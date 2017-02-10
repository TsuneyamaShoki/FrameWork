
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
	DrTransForm* m_parent = nullptr;       //! �e�ւ̃|�C���^
	DrTransForm* m_firstChild = nullptr;   //! ���q�ւ̃|�C���^
	DrTransForm* m_subling = nullptr;      //! �Z��ւ̃|�C���^

	//! �e�q�֌W����������
	//  ���̃��\�b�h�͊֘A����e�q�֌W�̑S�������������邱�Ƃ�����B
	DrBool RemoveOfParantChild();
public:
	DrVector3 m_localPosition;
	DrQuaternion m_localRotate;
	DrVector3 m_localScale;

#pragma region //! Constructor

	//! �K��̃R���X�g���N�^
	DrTransForm():m_parent(nullptr), m_localScale(1, 1, 1){};

	//! ���������ꂽ�K���Transform���쐬
	//  translate  �ʒu
	//  quaternion ��]����
	//	scale      �g�k(�f�t�H���g��1,1,1)
	DrTransForm(const DrVector3& translate,
		const DrQuaternion quaternion,
		const DrVector3 scale = DrVector3::one)
		:m_parent(nullptr),
		m_localPosition(translate),
		m_localRotate(quaternion),
		m_localScale(scale){};

	//! �R�s�[�R���X�g���N�^
	DrTransForm(const DrMatrix& m);

#pragma endregion

	//!�f�X�g���N�^
	virtual ~DrTransForm();

	//! Transform��WorldSpaceMatrix�Ŏ擾����
	DrMatrix ToWorldMatrix();
	DrMatrix ToLocalMatrix();
	DrMatrix ToLocalTRSMatrix();

	//! ���[���h�擾�n
	DrVector3 GetWorldPos();
	DrQuaternion GetWorldRotate();
	DrVector3 GetWorldScale();

	//! �e��Transform���擾����
	//  �e�����Ȃ��ꍇ��NULL���Ԃ�
	DrTransForm* GetParent()const;

	DrTransForm * GetFirstChild()const;
	DrTransForm*  GetSubling()const;

	//! �e��ݒ肷��B���̃��\�b�h�Őݒ肳�ꂽTransform��
	DrBool SetParent(__inout DrTransForm* transform);

	//! �q�m�[�h��ǉ�����B���̃��\�b�h�Őݒ肳�ꂽTransform��
	DrBool AddChild(DrTransForm* transform);

	//! �T���n
	//! ���O�ŒT������v����Transform���擾����
	DrTransForm* FindChildByName(const DrString&);
	//! �n�b�V���ŒT������v����Transform���擾����
	DrTransForm* FindChildByhash(DR_HASH);
	//! �N���X���ŒT������v����Transform���擾����
	DrTransForm* FindChildByClassName(const DrString& name);

	//! ��matrix�Ƃ�operator
	DrTransForm& operator = (const DrMatrix& m);
	DrTransForm  operator * (const DrMatrix& m);
	DrTransForm& operator *= (const DrMatrix& m);

	//! RootTransform���擾����
	DrTransForm* GetRootTransform()
	{
		DrTransForm * p = this;
		while (p->m_parent) p = p->m_parent;
		return p;
	};
};
