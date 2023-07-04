#include "GameScene.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "SphereCollider.h"
#include "CollisionManager.h"


#include <cassert>
#include <fstream>
#include <sstream>

GameScene::GameScene() {
	
}
GameScene::~GameScene() {
	delete player;
}

///-----変数の初期化-----///
void GameScene::Initialize(SpriteCommon& spriteCommon) {
	//基盤
	dxCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	//当たり判定
	collisionManager = CollisionManager::GetInstance();
	
	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetCollider(new SphereCollider);
	//sky
	skyModel = Model::LoadFromOBJ("skydome");
	sky = Object3d::Create();
	sky->SetModel(skyModel);
	sky->SetScale(Vector3(5,5,5));
	sky->SetRotation(Vector3(0, 180, 0));
	//floor
	floorModel = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorModel);
	floor->SetPosition({ 0,-20,0 });
	floor->SetScale(Vector3(500, 500, 500));

	railCamera = new RailCamera;
	railCamera->Initialize(player);

	xmViewProjection = new XMViewProjection;

	//FbxObjectの静的初期化
	//カメラをセット
	FbxObject3d::SetCamera(viewProjection);
	//グラフィックスパイプラインを初期化
	FbxObject3d::CreateGraphicsPipeline();

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dxCommon->GetDevice());

	//木の画像
	wood.LoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	wood.SetColor(Vector4(1, 1, 1, 1));
	wood.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(128 * 1, 128 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer(wood, spriteCommon, 0);
	wood.SpriteUpdate(wood, spriteCommon_);

	//霊夢の画像
	reimu.LoadTexture(spriteCommon_, 1, L"Resources/reimu.png", dxCommon->GetDevice());
	reimu.SetColor(Vector4(1, 1, 1, 1));
	reimu.SpriteCreate(dxCommon->GetDevice(), 50, 50, 1, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	reimu.SetPosition(Vector3(1100, 0, 0));
	reimu.SetScale(Vector2(128 * 1, 128 * 1));
	reimu.SetRotation(0.0f);
	reimu.SpriteTransferVertexBuffer(reimu, spriteCommon, 1);
	reimu.SpriteUpdate(reimu, spriteCommon_);

	//パーティクル初期化
	particle = Particle::LoadParticleTexture("wood.png");
	pm_ = ParticleManager::Create();
	particle_ = Particle::LoadParticleTexture("reimu.png");
	pm = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm->SetParticleModel(particle);
	pm_->SetParticleModel(particle_);
	//カメラをセット
	pm->SetXMViewProjection(xmViewProjection);
	pm_->SetXMViewProjection(xmViewProjection);

	//モデル名を指定して読み込み
	obj = new FbxObject3d;
	obj->Initialize();
	model = FbxLoader::GetInstance()->LoadModelFlomFile("cube");
	obj->SetModel(model);
	obj->SetPosition(Vector3(1, 0, -10));
	obj->SetScale(Vector3((float)0.01, (float)0.01, (float)0.01));

	//スプライン制御点の読み込み
	stageNum = 1;
	LoadStage(stageNum);
	LoadEnemy(stageNum);

}

///-----更新処理-----///
void GameScene::Update() {
	input->Update();

	////パーティクル
	//if (input->PushKey(DIK_SPACE))
	//{
	//	pm->Fire(particle, 30, 0.2f, 0, 2, { 8.0f, 0.0f });
	//	pm_->Fire(particle_, 30, 0.2f, 0, 1, { 8.0f, 0.0f });
	//}

	//リセット
	if (input->TriggerKey(DIK_R)) {
		Reset();
	}

	//当たり判定チェック
	collisionManager->CheckAllCollisions();

	//更新
	if (railCamera->GetIsEnd() == false) {
		railCamera->Update(player, points);
	}
	player->Update(railCamera->GetFrontVec());
	//デスフラグの立った敵を削除
	enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
		return enemy_->GetIsDead();
		});
	//敵キャラの更新
	for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Update();
	}
	sky->Update();
	floor->Update();
	pm->Update();
	pm_->Update();
	obj->Update();
}

void GameScene::Draw() {
#pragma region 3Dオブジェクト描画

// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	sky->Draw(railCamera->GetView());
	floor->Draw(railCamera->GetView());
	//敵キャラの描画
	for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw(railCamera->GetView());
	}
	player->PlayerDraw(railCamera->GetView());

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion

#pragma region FBX3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	FbxObject3d::PreDraw(dxCommon->GetCommandList());

	/*obj->Draw(railCamera->GetView());*/

	// 3Dオブジェクト描画後処理
	FbxObject3d::PostDraw();

#pragma endregion

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル
	pm->Draw();
	pm_->Draw();

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///
	/*wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);
	reimu.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), reimu.vbView);*/

	// スプライト描画後処理
	Sprite::PostDraw();
}

void GameScene::LoadStage(int stageNum) {
	points.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/stagePop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');


		// 先頭文字列がｖなら頂点座標
		if (key == "st" + num) {
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			points.emplace_back(position);
		}
		if (stageNum == 10) {
			if (key == "st10") {
				// X,Y,Z座標読み込み
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// 座標データに追加
				points.emplace_back(position);
			}
		}
		else if (stageNum > 10) {
			if (key == "st1" + stageNum - 10) {
				// X,Y,Z座標読み込み
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// 座標データに追加
				points.emplace_back(position);
			}
		}
	}
	// ファイルと閉じる
	file.close();
}

void GameScene::Reset() {
	delete player;
	delete railCamera;
	delete enemy;

	//player
	player = new Player;
	player->PlayerInitialize();

	railCamera = new RailCamera;
	railCamera->Initialize(player);
	LoadEnemy(stageNum);
}

void GameScene::LoadEnemy(int stageNum) {

	Spline spline;
	spline.Initialize();

	pointsL = points;
	pointsR = points;

	for (int i = 0; i < points.size(); i++)
	{
		pointsL[i] += Vector3(-4, 0, 0);
		pointsR[i] += Vector3(4, 0, 0);
	}

	enemys_.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/EnemyPop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

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

		if (stageNum < 10) {
			// 先頭文字列がｖなら頂点座標
			if (key == "ea" + num) {
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
					position = spline.EnemyPosition(pointsL, t);
				}
				else if (word.find("M") == 0)
				{
					line_stream >> t;
					position = spline.EnemyPosition(points, t);
				}
				else if (word.find("R") == 0)
				{
					line_stream >> t;
					position = spline.EnemyPosition(pointsR, t);
				}

				// 座標データに追加
				newEnemy->SetPosition(position);
				newEnemy->SetScale({ 0.6f,0.6f,0.6f });
				//登録
				enemys_.push_back(std::move(newEnemy));
			}
		}
	}
	// ファイルと閉じる
	file.close();
}