/**
 * @file GameScene.h
 * @brief ゲームのメイン部分一番重要
 * @author カネコ_リョウタ
 */

#include "GameScene.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "GameSceneManager.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <map>

GameScene::GameScene() {}

GameScene::~GameScene() {}

///-----変数の初期化-----///
void GameScene::Initialize() {
	//基盤
	dxCommon_ = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	//当たり判定
	collisionManager = CollisionManager::GetInstance();

	//player
	player = new MyEngine::Player;
	player->PlayerInitialize();
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));
	player->SetRotation(ROTATE_FRONT);

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
	railCamera = new MyEngine::RailCamera;
	railCamera->Initialize();
	railCamera->SetPlayer(player);
	railCamera->GetView()->SetEye(START_EYE);
	railCamera->GetView()->SetTarget(START_PLAYER);
	player->SetPosition(START_PLAYER);

	//パーティクル用
	xmViewProjection = new XMViewProjection;

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon_->GetDevice());

	//クロスヘアの画像
	for (int i = 0; i < crosshair.size(); i++) {
		crosshair[i].LoadTexture(spriteCommon_, 0, L"Resources/crosshair.png", dxCommon_->GetDevice());
		crosshair[i].SpriteCreate(dxCommon_->GetDevice(), 0, Vector2(0.5f, 0.5f), false, false);
		crosshair[i].SetPosition(Vector3(1100, 0, 0));
		crosshair[i].SetScale(Vector2(24.0f * (i + 1.0f), 24.0f * (i + 1.0f)));
		crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 0);
		crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
	}

	for (int i = 0; i < lock.size(); i++) {
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
	fadeAlpha = 0.0f;
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
	//thanks
	thanks.SpriteCreate(dxCommon_->GetDevice(), 5, Vector2(0.5f, 0.5f), false, false);
	thanks.SetScale(Vector2(832 * 1, 72 * 1));
	thanks.SetPosition({ 640,360,0 });
	thanks.SetAlpha(thanks, 0.0f);
	thanks.SpriteTransferVertexBuffer(thanks, 5);
	thanks.SpriteUpdate(thanks, spriteCommon_);
	thanks.LoadTexture(spriteCommon_, 5, L"Resources/ty.png", dxCommon_->GetDevice());
	thanksAlpha = 0.0f;
	//loading
	loading.SpriteCreate(dxCommon_->GetDevice(), 6, Vector2(0.0f, 0.0f), false, false);
	loading.SetScale(Vector2(256 * 1, 48 * 1));
	loading.SetPosition({ 1000,640,0 });
	loading.SpriteTransferVertexBuffer(loading, 6);
	loading.LoadTexture(spriteCommon_, 6, L"Resources/loading.png", dxCommon_->GetDevice());
	//tips
	tips.SpriteCreate(dxCommon_->GetDevice(), 7, Vector2(0.0f, 0.0f), false, false);
	tips.SetScale(Vector2(800, 48));
	tips.SetPosition({ 150,620,0 });
	tips.SpriteTransferVertexBuffer(tips, 7);
	tips.LoadTexture(spriteCommon_, 7, L"Resources/tips.png", dxCommon_->GetDevice());
	//dmg
	dmg.SpriteCreate(dxCommon_->GetDevice(), 8, Vector2(0.0f, 0.0f), false, false);
	dmg.SetScale(Vector2(1280, 720));
	dmg.SpriteTransferVertexBuffer(dmg, 8);
	dmg.LoadTexture(spriteCommon_, 8, L"Resources/dmg.png", dxCommon_->GetDevice());
	dmgAlpha = 0.0f;
	

	//UI初期化
	UIs = new MyEngine::GameSceneUI();
	UIs->Initialize(dxCommon_->GetDevice());

	//パーティクル初期化
	particle = Particle::LoadParticleTexture("exp.png");
	pm = ParticleManager::Create();
	clearParticle_01 = Particle::LoadParticleTexture("blue.png");
	clearPM_01 = ParticleManager::Create();
	clearParticle_02 = Particle::LoadParticleTexture("gp.png");
	clearPM_02 = ParticleManager::Create();
	clearParticle_03 = Particle::LoadParticleTexture("red.png");
	clearPM_03 = ParticleManager::Create();



	//オブジェクトにモデルを紐付ける
	pm->SetParticleModel(particle);
	clearPM_01->SetParticleModel(clearParticle_01);
	clearPM_02->SetParticleModel(clearParticle_02);
	clearPM_03->SetParticleModel(clearParticle_03);
	//カメラをセット
	pm->SetXMViewProjection(xmViewProjection);
	clearPM_01->SetXMViewProjection(xmViewProjection);
	clearPM_02->SetXMViewProjection(xmViewProjection);
	clearPM_03->SetXMViewProjection(xmViewProjection);

	//boss
	boss = new MyEngine::Boss;
	boss->BossInitialize();
	boss->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 10.0f));

	//背景オブジェクトを一度だけ更新
	for (auto& object : objects) {
		object->Update();
	}


	//スプライン制御点の読み込み
	LoadStage();
	LoadEnemy();
	//変数
	isCheckPoint = false;
	isPlayable = false;
	gameState = MAIN;
	infos.clear();
	gameTime = 150;
	cursorRotate = 0.002f;
	bossPass = 0;
	cameraTmpPos = { 0,0,0 };
	cameraTmpRot = { 0,0,0 };
	clearTimer = 0;
	isShowUI = true;
	particleTimer = 0;
	isNext = false;
	isSceneEnd = false;
	isPause = false;
	isbossStart = false;
	bossStartTime = 0;
	isBoss = false;
}

///-----更新処理-----///
void GameScene::Update() {
	//クロスヘアを更新
	GetCrosshair();
	//メインゲーム開始時フェードアウト
	if (fadeout.GetPosition().y < FADE_LIMIT) {
		fadeout.SetPosition(fadeout.GetPosition() + FADE_DOWN);
		fadeout.SpriteUpdate(fadeout, spriteCommon_);
	}

	//メインゲーム中
	switch (gameState)
	{
		//メインゲーム
	case GameScene::MAIN:
		MainUpdate();
		break;
		//ボス戦
	case GameScene::BOSS:
		BossUpdate();
		break;

		//コンティニュー
	case GameScene::CONTINUE:
		player->Dead();
		UIs->DeadUIPos();
		railCamera->ViewUpdate();
		if (player->GetDeathTimer() >= DEAD_TIME) {
			UIs->ContinueText();

			if (UIs->GetIsGameSceneReset() == true) {
				GameSceneManager::GetInstance()->ChangeScene("GAMEPLAY");
			}
			if (UIs->GetIsGameOver() == true) {
				fadeAlpha += ADD_FADE;
				fade.SetAlpha(fade, fadeAlpha);
				fade.SpriteUpdate(fade, spriteCommon_);
				if (fadeAlpha >= ALPHA_MAX) {
					GameSceneManager::GetInstance()->ChangeScene("OVER");
				}
			}
		}
		break;

		//クリアシーンに遷移
	case GameScene::CLEAR:
		//ボス撃破
		boss->SlainUpdate();

		ClearUpdate();
		break;

	case GameScene::PAUSE:
		PauseUpdate();
		break;
	}
	//////////////共通更新///////////////////
	//gameover
	if (player->GetHP() <= 0) {
		infos.clear();
		gameState = CONTINUE;
	}
	//ダメージエフェクト
	if (gameState == MAIN || gameState == BOSS) {
		if (player->GetIsHit() == true) {
			dmgAlpha += ADD_FADE;
			dmg.SetAlpha(dmg, dmgAlpha);
			//画面シェイク
			railCamera->ShakeCamera(SHAKE_MIN, SHAKE_MAX);
		}
		else {
			if (dmgAlpha >= 0) {
				dmgAlpha -= ADD_FADE;
				dmg.SetAlpha(dmg, dmgAlpha);  
			}
		}
	}

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
	for (const std::unique_ptr<MyEngine::Enemy>& enemy_ : enemys_) {
		enemy_->EnemyDraw(railCamera->GetView());
	}
	for (const std::unique_ptr<MyEngine::BombEnemy>& bombEnemy_ : bombEnemys_) {
		bombEnemy_->BombDraw(railCamera->GetView());
	}
	//ボス
	if (gameState == BOSS) {
		boss->BossDraw(railCamera->GetView());
	}
	if (gameState == CLEAR) {
		if (boss->GetISlained() == false) {
			boss->BossDraw(railCamera->GetView());
		}
	}
	//プレイヤー
	player->PlayerDraw(railCamera->GetView());

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion

#pragma region FBX3Dオブジェクト描画

#pragma endregion


#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon_->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///

	if (gameState == BOSS) {
		fade.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		if (boss->GetTimer() < 0) {
			//ボスのHP
			bossHP.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
	}
	Sprite::PostDraw();


	if (isShowUI == true) {
		UIs->Draw(dxCommon_->GetDevice(), dxCommon_->GetCommandList(),isBoss);
	}
	if (gameState == CONTINUE && player->GetDeathTimer() >= DEAD_TIME) {
		UIs->DrawContinue(dxCommon_->GetDevice(), dxCommon_->GetCommandList());
	}
	if (gameState == PAUSE) {
		UIs->DrawPause(dxCommon_->GetDevice(), dxCommon_->GetCommandList());
	}
	if (isNext == true) {
		UIs->DrawClear(dxCommon_->GetDevice(), dxCommon_->GetCommandList());
	}

	Sprite::PreDraw(dxCommon_->GetCommandList(), spriteCommon_);
	if (isPlayable == true && gameState != CONTINUE && gameState != PAUSE) {
		for (int i = 0; i < CROSSHAIR_MAX; i++) {
			crosshair[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
	}
	if (isPlayable == true && gameState != CONTINUE && gameState != PAUSE) {
		for (int i = 0; i < infos.size(); i++) {
			lock[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
	}
	fadeout.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());

	if (gameState == CONTINUE || gameState == PAUSE) {
		fade.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	if (gameState == PAUSE) {
		tips.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		loading.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	if (gameState == CLEAR) {
		fade.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		thanks.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	if (gameState != CLEAR) {
		dmg.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon_->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル
	if (isSceneEnd == false) {
		pm->Draw();
		clearPM_01->Draw();
		clearPM_02->Draw();
		clearPM_03->Draw();
	}

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

	dxCommon_->PostDraw();
}

void GameScene::LoadStage() {
	points.clear();
	bossPoint.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/stagePop.csv");
	assert(file.is_open());

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');


		// 先頭文字列がstなら通常ステージ
		if (key == "st") {
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			points.emplace_back(position);
		}
		//先頭文字がboならボスステージ
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
//解放
void GameScene::Finalize()
{
	delete player;
	delete railCamera;
	delete boss;
	delete UIs;
	delete sprite;
	delete xmViewProjection;
}

void GameScene::LoadEnemy() {

	Spline spline;
	spline.Initialize();

	enemys_.clear();
	bombEnemys_.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/EnemyPop.csv");
	assert(file.is_open());


	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');

		// 先頭文字列がeaなら通常敵
		if (key == "ea") {
			//敵の生成
			std::unique_ptr<MyEngine::Enemy> newEnemy = std::make_unique<MyEngine::Enemy>();
			//敵の初期化
			newEnemy->EnemyInitialize();
			////コライダーの追加
			newEnemy->SetCollider(new SphereCollider());
			// X,Y,Z座標読み込み
			Vector3 position{};
			Vector3 addpos{};
			float t;

			line_stream >> t;
			line_stream >> addpos.x;
			line_stream >> addpos.y;
			line_stream >> addpos.z;
			newEnemy->SetStagePoint(t);
			position = spline.LinePosition(points, t);

			// 座標データに追加
			newEnemy->SetPosition(position + addpos);
			newEnemy->SetScale(ENEMY_SCALE);
			//登録
			enemys_.push_back(std::move(newEnemy));
		}

		// 先頭文字列がebなら突進してくる敵
		if (key == "eb") {
			//敵の生成
			std::unique_ptr<MyEngine::BombEnemy> newEnemy = std::make_unique<MyEngine::BombEnemy>();
			//敵の初期化
			newEnemy->BombInitialize();
			////コライダーの追加
			newEnemy->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 2.0f));
			// X,Y,Z座標読み込み
			Vector3 position{};
			Vector3 addpos{};
			float t;

			line_stream >> t;
			line_stream >> addpos.x;
			line_stream >> addpos.y;
			line_stream >> addpos.z;
			newEnemy->SetStagePoint(t);
			position = spline.LinePosition(points, t);

			// 座標データに追加
			newEnemy->SetPosition(position + addpos);
			newEnemy->SetScale(ENEMY_SCALE);
			//登録
			bombEnemys_.push_back(std::move(newEnemy));
		}
	}
	// ファイルと閉じる
	file.close();
}
//ロックオン
void GameScene::SerchEnemy()
{
	Vector3 cur = input->GetMousePos();

	//ロックオン判定
	if (input->PushMouseRight()) {
		//ボス
		for (int i = 0; i < boss->GetPartsNum(); i++) {
			//敵座標を座標変換
			Vector3 bpos = GetWorldToScreenPos(boss->GetParts(i)->GetWorldPos(), railCamera);
			//ボスが登場しているなら
			if (boss->GetIsInvisible() == false) {
				//2D座標上で判定を取る(円)
				if (pow((bpos.x - cur.x), 2) + pow((bpos.y - cur.y), 2) < pow(BOSS_RADIUS, 2)) {
					if (boss->GetParts(i)->GetIsLocked() == false && infos.size() < INFOS_MAX) {
						LockInfo info;
						info.vec = boss->GetParts(i)->GetWorldPos();
						info.obj = boss->GetParts(i);
						infos.push_back(info);
						boss->GetParts(i)->SetIsLocked(true);
					}
				}
			}
		}

		//雑魚敵
		for (const std::unique_ptr<MyEngine::Enemy>& enemy_ : enemys_) {
			//敵座標を座標変換
			Vector3 epos = GetWorldToScreenPos(enemy_->GetWorldPos(), railCamera);
			//2D座標上で判定を取る(円)
			if (pow((epos.x - cur.x), 2) + pow((epos.y - cur.y), 2) < pow(ENEMY_RADIUS, 2)) {
				if (enemy_->GetIsLocked() == false && infos.size() < INFOS_MAX && enemy_->GetIsInvisible() == false) {
					LockInfo info;
					info.vec = enemy_->GetWorldPos();
					info.obj = enemy_->GetPointer();
					infos.push_back(info);
					enemy_->SetIsLocked(true);
				}
			}
		}
		//突進してくる敵
		for (const std::unique_ptr<MyEngine::BombEnemy>& bombEnemy_ : bombEnemys_) {
			//敵座標を座標変換
			Vector3 epos = GetWorldToScreenPos(bombEnemy_->GetWorldPos(), railCamera);
			//2D座標上で判定を取る(円)
			if (pow((epos.x - cur.x), 2) + pow((epos.y - cur.y), 2) < pow(ENEMY_RADIUS, 2)) {
				if (bombEnemy_->GetIsLocked() == false && infos.size() < INFOS_MAX && bombEnemy_->GetIsInvisible() == false) {
					LockInfo info;
					info.vec = bombEnemy_->GetWorldPos();
					info.obj = bombEnemy_->GetPointer();
					infos.push_back(info);
					bombEnemy_->SetIsLocked(true);
				}
			}
		}

		//ロックオン中のカーソル回転
		if (cursorRotate < ROTATE_CURSOR_MAX) {
			cursorRotate += ADD_ROTATE_CURSOR;
		}
	}
	//減速
	else {
		if (cursorRotate > ROTATE_CURSOR_MIN) {
			cursorRotate -= ADD_ROTATE_CURSOR;
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
//ロックオン情報クリア
void GameScene::LockedClear()
{
	if (player->GetIsReqClear() == true) {
		infos.erase(infos.begin());
	}
	
}

void GameScene::GetCrosshair()
{
	Vector3 mPos = input->GetMousePos();
	//マウスカーソルの場所にクロスヘアを表示
	if (gameState == MAIN) {
		for (int i = 0; i < crosshair.size(); i++) {
			//クロスヘアを距離を離して描画
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
			//回転の方向を交互に
			if (i % 2 == 0) {
				crosshair[i].SetRotation(crosshair[i].GetRotation() + cursorRotate);
			}
			else {
				crosshair[i].SetRotation(crosshair[i].GetRotation() - cursorRotate);
			}
			if (crosshair[i].GetRotation() == ROTATE_MAX) {
				crosshair[i].SetRotation(0.0f);
			}
			crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
			crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
		}
	}
	//ボス戦中
	else {
		for (int i = 0; i < CROSSHAIR_MAX; i++) {
			crosshair[i].SetPosition(mPos);
			if (i % 2 == 0) {
				crosshair[i].SetRotation(crosshair[i].GetRotation() + cursorRotate);
			}
			else {
				crosshair[i].SetRotation(crosshair[i].GetRotation() - cursorRotate);
			}
			if (crosshair[i].GetRotation() == ALPHA_MAX) {
				crosshair[i].SetRotation(0.0f);
			}
			crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
			crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
		}
	}
}
//3D座標を2D座標にして返す
Vector3 GameScene::GetScreenToWorldPos(const Sprite& sprite_, MyEngine::RailCamera* rail)
{
	//カメラがnullなら+zで返す
	if (rail == nullptr) {
		return Vector3(0, 0, 1);
	}

	//ビューポート行列生成
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width, WinApp::window_height, { 0.0f, 0.0f });

	//ビュープロジェクションビューポート合成行列
	Matrix4 invViewPort = viewPort;
	invViewPort.MakeInverse();
	//プロジェクション行列//	 
	float fovAngleY = PROJECTION_ANGLE * (PI / DEGREES);
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	//プロジェクション行列生成
	Matrix4 projection = projection.ProjectionMat(fovAngleY, aspectRatio, PROJECTION_NEAR, PROJECTION_FAR);
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
	Vector3 pos = player->GetWorldPos();
	Vector3 translate = (posFar - pos) * PROJECTION_DISTANCE;

	return translate;
}

//2D座標を3D座標(スクリーン)にして返す
Vector3 GameScene::GetWorldToScreenPos(const Vector3& pos_, MyEngine::RailCamera* rail)
{
	//カメラがnullなら0で返す
	if (rail == nullptr) {
		return Vector3(0, 0, 0);
	}

	//ビュー行列//
	Matrix4 view = railCamera->GetView()->GetMatView();
	//プロジェクション行列//
	float fovAngleY = PROJECTION_ANGLE * (PI / DEGREES);
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	//プロジェクション行列生成
	Matrix4 projection = projection.ProjectionMat(fovAngleY, aspectRatio, PROJECTION_NEAR, PROJECTION_FAR);
	//ビューポート行列生成
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width, WinApp::window_height, { 0.0f, 0.0f });
	//行列をかけ合わせる
	Matrix4 matVPV = view * projection * viewPort;
	//w除算
	Matrix4 mat;
	Vector3 posScreen = pos_;																									  
	posScreen = mat.transform(posScreen, matVPV);
	posScreen.z = 0;

	return posScreen;
}

Vector2 GameScene::GetWorldToScreenScale(Object3d* obj_, MyEngine::RailCamera* rail)
{
	//カメラがnullなら0で返す
	if (rail == nullptr) {
		return Vector2(0, 0);
	}

	Vector3 v = obj_->GetPosition() - rail->GetView()->GetEye();
	v.normalize();
	float len = v.length();

	float x = INITIAL_SCALE;
	x *= obj_->GetScale().x;
	float y = INITIAL_SCALE;
	y *= obj_->GetScale().y;


	return Vector2(x / len, y / len);
}

void GameScene::ClearUpdate()
{
	//カーソルを画面内固定を解除
	if (Input::GetInstance()->GetIsVailCursor() == true) {
		Input::GetInstance()->IsClipCursor(false);
	}

	   //クリア演出
	if (boss->GetISlained() == true && isSceneEnd == false) {
		//タイマーで進行(プレイヤー介入なし)
			//ボス爆破
		if (clearTimer < CLEARTIME_ONE) {
			pm->Fire(particle, { 0,0,0 }, PARTICLE_POS, BOSS_PARTICLE_VEL, 0, BOSS_PARTICLE_NUM, { BOSS_PARTICLE_SCALE,0 });
		}
		else if (clearTimer == CLEARTIME_TWO) {
			railCamera->GetView()->SetEye(CLEAR_CAMERA_POS_ONE);
		}
		else if (clearTimer > CLEARTIME_TWO && clearTimer < CLEARTIME_THREE) {
			pm->Fire(particle, { 0,0,0 }, PARTICLE_POS, BOSS_PARTICLE_VEL, 0, BOSS_PARTICLE_NUM, { BOSS_PARTICLE_SCALE,0 });
		}
		else if (clearTimer == CLEARTIME_FOUR) {
			railCamera->GetView()->SetEye(CLEAR_CAMERA_POS_TWO);
		}
		else if (clearTimer > CLEARTIME_FOUR && clearTimer < CLEARTIME_FIVE) {
			pm->Fire(particle, { 0,0,0 }, PARTICLE_POS, BOSS_PARTICLE_VEL, 0, BOSS_PARTICLE_NUM, { BOSS_PARTICLE_SCALE,0 });
		}
		//プレイヤーを映す
		else if (clearTimer == CLEARTIME_SIX) {
			railCamera->GetView()->SetEye(CLEAR_CAMERA_POS_THREE);
			player->SetPosition(CLEAR_PLAYER_POS);
			player->ViewUpdate();
		}
		//カメラを上に
		else if (clearTimer > CLEARTIME_SIX && clearTimer < CLEARTIME_SEVEN) {
			railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + CLOAR_CAMERA_MOVE);
		}
		//花火
		else if (clearTimer > CLEARTIME_SEVEN) {
			if (particleTimer < PARTICLENUM) {
				if (particleTimer < PARTICLENUM_ONE) {
					clearPM_01->Fire(clearParticle_01, { BLUE_FIRE.x,BLUE_FIRE.y,BLUE_FIRE.z }, PARTICLE_POS, FIRE_PARTICLE_VEL, 0, FIRE_PARTICLE_NUM, { FIRE_PARTICLE_SCALE,0 });
				}
				else if (particleTimer < PARTICLENUM_TWO) {
					clearPM_02->Fire(clearParticle_02, { GREEN_FIRE.x,GREEN_FIRE.y,GREEN_FIRE.z }, PARTICLE_POS, FIRE_PARTICLE_VEL, 0, FIRE_PARTICLE_NUM, { FIRE_PARTICLE_SCALE,0 });
				}
				else if (particleTimer < PARTICLENUM_THREE) {
					clearPM_03->Fire(clearParticle_03, { RED_FIRE.x,RED_FIRE.y,RED_FIRE.z }, PARTICLE_POS, FIRE_PARTICLE_VEL, 0, FIRE_PARTICLE_NUM, { FIRE_PARTICLE_SCALE,0 });
				}
				particleTimer++;
			}
			else {
				particleTimer = 0;
			}
			//クリック受付状態へ
			if (clearTimer > CLEARTIME_EIGHT) {
				isNext = true;
			}
		}

		pm->Update();
		clearPM_01->Update();
		clearPM_02->Update();
		clearPM_03->Update();
		clearTimer++;

		//クリック受付状態
		if (isNext == true) {
			UIs->CursorUpdate(false);
			UIs->ClearUpdate();
			//左クリックでつぎへ
			if (Input::GetInstance()->TriggerMouseLeft()) {
				isSceneEnd = true;
				clearTimer = 0;
				fadeAlpha = 0.0f;
			}
		}
	}

	//フェイドアウトしてタイトルへ
	if (isSceneEnd == true) {
		if (fadeAlpha < ALPHA_MAX) {
			fadeAlpha += ADD_FADE;
			fade.SetAlpha(fade, fadeAlpha);
		}
		else {
			if (clearTimer < FADENUM_ONE) {
				thanksAlpha += ADD_FADE;
				thanks.SetAlpha(thanks, thanksAlpha);
			}
			else if (clearTimer > FADENUM_TWO) {
				thanksAlpha -= ADD_FADE;
				thanks.SetAlpha(thanks, thanksAlpha);
			}
			else{
				GameSceneManager::GetInstance()->ChangeScene("TITLE");
			}
			clearTimer++;
		}
	}
	//カメラ更新
	railCamera->ViewUpdate();
}

void GameScene::PauseUpdate() {
	//カーソルを画面内固定を解除
	if (Input::GetInstance()->GetIsVailCursor() == true) {
		Input::GetInstance()->IsClipCursor(false);
	}
	if (isPause == true) {
		UIs->PauseText();

		//リセット
		if (UIs->GetIsGameOver() == true) {
			GameSceneManager::GetInstance()->ChangeScene("GAMEPLAY");
		}
		//タイトル
		else if (UIs->GetIsGameSceneReset() == true) {
			fadeAlpha += ADD_FADE;
			fade.SetAlpha(fade, fadeAlpha);
			fade.SpriteUpdate(fade, spriteCommon_);
			if (fadeAlpha >= ALPHA_MAX) {
				tips.SpriteUpdate(tips, spriteCommon_);
				loading.SpriteUpdate(loading, spriteCommon_);
				GameSceneManager::GetInstance()->ChangeScene("TITLE");
			}
		}
		//ポーズとじる
		else {
			if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
				isPause = false;
			}
		}
	}
	//ゲームシーンに戻る
	else {
		UIs->CloseText();

		if (UIs->GetIsClose() == true) {
			//もとのシーンへ
			gameState = gameState_bak;
		}
	}

	railCamera->ViewUpdate();
}

void GameScene::BossUpdate() {
	//カーソルを画面内に固定
	if (Input::GetInstance()->GetIsVailCursor() == false) {
		Input::GetInstance()->IsClipCursor(true);
	}
	//ボス戦開始時
	if (isbossStart == false) {
		//playerを操作不可に
		if (isPlayable == true) {
			isPlayable = false;
			railCamera->GetView()->SetEye(BOSS_START_EYE);
			isShowUI = false;
		}
		//演出
		railCamera->GetView()->SetTarget(boss->GetPosition());
		//演出終了
		if (boss->GetTimer() < 0) {
			player->SetAlpha(player->GetAlpha() - SUB_PLAYER_ALPHA);
			player->ViewUpdate();
			railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() - BOSS_CAMERA_FORCUS);
			if (bossStartTime == BOSS_START_MAX) {
				isbossStart = true;
				railCamera->SetPlayer(player);
				player->SetPosition({ 0,0,0 });
				player->SetRotation(ROTATE_BACK);
			}
			bossStartTime++;
		}
		else if (boss->GetTimer() == 0) {
			railCamera->GetView()->SetEye(BOSS_SCENE_CAMERA);
			player->SetPosition(BOSS_SCENE_PPOS);
			player->SetRotation(ROTATE_FRONT);
			player->ViewUpdate();
			railCamera->GetView()->SetTarget(player->GetPosition());
		}
		else if (boss->GetTimer() == BOSS_TIME) {
			railCamera->GetView()->SetEye(BOSS_POP_CAMERA);
		}
		else if (boss->GetTimer() < BOSS_TIME) {
			railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + BOSS_POP_MOVE);
		}
	}
	else {
		//操作可能状態に
		if (isPlayable == false) {
			railCamera->GetView()->SetEye(BOSS_FIGHT_EYE);
			railCamera->GetView()->SetTarget(BOSS_FIGHT_TARGET);
			railCamera->GetCamera()->SetPosition(BOSS_FIGHT_PPOSITION);
			fadeAlpha = ALPHA_MAX;
			fade.SetAlpha(fade, fadeAlpha);
			isPlayable = true;
			isShowUI = true;
		}
		//なんとかしたいBossHP
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
		if (isPlayable == true) {
			Vector3 shotVec;
			if (input->PushMouseLeft()) {
				shotVec = GetScreenToWorldPos(crosshair[0], railCamera);
			}
			SerchEnemy();
			player->Update(shotVec, infos);
			player->SetAlpha(0.0f);
			LockedClear();
		}

		//カメラ更新
		if (railCamera->GetOnRail() == false) {
			gameTime++;
			if (gameTime == GAME_TIME_MAX) {
				railCamera->SetOnRail(true);
				gameTime = 0;
			}
		}
		railCamera->Update(player, bossPoint);
		railCamera->GetCamera()->SetPosition(railCamera->GetView()->GetEye());
		railCamera->GetView()->SetTarget(BOSS_SCENE_TARGET);
		//カメラ制御
		if (railCamera->GetPasPoint() + 1.0f > (BOSS_RAIL_CHECKPOINT + bossPass * 2)) {
			railCamera->SetOnRail(false);
			bossPass++;
		}
	}
	//fadein
	if (fadeAlpha > 0.0f) {
		fadeAlpha -= SUB_FADE;
		fade.SetAlpha(fade, fadeAlpha);
	}
	//ポーズ画面へ
	if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
		gameState_bak = gameState;
		isPause = true;
		gameState = PAUSE;
	}
	//gameclear
	if (boss->GetIsDead() == true) {
		LockedClear();
		player->SetIsHit(false);
		//playerを操作不可に
		if (isPlayable == true) {
			isPlayable = false;
			railCamera->GetView()->SetEye(TO_CLEAR_CAMERA);
			railCamera->GetView()->SetTarget(boss->GetPosition());
			isShowUI = false;
		}
		//怒りの親子関係を力ずくで解除
		delete player;
		player = new MyEngine::Player;
		player->PlayerInitialize();
		gameState = CLEAR;
	}
	//UI表示
	UIs->Update(isPlayable, player);
	//更新
	boss->Update(player->GetWorldPos());
}

void GameScene::MainUpdate() {
	//カーソルを画面内に固定
	if (Input::GetInstance()->GetIsVailCursor() == false) {
		Input::GetInstance()->IsClipCursor(true);
	}

	//ゲームスタート時演出
	if (gameTime > 0) {
		//SPACEで演出スキップ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE) || Input::GetInstance()->TriggerMouseLeft()) {
			gameTime = 1;
			UIs->SkipUIPos();
		}
		//UI表示
		if (gameTime <= 25) {
			UIs->ShowUI();
		}
		railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + START_SCENE_EYEMOVE);
		gameTime--;
		if (gameTime <= 0) {
			player->SetPosition(Vector3(0, -1.0f, -5.5f));
			player->SetAlpha(0.0f);
		}
		player->ViewUpdate();
	}
	//ゲーム中
	if (gameTime == 0) {
		//操作不可状態を解除
		if (isPlayable == false) {
			player->SetRotation(ROTATE_BACK);
			isPlayable = true;
		}
		//boss戦へ
		if (railCamera->GetOnRail() == false) {
			if (isCheckPoint == false) {
				isCheckPoint = true;
				boss->Pop();
				gameState = BOSS;
				delete player;
				//player
				player = new MyEngine::Player;
				player->PlayerInitialize();
				player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));
				player->SetAlpha(ALPHA_MAX);
				delete railCamera;
				railCamera = new MyEngine::RailCamera;
				railCamera->Initialize();
				isBoss = true;
			}
		}

		//ポーズ画面へ
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			gameState_bak = gameState;
			isPause = true;
			gameState = PAUSE;
		}

		//player更新(カメラの前)
		if (isPlayable == true) {
			Vector3 shotVec;
			if (input->PushMouseLeft()) {
				shotVec = GetScreenToWorldPos(crosshair[0], railCamera);
			}
			SerchEnemy();
			player->Update(shotVec, infos);
			LockedClear();
		}
		//デスフラグの立った敵を削除
		enemys_.remove_if([](std::unique_ptr <MyEngine::Enemy>& enemy_) {
			return enemy_->GetIsDead();
			});
		//敵キャラの更新
		for (const std::unique_ptr<MyEngine::Enemy>& enemy_ : enemys_) {
			enemy_->Update(player->GetWorldPos(), railCamera);
		}
		//デスフラグの立った敵を削除
		bombEnemys_.remove_if([](std::unique_ptr <MyEngine::BombEnemy>& bombEnemy_) {
			return bombEnemy_->GetIsDead();
			});
		//敵キャラの更新
		for (const std::unique_ptr<MyEngine::BombEnemy>& bombEnemy_ : bombEnemys_) {
			bombEnemy_->BombUpdate(player->GetWorldPos(), railCamera);
		}
		//UI表示
		UIs->Update(isPlayable, player);
		//更新
		railCamera->Update(player, points);
	}
}