/**
 * @file CollisionManager.cpp
 * @brief 当たり判定管理クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include <forward_list>
#include <d3d12.h>

class BaseCollider;

class CollisionManager
{
public://静的メンバ関数
	static CollisionManager* GetInstance();

public://メンバ関数
	/// <summary>
	/// コライダーの追加
	/// </summary>
	/// <param name="collider">コライダー</param>
	inline void AddCollider(BaseCollider* collider)
	{
		colliders.push_front(collider);
	}
	
	/// <summary>
	/// コライダーの削除
	/// </summary>
	/// <param name="collider">コライダー</param>
	inline void RemoveCollider(BaseCollider* collider)
	{
		colliders.remove(collider);
	}
	/// <summary>
	/// 全ての衝突をチェック
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// レイキャスト
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="hitInfo">判定情報</param>
	/// <param name="maxDistance">最大距離</param>
	/// <returns></returns>
	bool Raycast(const Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);
private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator = (const CollisionManager&) = delete;
	//コライダーのリスト
	std::forward_list<BaseCollider*>colliders;
};

