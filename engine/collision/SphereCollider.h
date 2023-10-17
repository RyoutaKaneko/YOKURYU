/**
 * @file SphereCollider.cpp
 * @brief 球の当たり判定のクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"
#include "Vector3.h"
#include "Matrix4.h"

class SphereCollider :public BaseCollider, public Sphere
{
private:// エイリアス
public:
	/// <summary>
	/// 球状コライダーをセット
	/// </summary>
	/// <param name="offset">オフセット</param>
	/// <param name="radius">半径</param>
	SphereCollider(Vector3 offset = { 0,0,0 }, float radius = 1.0f) :offset(offset), radius(radius) {
		// 球形状をセット
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// オフセット取得
	/// </summary>
	/// <returns></returns>
	inline const Vector3& GetOffset() { return offset; }

	/// <summary>
	/// オフセット設定
	/// </summary>
	/// <param name="offset_">オフセット</param>
	inline void SetOffset(const Vector3& offset_) { this->offset = offset_; }

	/// <summary>
	/// 半径取得
	/// </summary>
	/// <returns></returns>
	inline float GetRadius() { return radius; }

	/// <summary>
	/// 半径設定
	/// </summary>
	/// <param name="radius_"></param>
	inline void SetRadius(float radius_) { this->radius = radius_; }

private:
	// オブジェクト中心からのオフセット
	Vector3 offset;
	// 半径
	float radius;
};