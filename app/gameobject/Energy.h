/**
 * @file Energy.cpp
 * @brief 必殺技に必要なエネルギー用クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>
#include <iostream>
#include <random>

//GameSceneの前方宣言
class GameScene;

class Energy : public Object3d
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void EnergyInitialize(const std::string& model_);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="rot">回転</param>
	void Update(Vector3 rot);

	/// <summary>
	/// 死亡フラグを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead; }

private:
	static const Vector3 ROTATE;
	static const Vector3 SUB_SCALE;
	static const float MIN_SCALE;

private:
	// モデル
	Model* energyModel = nullptr;

	std::random_device seed_gen;
	Vector3 randomNum;
	
	bool isDead;
};
