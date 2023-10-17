/**
 * @file SphereCollider.cpp
 * @brief ���̓����蔻��̃N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"
#include "Vector3.h"
#include "Matrix4.h"

class SphereCollider :public BaseCollider, public Sphere
{
private:// �G�C���A�X
public:
	/// <summary>
	/// ����R���C�_�[���Z�b�g
	/// </summary>
	/// <param name="offset">�I�t�Z�b�g</param>
	/// <param name="radius">���a</param>
	SphereCollider(Vector3 offset = { 0,0,0 }, float radius = 1.0f) :offset(offset), radius(radius) {
		// ���`����Z�b�g
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �I�t�Z�b�g�擾
	/// </summary>
	/// <returns></returns>
	inline const Vector3& GetOffset() { return offset; }

	/// <summary>
	/// �I�t�Z�b�g�ݒ�
	/// </summary>
	/// <param name="offset_">�I�t�Z�b�g</param>
	inline void SetOffset(const Vector3& offset_) { this->offset = offset_; }

	/// <summary>
	/// ���a�擾
	/// </summary>
	/// <returns></returns>
	inline float GetRadius() { return radius; }

	/// <summary>
	/// ���a�ݒ�
	/// </summary>
	/// <param name="radius_"></param>
	inline void SetRadius(float radius_) { this->radius = radius_; }

private:
	// �I�u�W�F�N�g���S����̃I�t�Z�b�g
	Vector3 offset;
	// ���a
	float radius;
};