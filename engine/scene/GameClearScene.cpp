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


	//�J����������
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
	// �`��O����
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCommandList());


	Object3d::PostDraw();

	
	// �`��㏈��
	dxCommon->PostDraw();
}

void GameClearScene::Finalize()
{
}
