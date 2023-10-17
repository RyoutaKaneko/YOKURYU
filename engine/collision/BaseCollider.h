/**
 * @brief 当たり判定基盤
 * @author カネコ_リョウタ
 */

#pragma once
#include "CollisionTypes.h"
#include "Object3d.h"
#include "CollisionInfo.h"

//コライダー基底クラス
class BaseCollider
{
public:
	BaseCollider() = default;
	//仮想デストラクタ
	virtual ~BaseCollider() = default;

	/// <summary>
	/// オブジェクトセット
	/// </summary>
	/// <param name="object">オブジェクト</param>
	inline void SetObject(Object3d* object)
	{
		this->object3d = object;
		collname = object->GetName();
	}

	/// <summary>
	/// オブジェクト取得
	/// </summary>
	/// <returns></returns>
	inline Object3d* GetObject3d()
	{
		return object3d;
	}

	/// <summary>
	/// 名前をセット
	/// </summary>
	/// <param name="name_">名前</param>
	void SetName(const char* name_) {
		this->collname = name_;
	}

	/// <summary>
	/// 名前を取得
	/// </summary>
	/// <returns></returns>
	const char* GetName() {
		return collname;
	}

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 形状タイプ取得
	/// </summary>
	/// <returns></returns>
	inline CollisionShapeType GetShapeType()
	{
		return shapeType;
	}

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	inline void OnCollision(const CollisionInfo& info)
	{
		object3d->OnCollision(info);
	}

	/// <summary>
	/// //衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	inline void OffCollision(const CollisionInfo& info)
	{
		object3d->OffCollision(info);
	}

protected:
	Object3d* object3d = nullptr;
	//形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	//衝突先クラス名
	const char* collname = nullptr;
};