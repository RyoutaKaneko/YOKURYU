/**
 * @file Collision.cpp
 * @brief 当たり判定の関数をまとめたクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "CollisionPrimitive.h"

class Collision
{
public:
	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphereA">球A</param>
	/// <param name="sphereB">球B</param>
	/// <param name="inter">衝突点</param>
	/// <param name="reject">衝突</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, Vector3* inter = nullptr, Vector3* reject = nullptr);
	
	/// <summary>
	/// 球と平面の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">衝突点</param>
	/// <returns></returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);

	/// <summary>
	/// //点と三角形の最近接点を求める
	/// </summary>
	/// <param name="point">点の位置</param>
	/// <param name="triangle">三角形</param>
	/// <param name="closest">最近位置</param>
	static void ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest);

	/// <summary>
	/// 球と法線付き三角形の当たりチェック
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="triangle">法線付き三角形</param>
	/// <param name="inter">衝突点</param>
	/// <param name="reject">衝突</param>
	/// <returns></returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter = nullptr, Vector3* reject = nullptr);

	/// <summary>
	/// レイと平面の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="distance">距離</param>
	/// <param name="inter">衝突点</param>
	/// <returns></returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, Vector3* inter = nullptr);

	/// <summary>
	/// レイと法線付き三角形の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="triangle">法線付き三角形</param>
	/// <param name="distance">距離</param>
	/// <param name="inter">衝突点</param>
	/// <returns></returns>
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, Vector3* inter = nullptr);

	/// <summary>
	/// レイと球の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="sphere">球</param>
	/// <param name="distance">距離</param>
	/// <param name="inter">衝突点</param>
	/// <returns></returns>
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, Vector3* inter = nullptr);
};

