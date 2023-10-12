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

//GameSceneの前方宣言
class GameScene;

class Energy : public Object3d
{
public:

	void EnergyInitialize();
	
	void Update(Vector3 pos, Vector3 rot);

	void OnCollision(const CollisionInfo& info) override;

	bool GetIsDead() const { return isDead; }

private:
	// モデル
	Model* energyModel = nullptr;
	
	bool isDead;
};
