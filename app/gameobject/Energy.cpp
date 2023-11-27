/**
 * @file Energy.h
 * @brief 必殺技に必要なエネルギー用クラス
 * @author カネコ_リョウタ
 */

#include "Energy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"

void Energy::EnergyInitialize(const std::string &model_)
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

void Energy::Update(Vector3 pos,Vector3 rot)
{
	//playerのもとへ
	Vector3 velo = pos - GetPosition();
	velo = velo.normalize();
	SetPosition(GetPosition() + velo);
	SetRotation(rot + Vector3(0,90,0));

	GetWorldTransform().UpdateMatrix();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

void Energy::DeadEffect()
{
	//乱数生成装置


	SetPosition(GetPosition() + randomNum);
	Vector3 minScale(0.01f, 0.01f, 0.01f);
	SetScale(GetScale() - minScale);

	GetWorldTransform().UpdateMatrix();
}

void Energy::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class Player";

	//相手がplayerの弾
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isDead == false) {
			isDead = true;
		}
	}
}
