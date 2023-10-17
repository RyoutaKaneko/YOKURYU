/**
 * @brief 当たり判定のステータスをまとめたクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include"Vector3.h"

class Object3d;
class BaseCollider;

struct CollisionInfo
{
public:
	/// <summary>
	/// 指定ありの生成
	/// </summary>
	/// <param name="object">オブジェクト</param>
	/// <param name="collider">コライダー</param>
	/// <param name="inter">衝突点</param>
	CollisionInfo(Object3d* object, BaseCollider* collider, const Vector3& inter) {
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	// 衝突相手のオブジェクト
	Object3d* object = nullptr;
	// 衝突相手のコライダー
	BaseCollider* collider = nullptr;
	// 衝突点
	Vector3 inter;

};