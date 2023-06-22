#include "GameScene.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

GameScene::GameScene() {
	
}
GameScene::~GameScene() {
	delete player;
}

///-----�ϐ��̏�����-----///
void GameScene::Initialize(SpriteCommon& spriteCommon) {
	//���
	dxCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	
	//player
	playerModel = Model::LoadFromOBJ("triangle_mat");
	player = Object3d::Create();
	player->SetModel(playerModel);
	player->SetPosition(Vector3(0, 0, 0));
	//test
	testModel = Model::LoadFromOBJ("ironSphere");
	test = Object3d::Create();
	test->SetModel(testModel);
	test->SetPosition(Vector3(-3, 0, -15));
	//�J����
	viewProjection = new ViewProjection;
	viewProjection->Initialize();
	viewProjection->eye = { 0, 3, -30 };
	viewProjection->target = { 0, 0, 0 };

	xmViewProjection = new XMViewProjection;

	//FbxObject�̐ÓI������
	//�J�������Z�b�g
	FbxObject3d::SetCamera(viewProjection);
	//�O���t�B�b�N�X�p�C�v���C����������
	FbxObject3d::CreateGraphicsPipeline();

	// �X�v���C�g�̏�����
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice(), 1280, 720);
	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dxCommon->GetDevice());

	//�؂̉摜
	wood.LoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	wood.SetColor(Vector4(1, 1, 1, 1));
	wood.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(128 * 1, 128 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer(wood, spriteCommon, 0);
	wood.SpriteUpdate(wood, spriteCommon_);

	//�얲�̉摜
	reimu.LoadTexture(spriteCommon_, 1, L"Resources/reimu.png", dxCommon->GetDevice());
	reimu.SetColor(Vector4(1, 1, 1, 1));
	reimu.SpriteCreate(dxCommon->GetDevice(), 50, 50, 1, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	reimu.SetPosition(Vector3(1100, 0, 0));
	reimu.SetScale(Vector2(128 * 1, 128 * 1));
	reimu.SetRotation(0.0f);
	reimu.SpriteTransferVertexBuffer(reimu, spriteCommon, 1);
	reimu.SpriteUpdate(reimu, spriteCommon_);

	//�p�[�e�B�N��������
	particle = Particle::LoadParticleTexture("wood.png");
	pm_ = ParticleManager::Create();
	particle_ = Particle::LoadParticleTexture("reimu.png");
	pm = ParticleManager::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	pm->SetParticleModel(particle);
	pm_->SetParticleModel(particle_);
	//�J�������Z�b�g
	pm->SetXMViewProjection(xmViewProjection);
	pm_->SetXMViewProjection(xmViewProjection);

	//���f�������w�肵�ēǂݍ���
	obj = new FbxObject3d;
	obj->Initialize();
	model = FbxLoader::GetInstance()->LoadModelFlomFile("cube");
	obj->SetModel(model);
	obj->SetPosition(Vector3(1, 0, -10));
	obj->SetScale(Vector3(0.01, 0.01, 0.01));
}

///-----�X�V����-----///
void GameScene::Update() {
	input->Update();

	//player�ړ�
	if (input->PushKey(DIK_W)) {
		player->SetPosition(player->GetPosition() + Vector3(0, 0, 0.1f));
	}
	if (input->PushKey(DIK_A)) {
		player->SetPosition(player->GetPosition() + Vector3(-0.1f, 0, 0));
	}
	if (input->PushKey(DIK_D)) {
		player->SetPosition(player->GetPosition() + Vector3(0.1f, 0, 0));
	}
	if (input->PushKey(DIK_S)) {
		player->SetPosition(player->GetPosition() + Vector3(0, 0, -0.1f));
	}

	//�p�[�e�B�N��
	if (input->PushKey(DIK_SPACE))
	{
		pm->Fire(particle, 30, 0.2f, 0, 2, { 8.0f, 0.0f });
		pm_->Fire(particle_, 30, 0.2f, 0, 1, { 8.0f, 0.0f });
	}

	//�J���� 
	if (input->PushKey(DIK_RIGHT)) {
		viewProjection->eye += Vector3(0.1f, 0, 0);
	}
	if (input->PushKey(DIK_LEFT)) {
		viewProjection->eye += Vector3(-0.1f, 0, 0);
	}
	if (input->PushKey(DIK_UP)) {
		viewProjection->eye += Vector3(0, 0, 0.1f);
	}
	if (input->PushKey(DIK_DOWN)) {
		viewProjection->eye += Vector3(0, 0, -0.1f);
	}
	//���_�ړ�
	if (input->PushKey(DIK_J)) {
		viewProjection->target += Vector3(-0.1f, 0, 0);
	}
	if (input->PushKey(DIK_L)) {
		viewProjection->target += Vector3(0.1f, 0, 0);
	}
	if (input->PushKey(DIK_I)) {
		viewProjection->target += Vector3(0, 0.1f, 0);
	}
	if (input->PushKey(DIK_K)) {
		viewProjection->target += Vector3(0, -0.1f, 0);
	}


	//�X�V
	player->Update();
	test->Update();
	viewProjection->UpdateMatrix();
	pm->Update();
	pm_->Update();
	obj->Update();
}

void GameScene::Draw() {
#pragma region 3D�I�u�W�F�N�g�`��

// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	player->Draw(viewProjection);
	test->Draw(viewProjection);

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

#pragma endregion

#pragma region FBX3D�I�u�W�F�N�g�`��

	// 3D�I�u�W�F�N�g�`��O����
	FbxObject3d::PreDraw(dxCommon->GetCommandList());

	obj->Draw(viewProjection);

	// 3D�I�u�W�F�N�g�`��㏈��
	FbxObject3d::PostDraw();

#pragma endregion

#pragma region �p�[�e�B�N���`��

	// �p�[�e�B�N���`��O����
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	///==== �p�[�e�B�N���`�� ====///
	//�p�[�e�B�N��
	pm->Draw();
	pm_->Draw();

	// �p�[�e�B�N���`��㏈��
	ParticleManager::PostDraw();

#pragma endregion

#pragma region �X�v���C�g�`��

	// �X�v���C�g�`��O����
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);

	///=== �X�v���C�g�`�� ===///
	wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);
	reimu.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), reimu.vbView);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}