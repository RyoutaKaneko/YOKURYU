/**
 * @file GameOverScene.h
 * @brief ゲームオーバー時のシーンクラス
 * @author カネコ_リョウタ
 */

#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	input_ = Input::GetInstance();
	dxCommon = DirectXCommon::GetInstance();

	//カメラ初期化
	viewProjection = new ViewProjection();
	viewProjection->Initialize();
	viewProjection->SetEye({ 0,5,-10 });

	// OBJからモデルデータを読み込む
	skyModel = Model::LoadFromOBJ("sky");
	skyModel->LoadTexture("Resources/black.png");
	// 3Dオブジェクト生成
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetPosition(Vector3(0, 0, 0));
	sky->SetScale(Vector3(50, 50, 50));
	// OBJからモデルデータを読み込む
	stageModel = Model::LoadFromOBJ("stage");
	// 3Dオブジェクト生成
	stage = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	stage->SetModel(stageModel);
	stage->SetPosition(Vector3(0, -2, 1));
	stage->SetScale(Vector3(1.5f, 1.5f, 1.5f));

	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetPosition({ 0.0f,-1.0f,0.0f });
	player->SetRotation({ 0,90,0 });
	viewProjection->SetTarget(player->GetWorldPos());

	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());
	//gameoverの画像
	overGH.LoadTexture(spriteCommon_, 0, L"Resources/over.png", dxCommon->GetDevice());
	overGH.SpriteCreate(dxCommon->GetDevice(), 0, Vector2(0.5f, 0.5f), false, false);
	overGH.SetScale(Vector2(768 * 1, 128 * 1));
	overGH.SetPosition(Vector3(640,150,0));
	overGH.SpriteTransferVertexBuffer(overGH, 0);
	overGH.SpriteUpdate(overGH, spriteCommon_);
	//fadeの画像
	fade.LoadTexture(spriteCommon_, 1, L"Resources/black.png", dxCommon->GetDevice());
	fade.SpriteCreate(dxCommon->GetDevice(), 1, Vector2(0.5f, 0.5f), false, false);
	fade.SetScale(Vector2(1280 * 1, 720 * 1));
	fade.SetPosition(Vector3(640, 360, 0));
	fade.SpriteTransferVertexBuffer(fade, 1);
	fade.SpriteUpdate(fade, spriteCommon_);
	//textの画像
	textGH.LoadTexture(spriteCommon_, 2, L"Resources/ty.png", dxCommon->GetDevice());
	textGH.SpriteCreate(dxCommon->GetDevice(), 2, Vector2(0.5f, 0.5f), false, false);
	textGH.SetScale(Vector2(832 * 1, 72 * 1));
	textGH.SetPosition(Vector3(640, 360, 0));
	textGH.SetAlpha(textGH, 0.0f);
	textGH.SpriteTransferVertexBuffer(textGH, 2);
	textGH.SpriteUpdate(textGH, spriteCommon_);

	fadeAlpha = 1.0f;
	gameTimer = 0;
}

void GameOverScene::Update()
{
	if (gameTimer < 50) {
		if (fadeAlpha > 0.0f) {
			fadeAlpha -= 0.05f;
			fade.SetAlpha(fade, fadeAlpha);
			fade.SpriteUpdate(fade, spriteCommon_);
		}
	}
	else if (gameTimer < 200) {}
	else if(gameTimer < 250){
		if (fadeAlpha < 1.0f) {
			fadeAlpha += 0.05f;
			fade.SetAlpha(fade, fadeAlpha);
			fade.SpriteUpdate(fade, spriteCommon_);
		}
		if (textAlpha < 1.0f) {
			textAlpha += 0.025f;
			textGH.SetAlpha(textGH, textAlpha);
			textGH.SpriteUpdate(textGH, spriteCommon_);
		}
	}
	else if(gameTimer < 300){
		if (textAlpha > 0.0f) {
			textAlpha -= 0.025f;
			textGH.SetAlpha(textGH, textAlpha);
			textGH.SpriteUpdate(textGH, spriteCommon_);
		}
	}
	else {
		GameSceneManager::GetInstance()->ChangeScene("TITLE");
	}


	player->GetWorldTransform().UpdateMatrix();
	sky->Update();
	stage->Update();
	viewProjection->UpdateMatrix();

	gameTimer++;
}

void GameOverScene::Draw()
{
	// 描画前処理
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCommandList());

	sky->Draw(viewProjection);
	stage->Draw(viewProjection);
	player->PlayerDraw(viewProjection);

	Object3d::PostDraw();
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);
	overGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	fade.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	textGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	Sprite::PostDraw();

	// 描画後処理
	dxCommon->PostDraw();
}

void GameOverScene::Finalize()
{
}
