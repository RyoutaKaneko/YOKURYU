/**
 * @file GameClearScene.h
 * @brief クリア時のシーンクラス
 * @author カネコ_リョウタ
 */

#include "GameClearScene.h"

using namespace DirectX;

GameClearScene::GameClearScene()
{
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::Initialize()
{
	input_ = Input::GetInstance();
	dxCommon = DirectXCommon::GetInstance();


	//カメラ初期化
	viewProjection = new ViewProjection();
	viewProjection->Initialize();

	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());

	//gameclearの画像
	clearGH.LoadTexture(spriteCommon_, 0, L"Resources/clear.png", dxCommon->GetDevice());
	clearGH.SpriteCreate(dxCommon->GetDevice(), 0, Vector2(0.0f, 0.0f), false, false);
	clearGH.SetScale(Vector2(1280 * 1, 720 * 1));
	clearGH.SpriteTransferVertexBuffer(clearGH, 0);
	clearGH.SpriteUpdate(clearGH, spriteCommon_);
	
	showTime = 0;
	isNext = false;
	curHit01 = false;
	curHit02 = false;
}

void GameClearScene::Update()
{
	viewProjection->UpdateMatrix();
	clearGH.SpriteUpdate(clearGH, spriteCommon_);
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		GameSceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameClearScene::Draw()
{
	// 描画前処理
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCommandList());


	Object3d::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList(),spriteCommon_);

	clearGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());

	Sprite::PostDraw();

	
	// 描画後処理
	dxCommon->PostDraw();
}

void GameClearScene::Finalize()
{
}
