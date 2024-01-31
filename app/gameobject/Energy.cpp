/**
 * @file Energy.h
 * @brief 必殺技に必要なエネルギー用クラス
 * @author カネコ_リョウタ
 */

#include "Energy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"

const Vector3 MyEngine::Energy::ROTATE = { 0,90,0 };
const Vector3 MyEngine::Energy::SUB_SCALE = { 0.01f, 0.01f, 0.01f };
const float MyEngine::Energy::MIN_SCALE = 0.01f;

void MyEngine::Energy::EnergyInitialize(const std::string &model_)
{
	Initialize();
	// OBJからモデルデータを読み込む
	energyModel = Model::LoadFromOBJ(model_);
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(energyModel);
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isDead = false;				

	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(-0.1f, 0.1f);
	std::uniform_real_distribution<float>dist2(-0.1f, 0.1f);
	randomNum = { dist(engine), dist2(engine), dist2(engine) };
}

void MyEngine::Energy::Update(const Vector3& rot)
{
	//乱数生成装置


	SetPosition(GetPosition() + randomNum);
	SetScale(GetScale() - SUB_SCALE);
	SetRotation(rot + ROTATE);

	if (GetScale().x < MIN_SCALE) {
		isDead = true;
	}

	GetWorldTransform().UpdateMatrix();
}
