#include "GameTitleScene.h"

using namespace DirectX;

GameTitleScene::GameTitleScene()
{
	//// サウンドの静的初期化
	//Sound::StaticInitialize();
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Initialize()
{
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon_->GetDevice());

	//titleの画像
	title.SpriteCreate(dxCommon_->GetDevice(), 50, 50, 0, Vector2(0.0f, 0.0f), false, false);
	title.SetScale(Vector2(1280 * 1, 720 * 1));
	title.SpriteTransferVertexBuffer(title, 0);
	title.SpriteUpdate(title, spriteCommon_);
	title.LoadTexture(spriteCommon_, 0, L"Resources/title.png", dxCommon_->GetDevice());

	//カメラ初期化
	viewProjection = new ViewProjection();
	viewProjection->Initialize();

	
}

void GameTitleScene::Update()
{
	viewProjection->UpdateMatrix();
	title.SpriteUpdate(title, spriteCommon_);
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		GameSceneManager::GetInstance()->ChangeScene("GAMEPLAY");
	}
}

void GameTitleScene::Draw()
{
	dxCommon_->PreDraw();

	Object3d::PreDraw(dxCommon_->GetCommandList());


	Object3d::PostDraw();
 
	Sprite::PreDraw(dxCommon_->GetCommandList(),spriteCommon_);

	title.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());

	Sprite::PostDraw();

	dxCommon_->PostDraw();
}

void GameTitleScene::Finalize()
{

}
