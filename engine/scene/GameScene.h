#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "time.h"
#include <random>
#include "Model.h"
#include "ViewProjection.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "FbxObject3d.h"
#include "FbxModel.h"
#include "Player.h"
#include "RailCamera.h"
#include "Enemy.h"
#include "CollisionManager.h"


class GameScene {
public:
	//メンバ関数
	GameScene();

	~GameScene();

	void Initialize(SpriteCommon& spriteCommon);

	void Update();

	void Draw();
	void Reset();

	void LoadStage(int stageNum);
	void LoadEnemy(int stageNum);

	Vector3 GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail);

private:
	//base
	DirectXCommon* dxCommon = nullptr;
	WinApp* winApp = nullptr;
	//入力のポインタ
	Input* input = nullptr;
	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite wood;
	Sprite reimu;
	Sprite hp[5];
	//オブジェクトのポインタ
	//3Dオブジェクト生成
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Model* skyModel = nullptr;
	Object3d* sky = nullptr;
	Model* floorModel = nullptr;
	Object3d* floor = nullptr;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	//パーティクル
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* particle_ = nullptr;
	ParticleManager* pm_ = nullptr;
	//enemy
	std::list<std::unique_ptr<Enemy>> enemys_;
	//当たり判定
	CollisionManager* collisionManager = nullptr;
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* obj = nullptr;
	//カメラ移動用レール
	std::vector<Vector3> points{};
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;
	//ステージ
	int stageNum = 0;
	

};