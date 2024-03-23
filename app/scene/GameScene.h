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
#include "GameSceneUI.h"
#include "GameSceneConst.h"
#include "BombEnemy.h"


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
	/// スクリーン座標からワールド座標に
	/// </summary>
	/// <param name="sprite_">スプライト</param>
	/// <param name="rail">レールカメラ</param>
	/// <returns></returns>
	Vector3 GetScreenToWorldPos(const Sprite& sprite_, MyEngine::RailCamera* rail);

	/// <summary>
	/// ワールド座標からスクリーン座標に
	/// </summary>
	/// <param name="pos_">座標</param>
	/// <param name="rail">レールカメラ</param>
	/// <returns></returns>
	Vector3 GetWorldToScreenPos(const Vector3& pos_, MyEngine::RailCamera* rail);

	/// <summary>
	/// ワールド座標のオブジェクトに合わせてスクリーン座標のスプライトのスケールを取得
	/// </summary>
	/// <param name="obj">オブジェクト</param>
	/// <param name="rail">レールカメラ</param>
	/// <returns></returns>
	Vector2 GetWorldToScreenScale(Object3d* obj, MyEngine::RailCamera* rail);

	/// <summary>
	///  クリア更新
	/// </summary>
	void ClearUpdate();

	/// <summary>
	///  ポーズ更新
	/// </summary>
	void PauseUpdate();

	/// <summary>
	/// ボス戦処理
	/// </summary>
	void BossUpdate();

	/// <summary>
	/// メインゲーム処理
	/// </summary>
	void MainUpdate();

private:
	//base
	DirectXCommon* dxCommon_ = nullptr;
	WinApp* winApp = nullptr;
	//入力のポインタ
	Input* input = nullptr;

	//定数
	static const int CROSSHAIR_MAX = 4;
	static const int LOCK_MAX = 10;
	static const int INFOS_MAX = 10;

	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	std::array <Sprite, CROSSHAIR_MAX> crosshair;
	std::array <Sprite, LOCK_MAX> lock;
	Sprite fade;
	float fadeAlpha;
	Sprite bossHP;
	Sprite fadeout;
	Sprite thanks;
	Sprite loading;
	Sprite tips;
	float thanksAlpha;
	Sprite dmg;
	float dmgAlpha;
	//UI
	MyEngine::GameSceneUI* UIs = nullptr;
	//オブジェクトのポインタ
	//3Dオブジェクト生成
	MyEngine::Player* player = nullptr;
	Model* skyModel = nullptr;
	Model* seaModel = nullptr;
	Model* block01Model = nullptr;
	Model* block02Model = nullptr;
	Model* stoneModel = nullptr;
	MyEngine::Boss* boss = nullptr;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	MyEngine::RailCamera* railCamera = nullptr;
	Vector3 cameraTmpPos;
	Vector3 cameraTmpRot;
	//パーティクル
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* clearParticle_01 = nullptr;
	ParticleManager* clearPM_01 = nullptr;
	Particle* clearParticle_02 = nullptr;
	ParticleManager* clearPM_02 = nullptr;
	Particle* clearParticle_03 = nullptr;
	ParticleManager* clearPM_03 = nullptr;

	//enemy
	std::list<std::unique_ptr<MyEngine::Enemy>> enemys_;
	std::list<std::unique_ptr<MyEngine::BombEnemy>> bombEnemys_;
	//当たり判定
	CollisionManager* collisionManager = nullptr;
	//カメラ移動用レール
	std::vector<Vector3> points{};
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;
	std::vector<Vector3> bossPoint{};
	std::vector < std::vector<Vector3> > lockPoints{};
	//ステージ
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
		ULT,
		CONTINUE,
		CLEAR,
		PAUSE
	};
	GameState gameState;
	GameState gameState_bak;
	int bossPass;
	int clearTimer;
	bool isShowUI;
	int particleTimer;
	bool isNext;
	bool isSceneEnd;
	bool isPause;
	bool isbossStart;
	int bossStartTime;
	bool isBoss;
};