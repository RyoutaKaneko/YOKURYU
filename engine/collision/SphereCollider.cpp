/**
 * @file SphereCollider.h
 * @brief ���̓����蔻��̃N���X
 * @author �J�l�R_�����E�^
 */

#include "SphereCollider.h"

void SphereCollider::Update()
{
	// ���[���h�s�񂩂���W�𒊏o
	const Matrix4& matWorld = object3d->GetWorldTransform().GetMatWorld();

	const Vector3& position_ = { matWorld.m[3][0],matWorld.m[3][1] ,matWorld.m[3][2] };

	// ���̃����o�ϐ����X�V
	Sphere::center = position_ + offset;
	Sphere::radius = radius;
}