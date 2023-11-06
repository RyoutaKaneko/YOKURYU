/**
 * @file GameScene.h
 * @brief ゲームのメイン部分一番重要
 * @author カネコ_リョウタ
 */

#include "GameScene.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "GameSceneManager.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <map>

std::list<std::unique_ptr<Energy>> GameScene::energys_;
int GameScene::popEnergyCount = 0;
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player;
}

///-----変数の初期化-----///
void GameScene::Initialize() {
	//基盤
	dxCommon_ = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	//当たり判定
	collisionManager = CollisionManager::GetInstance();

	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));

	//モデル読み込み
	skyModel = Model::LoadFromOBJ("sky");
	seaModel = Model::LoadFromOBJ("sea");
	block01Model = Model::LoadFromOBJ("block01");
	block02Model = Model::LoadFromOBJ("block02");
	stoneModel = Model::LoadFromOBJ("stone");
	models.insert(std::make_pair("sky", skyModel));
	models.insert(std::make_pair("sea", seaModel));
	models.insert(std::make_pair("block01", block01Model));
	models.insert(std::make_pair("block02", block02Model));
	models.insert(std::make_pair("stone", stoneModel));
	//レベルエディタ読み込み
	LoadObjFromLevelEditor("scene");

	//レールカメラ
	railCamera = new RailCamera;
	railCamera->Initialize(player);

	xmViewProjection = new XMViewProjection;

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon_->GetDevice());

	//クロスヘアの画像
	for (int i = 0; i < 4; i++) {
		crosshair[i].LoadTexture(spriteCommon_, 0, L"Resources/crosshair.png", dxCommon_->GetDevice());
		crosshair[i].SpriteCreate(dxCommon_->GetDevice(), 0, Vector2(0.5f, 0.5f), false, false);
		crosshair[i].SetPosition(Vector3(1100, 0, 0));
		crosshair[i].SetScale(Vector2(24.0f * (i + 1.0f), 24.0f * (i + 1.0f)));
		crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 0);
		crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
	}

	for (int i = 0; i < 10; i++) {
		lock[i].LoadTexture(spriteCommon_, 1, L"Resources/crosshair.png", dxCommon_->GetDevice());
		lock[i].SpriteCreate(dxCommon_->GetDevice(), 1, Vector2(0.0f, 0.0f), false, false);
		lock[i].SetScale(Vector2(128 * 1, 128 * 1));
		lock[i].SpriteTransferVertexBuffer(lock[i], 1);
		lock[i].SpriteUpdate(lock[i], spriteCommon_);
	}

	//fade
	fade.LoadTexture(spriteCommon_, 2, L"Resources/black.png", dxCommon_->GetDevice());
	fade.SpriteCreate(dxCommon_->GetDevice(), 2, Vector2(0.0f, 0.0f), false, false);
	fade.SetScale(Vector2(1280 * 1, 720 * 1));
	fade.SpriteTransferVertexBuffer(fade, 2);
	fade.SpriteUpdate(fade, spriteCommon_);
	//alpha
	fadeAlpha = 1.0f;
	fade.SetAlpha(fade, fadeAlpha);
	//boosHP
	bossHP.LoadTexture(spriteCommon_, 3, L"Resources/hp.png", dxCommon_->GetDevice());
	bossHP.SpriteCreate(dxCommon_->GetDevice(), 3, Vector2(0.0f, 0.5f), false, false);
	bossHP.SetPosition(Vector3(25, 50, 0));
	bossHP.SetScale(Vector2(2 * 1, 48 * 1));
	bossHP.SpriteTransferVertexBuffer(bossHP, 3);
	bossHP.SpriteUpdate(bossHP, spriteCommon_);
	
	//フェードアウト
	fadeout.SpriteCreate(dxCommon_->GetDevice(), 4, Vector2(0.0f, 0.0f), false, true);
	fadeout.SetScale(Vector2(1280 * 1, 1120 * 1));
	fadeout.SetPosition({ 0,720,0 });
	fadeout.SpriteTransferVertexBuffer(fadeout, 4);
	fadeout.SpriteUpdate(fadeout, spriteCommon_);
	fadeout.LoadTexture(spriteCommon_, 4, L"Resources/fade.png", dxCommon_->GetDevice());

	//UI初期化
	UIs = new GameSceneUI();
	UIs->Initialize(dxCommon_->GetDevice());

	//パーティクル初期化
	particle = Particle::LoadParticleTexture("blue.png");
	pm = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm->SetParticleModel(particle);
	//カメラをセット
	pm->SetXMViewProjection(xmViewProjection);

	//boss
	boss = new Boss;
	boss->BossInitialize();
	boss->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 10.0f));


	//スプライン制御点の読み込み
	stageNum = 1;
	LoadStage();
	LoadEnemy();
	//変数
	isCheckPoint = false;
	isPlayable = false;
	gameState = MAIN;
	infos.clear();
	gameTime = 150;
	cursorRotate = 0.001f;
	bossPass = 0;
	cameraTmpPos = { 0,0,0 };
	cameraTmpRot = { 0,0,0 };
	isStart = false;
}

///-----更新処理-----///
void GameScene::Update() {
	//クロスヘアを更新
	GetCrosshair();
	//リセット
	if (Input::GetInstance()->TriggerKey(DIK_R)) {
		Reset();
		gameState = MAIN;
		gameTime = 150;
		railCamera->GetView()->SetEye(Vector3(-1, 0.5f, 490.0f));
		railCamera->GetView()->SetTarget(Vector3(0.0f, 0.5f, 495));
		player->SetPosition({ 0,0.5f,495 });
		Vector3 cursor = GetWorldToScreenPos(Vector3(0, 0, 0), railCamera);
		input->SetMousePos({ cursor.x,cursor.y });
	}
	if (isStart == false) {
		fadeAlpha = 0.0f;
		fade.SetAlpha(fade, fadeAlpha);
		gameTime = 150;
		railCamera->GetView()->SetEye(Vector3(-1, 0.5f, 490.0f));
		railCamera->GetView()->SetTarget(Vector3(0.0f, 0.5f, 495));
		player->SetPosition({ 0,0.5f,495 });
		Vector3 cursor = GetWorldToScreenPos(Vector3(-230, 85, 0), railCamera);
		input->SetMousePos({ cursor.x,cursor.y });
		for (auto& object : objects) {
			object->Update();
		}
		isStart = true;
	}
	//メインゲーム開始時フェードアウト
	if (fadeout.GetPosition().y < 18200) {
		fadeout.SetPosition(fadeout.GetPosition() + Vector3(0, 40, 0));
		fadeout.SpriteUpdate(fadeout, spriteCommon_);
	}

	Vector3 shotVec = { 0,0,0 };

	//メインゲーム中
	switch (gameState)
	{
		//メインゲーム
	case GameScene::MAIN:
		//ゲームスタート時演出
		if (gameTime > 0) {
			//SPACEで演出スキップ
			if (Input::GetInstance()->TriggerKey(DIK_SPACE) || Input::GetInstance()->TriggerMouseLeft()) {
				gameTime = 1;
				UIs->SkipUIPos();
			}
			//UI表示
			if (gameTime <= 50) {
				UIs->ShowUI();
			}
			railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + Vector3(0, 0.0f, 0.05f));
			gameTime--;
			if (gameTime <= 0) {
				player->SetPosition(Vector3(0, -1.0f, -5.5f));
				player->SetAlpha(0.0f);
			}
			player->GetWorldTransform().UpdateMatrix();
		}
		//ゲーム中
		if (gameTime == 0) {
			//操作不可状態を解除
			if (isPlayable == false) {
				isPlayable = true;
			}
			//boss戦へ
			if (railCamera->GetOnRail() == false) {
				if (isCheckPoint == false) {
					isCheckPoint = true;
					boss->Pop();
					gameState = BOSS;
					delete railCamera;
					railCamera = new RailCamera;
					railCamera->Initialize(player);
				}
			}
			/////デバック用(ボスまでスキップ)/////
			if (input->TriggerKey(DIK_B)) {
				railCamera->SetOnRail(false);
			}

			//player更新(カメラの前)
			if (input->PushMouseLeft()) {
				shotVec = GetScreenToWorldPos(crosshair[0], railCamera);
			}
			if (isPlayable == true) {
				SerchEnemy();
				player->Update(shotVec, infos);
				if (gameState == BOSS && railCamera->GetOnRail() == true) {
					player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				}
				LockedClear();
			}
			//デスフラグの立った敵を削除
			enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
				return enemy_->GetIsDead();
				});
			//敵キャラの更新
			for (const std::unique_ptr<Enemy>& enemy_ : enemys_) {
				enemy_->Update(player->GetWorldPos(), railCamera->GetPasPoint());
			}
			//更新
			railCamera->Update(player, points);
			//ダメージをくらったときに画面シェイク
			if (player->GetIsHit() == true) {
				railCamera->ShakeCamera(-0.2f, 0.2f);
			}
		}
		break;
		//ボス戦
	case GameScene::BOSS:
		if (boss->GetTimer() > 0) {
			player->SetIsHit(false);
			//playerを操作不可に
			if (isPlayable == true) {
				isPlayable = false;
				railCamera->GetView()->SetEye(Vector3(-40, 55, -150));
			}
			//SPACEで演出スキップ
			if (input->TriggerKey(DIK_SPACE)) {
				boss->SkipMovie();
			}
			//演出
			railCamera->GetView()->SetTarget(boss->GetPosition());
			if (boss->GetTimer() == 150) {
				railCamera->GetView()->SetEye(Vector3(-80, 55, -300));
			}
			else if (boss->GetTimer() < 150) {
				railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + Vector3(0.5f, 0.0f, 0.05f));
			}
		}
		else {
			//操作可能状態に
			if (isPlayable == false) {
				railCamera->GetView()->SetEye(Vector3(0, 60, -95));
				railCamera->GetView()->SetTarget(Vector3(0, 52, -200));
				railCamera->GetCamera()->SetPosition(Vector3(0, 59, -100));
				railCamera->GetCamera()->SetRotation(Vector3(0, 180, 0));
				player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				fadeAlpha = 1.0f;
				fade.SetAlpha(fade, fadeAlpha);
				isPlayable = true;
			}
			//BossHP
			float bossHp_ = boss->GetHP() - (bossHP.GetScale().x / 4);
			if (bossHp_ > 0) {
				if ((bossHp_) > 4) {
					bossHP.SetScale(bossHP.GetScale() + Vector2(16.0f, 0.0f));
				}
				else if ((bossHp_) > 2) {
					bossHP.SetScale(bossHP.GetScale() + Vector2(8.0f, 0.0f));
				}
				else if ((bossHp_) > 1) {
					bossHP.SetScale(bossHP.GetScale() + Vector2(4.0f, 0.0f));
				}
			}
			else if (bossHp_ < 0) {
				if ((bossHp_) < 4) {
					bossHP.SetScale(bossHP.GetScale() - Vector2(8.0f, 0.0f));
				}
				else if ((bossHp_) < 2) {
					bossHP.SetScale(bossHP.GetScale() - Vector2(4.0f, 0.0f));
				}
				else if ((bossHp_) < 1) {
					bossHP.SetScale(bossHP.GetScale() - Vector2(2.0f, 0.0f));
				}
			}
			bossHP.SpriteTransferVertexBuffer(bossHP, 6);
			bossHP.SpriteUpdate(bossHP, spriteCommon_);
			//player更新(カメラの前)
			if (input->PushMouseLeft()) {
				shotVec = GetScreenToWorldPos(crosshair[0], railCamera);
			}
			if (isPlayable == true) {
				SerchEnemy();
				player->Update(shotVec, infos);
				if (gameState == BOSS && railCamera->GetOnRail() == true) {
					player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				}
				LockedClear();
			}

			//カメラ更新
			if (railCamera->GetOnRail() == false) {
				gameTime++;
				if (gameTime == 300) {
					railCamera->SetOnRail(true);
					gameTime = 0;
				}
			}
			railCamera->Update(player, bossPoint);
			railCamera->GetView()->SetTarget(boss->GetPosition());
			railCamera->GetCamera()->SetRotation(railCamera->GetView()->GetTarget());
			//カメラ制御
			if (bossPass == 0) {
				if (railCamera->GetPasPoint() + 1.0f > 3.0f) {
					railCamera->SetOnRail(false);
					bossPass = 1;
				}
			}
			else if (bossPass == 1) {
				if (railCamera->GetPasPoint() + 1.0f > 5.0f) {
					railCamera->SetOnRail(false);
					bossPass = 2;
				}
			}
			else if (bossPass == 2) {
				if (railCamera->GetPasPoint() + 1.0f > 7.0f) {
					railCamera->SetOnRail(false);
					bossPass = 3;
				}
			}
			else if (bossPass == 3) {
				if (railCamera->GetPasPoint() + 1.0f >= 8.96f) {
					railCamera->SetOnRail(false);
					railCamera->RailReset();
					bossPass = 0;
				}
			}
		}
		//fadein
		if (fadeAlpha > 0.0f) {
			fadeAlpha -= 0.005f;
			fade.SetAlpha(fade, fadeAlpha);
		}
		//gameclear
		if (boss->GetIsDead() == true) {
			LockedClear();
			GameSceneManager::GetInstance()->ChangeScene("CLEAR");
		}
		//更新
		boss->Update(player->GetWorldPos());
		//ダメージをくらったときに画面シェイク
		if (player->GetIsHit() == true) {
			railCamera->ShakeCamera(-2.0f, 2.0f);
		}
		break;
	case GameScene::ULT:
		if (isPlayable == true) {
			isPlayable = false;
		}
		player->Ultimate();
		railCamera->SetTarget(player->GetWorldPos());
		if (player->GetIsUltimate() == false) {
			player->BackRail();
			railCamera->SetEye(cameraTmpPos);
			railCamera->SetTarget(cameraTmpRot);
			gameState = gameState_bak;
		}
		break;

	case GameScene::CONTINUE:
		player->Dead();
		UIs->DeadUIPos();
		railCamera->ViewUpdate();
		if (player->GetDeathTimer() >= 100) {
			UIs->ContinueText();

			if (UIs->GetIsGameSceneReset() == true) {
				Reset();
				gameState = MAIN;
				gameTime = 150;
				railCamera->GetView()->SetEye(Vector3(-1, 0.5f, 490.0f));
				railCamera->GetView()->SetTarget(Vector3(0.0f, 0.5f, 495));
				player->SetPosition({ 0,0.5f,495 });
				Vector3 cursor = GetWorldToScreenPos(Vector3(0, 0, 0), railCamera);
				input->SetMousePos({ cursor.x,cursor.y });
				fadeAlpha = 0.0f;
				fade.SetAlpha(fade, fadeAlpha);
			}
			if (UIs->GetIsGameOver() == true) {
				fadeAlpha += 0.05f;
				fade.SetAlpha(fade, fadeAlpha);
				fade.SpriteUpdate(fade,spriteCommon_);
				if (fadeAlpha >= 1.0f) {
					GameSceneManager::GetInstance()->ChangeScene("OVER");
				}
			}
		}
		break;
	}
	//////////////操作可能なら更新///////////////////
	if (player->GetIsUltimate() == true && gameState != ULT) {
		cameraTmpPos = railCamera->GetView()->GetEye();
		cameraTmpRot = railCamera->GetView()->GetTarget();
		railCamera->SetEye(player->GetWorldPos() + Vector3(-2, 0, -3));
		railCamera->SetTarget(player->GetWorldPos());
		gameState_bak = gameState;
		gameState = ULT;
	}
	//必殺技エネルギー
	for (const std::unique_ptr<Energy>& energy : energys_) {
		energy->Update(player->GetWorldPos(), railCamera->GetCamera()->GetRotation());
	}
	//UI表示
	UIAlpha();
	UIs->Update(isPlayable, player);
	//デスフラグの立ったエネルギーを削除
	energys_.remove_if([](std::unique_ptr <Energy>& energys) {
		return energys->GetIsDead();
		});
	//gameover
	if (player->GetHP() <= 0) {
		LockedClear();
		gameState = CONTINUE;
	}

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		Vector3 pap = player->GetPosition();
		pm->Fire(particle, {-20,0,0},1, 0.5f, 0, 15, { 5,0 });
	}
	pm->Update();

	//当たり判定チェック
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw() {
#pragma region 3Dオブジェクト描画

	dxCommon_->PreDraw();

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());

	//背景オブジェクト
	for (auto& object : objects) {
		object->Draw(railCamera->GetView());
	}
	//敵キャラの描画
	for (const std::unique_ptr<Enemy>& enemy_ : enemys_) {
		enemy_->EnemyDraw(railCamera->GetView());
	}
	for (const std::unique_ptr<Energy>& energy : energys_) {
		energy->Draw(railCamera->GetView());
	}
	//ボス
	if (gameState == BOSS) {
		boss->BossDraw(railCamera->GetView());
	}
	//プレイヤー
	player->PlayerDraw(railCamera->GetView());

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion

#pragma region FBX3Dオブジェクト描画

#pragma endregion

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon_->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル
	pm->Draw();

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon_->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///

	if (gameState == BOSS) {
		fade.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		if (boss->GetTimer() == 0) {
			//ボスのHP
			bossHP.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
	}
	Sprite::PostDraw();

	UIs->Draw(dxCommon_->GetDevice(), dxCommon_->GetCommandList()); 
	if (gameState == CONTINUE && player->GetDeathTimer() >= 100) {
		UIs->DrawContinue(dxCommon_->GetDevice(), dxCommon_->GetCommandList());
	}

	Sprite::PreDraw(dxCommon_->GetCommandList(), spriteCommon_);
	if (isPlayable == true && gameState != CONTINUE) {
		for (int i = 0; i < 4; i++) {
			crosshair[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
	}
	for (int i = 0; i < infos.size(); i++) {
		lock[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	fadeout.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());

	if (gameState == CONTINUE) {
		fade.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	// スプライト描画後処理
	Sprite::PostDraw();

	dxCommon_->PostDraw();
}

void GameScene::LoadStage() {
	points.clear();
	bossPoint.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/stagePop.csv");
	assert(file.is_open());

	std::string num;
	num = "1";

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');


		// 先頭文字列がstならステージ
		if (key == "st") {
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			points.emplace_back(position);
		}
		//先頭文字がboならボス
		if (key == "bo") {
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			bossPoint.emplace_back(position);
		}
	}
	// ファイルと閉じる
	file.close();
}

void GameScene::Reset() {
	delete player;
	delete railCamera;
	delete enemy;
	delete boss;

	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));
	player->SetPosition({ 0,0.5f,495 });
	player->ResetHP();
	//boss
	boss = new Boss;
	boss->BossInitialize();
	boss->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 10.0f));
	bossHP.SetScale(Vector2(12 * 1, 48 * 1));
	//camera
	railCamera = new RailCamera;
	railCamera->Initialize(player);
	//enemy
	LoadEnemy();
	//変数
	isCheckPoint = false;
	isPlayable = false;
	cursorRotate = 0.001f;
	LockedClear();
	infos.clear();
	gameState = MAIN;
	gameTime = 150;
	bossPass = 0;
	fadeAlpha = 1.0f;
	fade.SetAlpha(fade, fadeAlpha);
	popEnergyCount = 0;
	//UI
	UIs->ResetUIPos();
}

void GameScene::Finalize()
{
}

void GameScene::LoadEnemy() {

	Spline spline;
	spline.Initialize();

	pointsL = points;
	pointsR = points;

	for (int i = 0; i < points.size(); i++)
	{
		pointsL[i] += Vector3(-2, 0, 0);
		pointsR[i] += Vector3(2, 0, 0);
	}

	enemys_.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/EnemyPop.csv");
	assert(file.is_open());


	std::string num;
	num = "0";

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');

		string word;
		getline(line_stream, word, ' ');

			// 先頭文字列がｖなら頂点座標
			if (key == "ea") {
				//敵の生成
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				//敵の初期化
				newEnemy->EnemyInitialize();
				////コライダーの追加
				newEnemy->SetCollider(new SphereCollider());
				// X,Y,Z座標読み込み
				Vector3 position{};
				float t;

				if (word.find("L") == 0)
				{
					line_stream >> t;
					newEnemy->SetStagePoint(t);
					position = spline.EnemyPosition(pointsL, t);
				}
				else if (word.find("M") == 0)
				{
					line_stream >> t;
					newEnemy->SetStagePoint(t);
					position = spline.EnemyPosition(points, t);
				}
				else if (word.find("R") == 0)
				{
					line_stream >> t;
					newEnemy->SetStagePoint(t);
					position = spline.EnemyPosition(pointsR, t);
				}

				// 座標データに追加
				newEnemy->SetPosition(position);
				newEnemy->SetScale({ 0.6f,0.6f,0.6f });
				//登録
				enemys_.push_back(std::move(newEnemy));
			}
	}
	// ファイルと閉じる
	file.close();
}

void GameScene::SerchEnemy()
{
	Vector3 cur = input->GetMousePos();

	if (input->PushMouseRight()) {
		for (int i = 0; i < boss->GetPartsNum(); i++) {
			Vector3 epos1 = GetWorldToScreenPos(boss->GetParts(i)->GetWorldPos(), railCamera);
			if (boss->GetIsInvisible() == false) {
				if (pow((epos1.x - cur.x), 2) + pow((epos1.y - cur.y), 2) < pow(50, 2)) {
					if (boss->GetParts(i)->GetIsLocked() == false && infos.size() < 10) {
						LockInfo info;
						info.vec = boss->GetParts(i)->GetWorldPos();
						info.obj = boss->GetParts(i);
						infos.push_back(info);
						boss->GetParts(i)->SetIsLocked(true);
					}
				}
			}
		}

		for (const std::unique_ptr<Enemy>& enemy_ : enemys_) {
			Vector3 epos2 = GetWorldToScreenPos(enemy_->GetWorldPos(), railCamera);
			Vector3 len = enemy_->GetWorldPos() - player->GetWorldPos();
			if (pow((epos2.x - cur.x), 2) + pow((epos2.y - cur.y), 2) < pow(30, 2)) {
				if (enemy_->GetIsLocked() == false && infos.size() < 10) {
					LockInfo info;
					info.vec = enemy_->GetWorldPos();
					info.obj = enemy_->GetPointer();
					infos.push_back(info);
					enemy_->SetIsLocked(true);
				}
			}
		}
		if (cursorRotate < 0.005f) {
			cursorRotate += 0.0001f;
		}
	}
	else {
		if (cursorRotate > 0.001f) {
			cursorRotate -= 0.0001f;
		}
	}
	//ロックオン画像の更新
	for (int i = 0; i < infos.size(); i++) {
		lock[i].SetScale(GetWorldToScreenScale(infos[i].obj, railCamera));
		lock[i].SetPosition(GetWorldToScreenPos(infos[i].obj->GetWorldPos(), railCamera) - (Vector3(lock[i].GetScale().x, lock[i].GetScale().y, 0) / 2));
		lock[i].SpriteUpdate(lock[i], spriteCommon_);
		lock[i].SpriteTransferVertexBuffer(lock[i], 1);
	}
}

void GameScene::LockedClear()
{
	if (player->GetIsShooted() == true) {
		if (boss->GetIsLocked() == true) {
			boss->SetIsLocked(false);
		}

		for (const std::unique_ptr<Enemy>& enemy_ : enemys_) {
			if (enemy_->GetIsLocked() == true) {
				enemy_->SetIsLocked(false);
			}
		}
		infos.clear();
	}
}

void GameScene::GetCrosshair()
{
	Vector3 mPos = input->GetMousePos();
	//マウスカーソルの場所にクロスヘアを表示
	if (gameState == MAIN) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				crosshair[i].SetPosition(mPos);
			}
			else if (i == 1) {
				crosshair[i].SetPosition(mPos - (mPos - GetWorldToScreenPos(player->GetWorldPos(), railCamera)) * 0.1f);
			}
			else if (i == 2) {
				crosshair[i].SetPosition(mPos - (mPos - GetWorldToScreenPos(player->GetWorldPos(), railCamera)) * 0.25f);
			}
			else if (i == 3) {
				crosshair[i].SetPosition(mPos - (mPos - GetWorldToScreenPos(player->GetWorldPos(), railCamera)) * 0.55f);
			}
			if (i % 2 == 0) {
				crosshair[i].SetRotation(crosshair[i].GetRotation() + cursorRotate);
			}
			else {
				crosshair[i].SetRotation(crosshair[i].GetRotation() - cursorRotate);
			}
			if (crosshair[i].GetRotation() == 1.0f) {
				crosshair[i].SetRotation(0.0f);
			}
			crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
			crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			crosshair[i].SetPosition(mPos);
			if (i % 2 == 0) {
				crosshair[i].SetRotation(crosshair[i].GetRotation() + cursorRotate);
			}
			else {
				crosshair[i].SetRotation(crosshair[i].GetRotation() - cursorRotate);
			}
			if (crosshair[i].GetRotation() == 1.0f) {
				crosshair[i].SetRotation(0.0f);
			}
			crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
			crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
		}
	}
}

void GameScene::PopEnergy(Vector3 pos_)
{
	//乱数生成装置
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(-1.5f, 1.5f);
	std::uniform_real_distribution<float>dist2(-2.5f, 2.5f);
	std::uniform_real_distribution<float>dist3(-1.5f, 1.5f);
	//弾を生成し初期化
	std::unique_ptr<Energy> newEnergy = std::make_unique<Energy>();

	//単発													   
	newEnergy->EnergyInitialize();
	newEnergy->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 2.0f));
	newEnergy->SetPosition(pos_ + Vector3(dist(engine), dist2(engine), dist3(engine)));
	energys_.push_back(std::move(newEnergy));
}

void GameScene::UIAlpha()
{
	Vector3 hpPos = UIs->GetHPFramePos();
	Vector3 pPos = GetWorldToScreenPos(player->GetWorldPos(), railCamera);
		if ((pPos.x > hpPos.x - 284.0f && pPos.x < hpPos.x + 284.0f)) {
			if ((pPos.y > hpPos.y - 70.5f && pPos.y < hpPos.y + 70.5f)) {
				UIs->SetHPAlpha(true);
		}
			else {
				UIs->SetHPAlpha(false);
			}
	}
		else {
			UIs->SetHPAlpha(false);
		}
}

Vector3 GameScene::GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector3(0, 0, 1);
	}

	//ビューポート行列生成
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width, WinApp::window_height, Vector2(0.0f, 0.0f));

	//ビュープロジェクションビューポート合成行列
	Matrix4 invViewPort = viewPort;
	invViewPort.MakeInverse();
	//プロジェクション行列//
	float fovAngleY = 45.0f * (3.141592f / 180.0f);;
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	//プロジェクション行列生成
	Matrix4 projection = projection.ProjectionMat(fovAngleY, aspectRatio, 0.1f, 200.0f);
	Matrix4 invProjection = projection;
	invProjection.MakeInverse();
	//ビュー行列//
	Matrix4 view = railCamera->GetView()->GetMatView();
	Matrix4 invView = view;
	invView.MakeInverse();
	////合成行列の逆行列を計算する
	Matrix4 matInverseVPV = invViewPort * invProjection * invView;
	//スクリーン座標系からワールド座標系
	Matrix4 mat1, mat2;
	//w除算
	Vector3 posNear = Vector3(sprite_.GetPosition().x, sprite_.GetPosition().y, 0);
	Vector3 posFar = Vector3(sprite_.GetPosition().x, sprite_.GetPosition().y, 1);
	posNear = mat1.transform(posNear, matInverseVPV);
	posFar = mat2.transform(posFar, matInverseVPV);

	//マウスレイの方向
	Vector3 mouseDirection = posFar - posNear;
	mouseDirection = mouseDirection.normalize();
	//カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 0.05f;

	Vector3 pos = player->GetWorldPos();
	Vector3 translate = (posFar - pos) * kDistanceTestObject;

	return translate;
}

Vector3 GameScene::GetWorldToScreenPos(Vector3 pos_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector3(0, 0, 0);
	}

	//ビュー行列//
	Matrix4 view = railCamera->GetView()->GetMatView();
	//プロジェクション行列//
	float fovAngleY = 45.0f * (3.141592f / 180.0f);;
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	//プロジェクション行列生成
	Matrix4 projection = projection.ProjectionMat(fovAngleY, aspectRatio, 0.1f, 200.0f);
	//ビューポート行列生成
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width, WinApp::window_height, Vector2(0.0f, 0.0f));

	Matrix4 matVPV = view * projection * viewPort;

	Matrix4 mat;
	Vector3 posScreen = pos_;
	posScreen = mat.transform(posScreen, matVPV);
	posScreen.z = 0;

	return posScreen;
}

Vector2 GameScene::GetWorldToScreenScale(Object3d* obj_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector2(0, 0);
	}

	Vector3 v = obj_->GetPosition() - rail->GetView()->GetEye();
	v.normalize();
	float len = v.length();

	float x = 64;
	x *= obj_->GetScale().x;
	float y = 64;
	y *= obj_->GetScale().y;


	return Vector2(x / len, y / len);
}