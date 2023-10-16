/**
 * @file GameOverScene.h
 * @brief �Q�[���I�[�o�[���̃V�[���N���X
 * @author �J�l�R_�����E�^
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


	//�J����������
	viewProjection = new ViewProjection();
	viewProjection->Initialize();

	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());
	//gameclear�̉摜
	overGH.LoadTexture(spriteCommon_, 0, L"Resources/over.png", dxCommon->GetDevice());
	overGH.SpriteCreate(dxCommon->GetDevice(), 0, Vector2(0.0f, 0.0f), false, false);
	overGH.SetScale(Vector2(1280 * 1, 720 * 1));
	overGH.SpriteTransferVertexBuffer(overGH, 0);
	overGH.SpriteUpdate(overGH, spriteCommon_);
}

void GameOverScene::Update()
{
	viewProjection->UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		GameSceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameOverScene::Draw()
{
	// �`��O����
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCommandList());


	Object3d::PostDraw();
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);
	overGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	Sprite::PostDraw();

	// �`��㏈��
	dxCommon->PostDraw();
}

void GameOverScene::Finalize()
{
}
