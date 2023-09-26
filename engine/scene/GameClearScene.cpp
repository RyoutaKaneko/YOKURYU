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


	//ƒJƒƒ‰‰Šú‰»
	viewProjection = new ViewProjection();
	viewProjection->Initialize();

	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());
	
	showTime = 0;
	isNext = false;
	curHit01 = false;
	curHit02 = false;
}

void GameClearScene::Update()
{
	
}

void GameClearScene::Draw()
{
	// •`‰æ‘Oˆ—
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCommandList());


	Object3d::PostDraw();

	
	// •`‰æŒãˆ—
	dxCommon->PostDraw();
}

void GameClearScene::Finalize()
{
}
