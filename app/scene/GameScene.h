/**
 * @file GameScene.cpp
 * @brief ゲームのメイン部分一番重要
 * @author カネコ_リョウタ
 */

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
#include "Boss.h"
#include "JsonLoader.h"	
#include "energy.h"
#include "GameBaseScene.h"


class GameScene : public GameBaseScene {
public:
	//メンバ関数
	GameScene();

	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// ステージ読み込み
	/// </summary>
	void LoadStage();

	/// <summary>
	/// 敵読み込み
	/// </summary>
	void LoadEnemy();

	/// <summary>
	/// 索敵
	/// </summary>
	void SerchEnemy();

	/// <summary>
	/// ロックオン情報クリア
	/// </summary>
	void LockedClear();

	/// <summary>
	/// クロスヘアを取得
	/// </summary>
	void GetCrosshair();

	/// <summary>
	/// エネルギー出現
	/// </summary>
	/// <param name="pos_">座標</param>
	static void PopEnergy(Vector3 pos_);

	/// <summary>
	/// スクリーン座標からワールド座標に
	/// </summary>
	/// <param name="sprite_">スプライト</param>
	/// <param name="rail">レールカメラ</param>
	/// <returns></returns>
	Vector3 GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail);

	/// <summary>
	/// ワールド座標からスクリーン座標に
	/// </summary>
	/// <param name="pos_">座標</param>
	/// <param name="rail">レールカメラ</param>
	/// <returns></returns>
	Vector3 GetWorldToScreenPos(Vector3 pos_, RailCamera* rail);

	/// <summary>
	/// ワールド座標のオブジェクトに合わせてスクリーン座標のスプライトのスケールを取得
	/// </summary>
	/// <param name="obj">オブジェクト</param>
	/// <param name="rail">レールカメラ</param>
	/// <returns></returns>
	Vector2 GetWorldToScreenScale(Object3d* obj, RailCamera* rail);

private:
	//base
	DirectXCommon* dxCommon_ = nullptr;
	WinApp* winApp = nullptr;
	//入力のポインタ
	Input* input = nullptr;
	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite titleGH;
	Sprite crosshair[4];
	Sprite hp;
	Sprite clearGH;
	Sprite overGH;
	Sprite lock[10];
	Sprite fade;
	float fadeAlpha;
	Sprite bossHP;
	Sprite gage;
	Sprite gageBack;
	Sprite hpBack;
	Sprite fadeout;
	Sprite hpFrame;
	//オブジェクトのポインタ
	//3Dオブジェクト生成
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Model* skyModel = nullptr;
	Model* seaModel = nullptr;
	Model* block01Model = nullptr;
	Model* block02Model = nullptr;
	Model* stoneModel = nullptr;
	Boss* boss = nullptr;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	Vector3 cameraTmpPos;
	Vector3 cameraTmpRot;
	//パーティクル
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* particle_ = nullptr;
	ParticleManager* pm_ = nullptr;
	//enemy
	std::list<std::unique_ptr<Enemy>> enemys_;
	//energy
	static std::list<std::unique_ptr<Energy>> energys_;
	static int popEnergyCount;
	//当たり判定
	CollisionManager* collisionManager = nullptr;
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* obj = nullptr;
	//カメラ移動用レール
	std::vector<Vector3> points{};
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;
	std::vector<Vector3> bossPoint{};
	//ステージ
	int stageNum = 0;
	bool isCheckPoint = false;
	bool isPlayable = false;
	//ロックオン情報
	std::vector<LockInfo> infos;
	int gameTime;
	float cursorRotate;
	//ゲームステータス
	enum GameState {
		MAIN,
		BOSS,
		ULT
	};
	GameState gameState;
	GameState gameState_bak;
	int bossPass;
	bool isStart;
};