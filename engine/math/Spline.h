/**
 * @file Spline.cpp
 * @brief 曲線補間クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Vector3.h"
#include <Vector>

class Spline 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="points">spline制御点</param>
	/// <param name="val"> 加速度</param>
	/// <returns></returns>
	Vector3 Update(std::vector<Vector3>& points,float val);

	/// <summary>
	/// 敵位置の計算
	/// </summary>
	/// <param name="points">spline制御点</param>
	/// <param name="val">加速度</param>
	/// <returns></returns>
	Vector3 LinePosition(std::vector<Vector3>& points, float val);

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// 曲線補完
	/// </summary>
	/// <param name="point">spline制御点</param>
	/// <param name="startIndex">補間する区間の添字</param>
	/// <param name="t">時間経過率</param>
	/// <returns></returns>
	Vector3 SplinePosition(const std::vector<Vector3>& point, size_t startIndex, float t);

	/// <summary>
	/// 制御点の最後まで行ったかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsEnd() { return isEnd; }

	/// <summary>
	/// 時間経過率取得
	/// </summary>
	/// <returns></returns>
	float GetT() { return t + integer; }

private:
	//P1からスタートする
	size_t startIndex = 1;
	bool isEnd = false;
	float t = 0;
	float integer = 0;


	//球の位置
	Vector3 position;
};