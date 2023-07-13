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
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));
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
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());

	//木の画像
	wood.LoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	wood.SetColor(Vector4(1, 1, 1, 1));
	wood.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, Vector2(0.0f, 0.0f), false, false);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(128 * 1, 128 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer(wood, 0);
	wood.SpriteUpdate(wood, spriteCommon_);

	//クロスヘアの画像
	crosshair.LoadTexture(spriteCommon_, 1, L"Resources/crosshair.png", dxCommon->GetDevice());
	crosshair.SetColor(Vector4(1, 1, 1, 1));
	crosshair.SpriteCreate(dxCommon->GetDevice(), 50, 50, 1, Vector2(0.0f, 0.0f), false, false);
	crosshair.SetPosition(Vector3(1100, 0, 0));
	crosshair.SetScale(Vector2(64 * 1, 64 * 1));
	crosshair.SetRotation(0.0f);
	crosshair.SpriteTransferVertexBuffer(crosshair, 1);
	crosshair.SpriteUpdate(crosshair, spriteCommon_);

	//HP用画像
	for (int i = 0; i < 5; i++) {
		hp[i].LoadTexture(spriteCommon_, 2, L"Resources/hitPoint.png", dxCommon->GetDevice());
		hp[i].SetColor(Vector4(1, 1, 1, 1));
		hp[i].SpriteCreate(dxCommon->GetDevice(), 50, 50, 2, Vector2(0.0f, 0.0f), false, false);
		hp[i].SetPosition(Vector3(0 + i * 68.0f, 0, 0));
		hp[i].SetScale(Vector2(64 * 1, 64 * 1));
		hp[i].SetRotation(0.0f);
		hp[i].SpriteTransferVertexBuffer(hp[i], 2);
		hp[i].SpriteUpdate(hp[i], spriteCommon_);
	}

	//パーティクル初期化
	particle = Particle::LoadParticleTexture("wood.png");
	pm_ = ParticleManager::Create();
	particle_ = Particle::LoadParticleTexture("crosshair.png");
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
	//デバックカメラ
	/*if (input->PushMouseRight()) {
		Vector3 v = input->GetMouseVelo();
		v.x *= -1;
		railCamera->GetView()->SetTarget(railCamera->GetView()->GetTarget() + v);
	}*/

	//マウスカーソルの場所にクロスヘアを表示
	Vector3 v = input->GetMousePos();
	crosshair.SetPosition( v - Vector3(32, 32, 0));
	/*crosshair.SetPosition(Vector3(640, 360, 0));*/
	crosshair.SpriteUpdate(crosshair, spriteCommon_);
	crosshair.SpriteTransferVertexBuffer(crosshair, 1);

	//当たり判定チェック
	collisionManager->CheckAllCollisions();

	if (player->GetHP() == 0) {
		Reset();
	}

	//更新
	if (railCamera->GetIsEnd() == false) {
		railCamera->Update(player, points);
	}
	/*railCamera->ViewUpdate();*/
	Vector3 shotVec = { 0,0,0 };
	if (input->PushMouseLeft()) {
		shotVec = GetScreenToWorldPos(crosshair, railCamera);
	}
	player->Update(shotVec);
	//デスフラグの立った敵を削除
	enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
		return enemy_->GetIsDead();
		});
	//敵キャラの更新
	for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Update(player->GetWorldPos(),railCamera->GetPasPoint());
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
		enemy->EnemyDraw(railCamera->GetView());
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
	/*wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);*/
	for (int i = 0; i < player->GetHP(); i++) {
		hp[i].SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), hp[i].vbView);
	}
	crosshair.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), crosshair.vbView);

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
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));

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
		pointsL[i] += Vector3(-2, 0, 0);
		pointsR[i] += Vector3(2, 0, 0);
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
	}
	// ファイルと閉じる
	file.close();
}

Vector3 GameScene::GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector3(0,0,1);
	}

	//ビューポート行列生成
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width,WinApp::window_height,Vector2(0.0f,0.0f));

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
	const float kDistanceTestObject = 0.01f;

	Vector3 pos = player->GetWorldPos();
	Vector3 translate = (posFar - posNear) * kDistanceTestObject;

	return translate;
}