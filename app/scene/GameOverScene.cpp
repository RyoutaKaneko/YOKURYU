/**
 * @file GameOverScene.h
 * @brief �Q�[���I�[�o�[���̃V�[���N���X
 * @author �J�l�R_�����E�^
 */

#include "GameOverScene.h"

const float GameOverScene::MAX_ALPHA = 1.0f;
const float  GameOverScene::ADD_FADE_ALPHA = 0.1f;
const float  GameOverScene::ADD_TEXT_ALPHA = 0.05f;

GameOverScene::GameOverScene(){}

GameOverScene::~GameOverScene(){}

void GameOverScene::Initialize()
{
	//�J�[�\������ʓ��Œ������
	if (Input::GetInstance()->GetIsVailCursor() == true) {
		Input::GetInstance()->IsClipCursor(false);
	}
	input_ = Input::GetInstance();
	dxCommon = DirectXCommon::GetInstance();

	//�J����������
	viewProjection = new ViewProjection();
	viewProjection->Initialize();
	viewProjection->SetEye({ 0,5,-10 });

	// OBJ���烂�f���f�[�^��ǂݍ���
	skyModel = Model::LoadFromOBJ("sky");
	skyModel->LoadTexture("Resources/black.png");
	// 3D�I�u�W�F�N�g����
	sky = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	sky->SetModel(skyModel);
	sky->SetPosition(Vector3(0, 0, 0));
	sky->SetScale(Vector3(50, 50, 50));
	// OBJ���烂�f���f�[�^��ǂݍ���
	stageModel = Model::LoadFromOBJ("stage");
	// 3D�I�u�W�F�N�g����
	stage = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	stage->SetModel(stageModel);
	stage->SetPosition(Vector3(0, -2, 1));
	stage->SetScale(Vector3(1.5f, 1.5f, 1.5f));

	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetPosition({ 0.0f,-1.0f,-1.0f });
	player->SetRotation({ 20,80,90 });
	player->SetScale({ 1.5f,1.5f,1.5f });
	player->SetDie();
	viewProjection->SetTarget(player->GetWorldPos());

	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());
	//gameover�̉摜
	overGH.LoadTexture(spriteCommon_, 0, L"Resources/over.png", dxCommon->GetDevice());
	overGH.SpriteCreate(dxCommon->GetDevice(), 0, Vector2(0.5f, 0.5f), false, false);
	overGH.SetScale(Vector2(768 * 1, 128 * 1));
	overGH.SetPosition(Vector3(640,150,0));
	overGH.SpriteTransferVertexBuffer(overGH, 0);
	overGH.SpriteUpdate(overGH, spriteCommon_);
	//fade�̉摜
	fade.LoadTexture(spriteCommon_, 1, L"Resources/black.png", dxCommon->GetDevice());
	fade.SpriteCreate(dxCommon->GetDevice(), 1, Vector2(0.5f, 0.5f), false, false);
	fade.SetScale(Vector2(1280 * 1, 720 * 1));
	fade.SetPosition(Vector3(640, 360, 0));
	fade.SpriteTransferVertexBuffer(fade, 1);
	fade.SpriteUpdate(fade, spriteCommon_);
	//text�̉摜
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
	//�Q�[���I�[�o�[���o
	if (gameTimer < GAMETIME_ONE) {
		if (fadeAlpha > 0.0f) {
			fadeAlpha -= ADD_FADE_ALPHA;
			fade.SetAlpha(fade, fadeAlpha);
			fade.SpriteUpdate(fade, spriteCommon_);
		}
	}
	else if (gameTimer < GAMETIME_TWO) {}
	else if(gameTimer < GAMETIME_THREE){
		if (fadeAlpha < MAX_ALPHA) {
			fadeAlpha += ADD_FADE_ALPHA;
			fade.SetAlpha(fade, fadeAlpha);
			fade.SpriteUpdate(fade, spriteCommon_);
		}
		if (textAlpha < MAX_ALPHA) {
			textAlpha += ADD_TEXT_ALPHA;
			textGH.SetAlpha(textGH, textAlpha);
			textGH.SpriteUpdate(textGH, spriteCommon_);
		}
	}
	else if(gameTimer < GAMETIME_FOUR){
		if (textAlpha > 0.0f) {
			textAlpha -= ADD_TEXT_ALPHA;
			textGH.SetAlpha(textGH, textAlpha);
			textGH.SpriteUpdate(textGH, spriteCommon_);
		}
	}
	else {
		//�^�C�g����
		GameSceneManager::GetInstance()->ChangeScene("TITLE");
	}


	player->ViewUpdate();
	sky->Update();
	stage->Update();
	viewProjection->UpdateMatrix();

	gameTimer++;
}

void GameOverScene::Draw()
{
	// �`��O����
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCommandList());

	sky->Draw(viewProjection);
	stage->Draw(viewProjection);
	player->DrawDead(viewProjection);

	Object3d::PostDraw();
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);
	overGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	fade.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	textGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
	Sprite::PostDraw();

	// �`��㏈��
	dxCommon->PostDraw();
}

//���
void GameOverScene::Finalize()
{
	delete player;
	delete sprite;
	delete viewProjection;
}
