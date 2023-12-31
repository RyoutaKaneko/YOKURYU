/**
 * @file SphereCollider.h
 * @brief 球の当たり判定のクラス
 * @author カネコ_リョウタ
 */

#include "SphereCollider.h"

void SphereCollider::Update()
{
	// ワールド行列から座標を抽出
	const Matrix4& matWorld = object3d->GetWorldTransform().GetMatWorld();

	const Vector3& position_ = { matWorld.m[3][0],matWorld.m[3][1] ,matWorld.m[3][2] };

	// 球のメンバ変数を更新
	Sphere::center = position_ + offset;
	Sphere::radius = radius;
}