/**
 * @brief �����蔻����
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "CollisionTypes.h"
#include "Object3d.h"
#include "CollisionInfo.h"

//�R���C�_�[���N���X
class BaseCollider
{
public:
	BaseCollider() = default;
	//���z�f�X�g���N�^
	virtual ~BaseCollider() = default;

	/// <summary>
	/// �I�u�W�F�N�g�Z�b�g
	/// </summary>
	/// <param name="object">�I�u�W�F�N�g</param>
	inline void SetObject(Object3d* object)
	{
		this->object3d = object;
		collname = object->GetName();
	}

	/// <summary>
	/// �I�u�W�F�N�g�擾
	/// </summary>
	/// <returns></returns>
	inline Object3d* GetObject3d()
	{
		return object3d;
	}

	/// <summary>
	/// ���O���Z�b�g
	/// </summary>
	/// <param name="name_">���O</param>
	void SetName(const char* name_) {
		this->collname = name_;
	}

	/// <summary>
	/// ���O���擾
	/// </summary>
	/// <returns></returns>
	const char* GetName() {
		return collname;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��^�C�v�擾
	/// </summary>
	/// <returns></returns>
	inline CollisionShapeType GetShapeType()
	{
		return shapeType;
	}

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	inline void OnCollision(const CollisionInfo& info)
	{
		object3d->OnCollision(info);
	}

	/// <summary>
	/// //�Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	inline void OffCollision(const CollisionInfo& info)
	{
		object3d->OffCollision(info);
	}

protected:
	Object3d* object3d = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	//�Փː�N���X��
	const char* collname = nullptr;
};