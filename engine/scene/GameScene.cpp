#include "GameScene.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "SphereCollider.h"
#include "CollisionManager.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <map>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player;
}

///-----�ϐ��̏�����-----///
void GameScene::Initialize(SpriteCommon& spriteCommon) {
	//���
	dxCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	//�����蔻��
	collisionManager = CollisionManager::GetInstance();

	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));

	//���f���ǂݍ���
	skyModel = Model::LoadFromOBJ("sky");
	seaModel = Model::LoadFromOBJ("sea");
	block01Model = Model::LoadFromOBJ("block01");
	block02Model = Model::LoadFromOBJ("block02");
	stoneModel = Model::LoadFromOBJ("stone");
	models.insert(std::make_pair("sky", skyModel));
	models.insert(std::make_pair("sea", seaModel));
	models.insert(std::make_pair("block01", block01Model));
	models.insert(std::make_pair("block02", block02Model));
	models.insert(std::make_pair("stone", stoneModel));
	//���x���G�f�B�^�ǂݍ���
	LoadObjFromLevelEditor("scene");

	railCamera = new RailCamera;
	railCamera->Initialize(player);

	xmViewProjection = new XMViewProjection;

	//FbxObject�̐ÓI������
	//�J�������Z�b�g
	FbxObject3d::SetCamera(viewProjection);
	//�O���t�B�b�N�X�p�C�v���C����������
	FbxObject3d::CreateGraphicsPipeline();

	// �X�v���C�g�̏�����
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());

	//title�̉摜
	titleGH.LoadTexture(spriteCommon_, 0, L"Resources/title.png", dxCommon->GetDevice());
	titleGH.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, Vector2(0.0f, 0.0f), false, false);
	titleGH.SetScale(Vector2(1280 * 1, 720 * 1));
	titleGH.SpriteTransferVertexBuffer(titleGH, 0);
	titleGH.SpriteUpdate(titleGH, spriteCommon_);

	//�N���X�w�A�̉摜
	for (int i = 0; i < 4; i++) {
		crosshair[i].LoadTexture(spriteCommon_, 1, L"Resources/crosshair.png", dxCommon->GetDevice());
		crosshair[i].SpriteCreate(dxCommon->GetDevice(), 1280, 720, 1, Vector2(0.5f, 0.5f), false, false);
		crosshair[i].SetPosition(Vector3(1100, 0, 0));
		crosshair[i].SetScale(Vector2(24.0f * (i + 1.0f), 24.0f * (i + 1.0f)));
		crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
		crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
	}

	//HP�p�摜
	hp.SpriteCreate(dxCommon->GetDevice(), 50, 50, 2, Vector2(0.0f, 0.0f), false, false);
	hp.SetPosition(Vector3(28, 650, 0));
	hp.SetScale(Vector2(4 * 1, 48 * 1));
	hp.LoadTexture(spriteCommon_, 2, L"Resources/life.png", dxCommon->GetDevice());
	hp.SpriteTransferVertexBuffer(hp, 2);
	hp.SpriteUpdate(hp, spriteCommon_);

	//gameclear�̉摜
	clearGH.LoadTexture(spriteCommon_, 3, L"Resources/clear.png", dxCommon->GetDevice());
	clearGH.SpriteCreate(dxCommon->GetDevice(), 1280, 720, 3, Vector2(0.0f, 0.0f), false, false);
	clearGH.SetScale(Vector2(1280 * 1, 720 * 1));
	clearGH.SpriteTransferVertexBuffer(clearGH, 3);
	clearGH.SpriteUpdate(clearGH, spriteCommon_);

	//gameover�̉摜
	overGH.LoadTexture(spriteCommon_, 4, L"Resources/over.png", dxCommon->GetDevice());
	overGH.SpriteCreate(dxCommon->GetDevice(), 1280, 720, 4, Vector2(0.0f, 0.0f), false, false);
	overGH.SetScale(Vector2(1280 * 1, 720 * 1));
	overGH.SpriteTransferVertexBuffer(overGH, 4);
	overGH.SpriteUpdate(overGH, spriteCommon_);

	for (int i = 0; i < 10; i++) {
		lock[i].LoadTexture(spriteCommon_, 1, L"Resources/crosshair.png", dxCommon->GetDevice());
		lock[i].SpriteCreate(dxCommon->GetDevice(), 50, 50, 1, Vector2(0.0f, 0.0f), false, false);
		lock[i].SetScale(Vector2(128 * 1, 128 * 1));
		lock[i].SpriteTransferVertexBuffer(lock[i], 1);
		lock[i].SpriteUpdate(lock[i], spriteCommon_);
	}

	//fade
	fade.LoadTexture(spriteCommon_, 5, L"Resources/black.png", dxCommon->GetDevice());
	fade.SpriteCreate(dxCommon->GetDevice(), 1280, 720, 5, Vector2(0.0f, 0.0f), false, false);
	fade.SetScale(Vector2(1280 * 1, 720 * 1));
	fade.SpriteTransferVertexBuffer(fade, 5);
	fade.SpriteUpdate(fade, spriteCommon_);
	//alpha
	fadeAlpha = 1.0f;
	fade.SetAlpha(fade, fadeAlpha);
	//boosHP
	bossHP.LoadTexture(spriteCommon_, 6, L"Resources/hp.png", dxCommon->GetDevice());
	bossHP.SpriteCreate(dxCommon->GetDevice(), 1280, 720, 6, Vector2(0.0f, 0.5f), false, false);
	bossHP.SetPosition(Vector3(25, 50, 0));
	bossHP.SetScale(Vector2(2 * 1, 48 * 1));
	bossHP.SpriteTransferVertexBuffer(bossHP, 6);
	bossHP.SpriteUpdate(bossHP, spriteCommon_);


	//�p�[�e�B�N��������
	particle = Particle::LoadParticleTexture("blue.png");
	pm_ = ParticleManager::Create();
	particle_ = Particle::LoadParticleTexture("crosshair.png");
	pm = ParticleManager::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	pm->SetParticleModel(particle);
	pm_->SetParticleModel(particle_);
	//�J�������Z�b�g
	pm->SetXMViewProjection(xmViewProjection);
	pm_->SetXMViewProjection(xmViewProjection);

	////���f�������w�肵�ēǂݍ���
	//obj = new FbxObject3d;
	//obj->Initialize();
	//model = FbxLoader::GetInstance()->LoadModelFlomFile("cube");
	//obj->SetModel(model);
	//obj->SetPosition(Vector3(1, 0, -10));
	//obj->SetScale(Vector3((float)0.01, (float)0.01, (float)0.01));

	//boss
	boss = new Boss;
	boss->BossInitialize();
	boss->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 10.0f));


	//�X�v���C������_�̓ǂݍ���
	stageNum = 1;
	LoadStage(stageNum);
	LoadEnemy(stageNum);
	//�ϐ�
	isCheckPoint = false;
	isPlayable = false;
	sceneNum = TITLE;
	gameState = MAIN;
	infos.clear();
	gameTime = 150;
	cursorRotate = 0.001f;
	bossPass = 0;
}

///-----�X�V����-----///
void GameScene::Update() {
	input->Update();
	//�N���X�w�A���X�V
	GetCrosshair();
	//���Z�b�g
	if (input->TriggerKey(DIK_R)) {
		Reset();
		sceneNum = GAME;
		gameState = MAIN;
		gameTime = 150;
		railCamera->GetView()->SetEye(Vector3(-1, 0.5f, 490.0f));
		railCamera->GetView()->SetTarget(Vector3(0.0f, 0.5f, 495));
		player->SetPosition({ 0,0.5f,495 });
		Vector3 cursor = GetWorldToScreenPos(Vector3(0, 0, 0), railCamera);
		input->SetMousePos({ cursor.x,cursor.y });
	}

	Vector3 shotVec = { 0,0,0 };
	/*Vector2 playerHp_ = {0,0};*/
	switch (sceneNum)
	{
	case GameScene::TITLE:
		if (input->TriggerKey(DIK_SPACE)) {
			fadeAlpha = 0.0f;
			fade.SetAlpha(fade, fadeAlpha);
			sceneNum = GAME;
			gameState = MAIN;
			gameTime = 150;
			railCamera->GetView()->SetEye(Vector3(-1, 0.5f, 490.0f));
			railCamera->GetView()->SetTarget(Vector3(0.0f, 0.5f, 495));
			player->SetPosition({ 0,0.5f,495 });
			Vector3 cursor = GetWorldToScreenPos(Vector3(-230, 85, 0), railCamera);
			input->SetMousePos({ cursor.x,cursor.y });
			for (auto& object : objects) {
				object->Update();
			}
		}
		break;

	case GameScene::GAME:
		if (isPlayable == true) {
			//playerhp
			float playerHp_ = player->GetHP() -  (hp.GetScale().x / 4);
			if (playerHp_ > 0) {
				if ((playerHp_) > 4) {
					hp.SetScale(hp.GetScale() + Vector2(16.0f, 0.0f));
				}
				else if ((playerHp_) > 2) {
					hp.SetScale(hp.GetScale() + Vector2(8.0f, 0.0f));
				}
				else if ((playerHp_) > 1) {
					hp.SetScale(hp.GetScale() + Vector2(4.0f, 0.0f));
				}
			}
			else if (playerHp_ < 0) {
				if ((playerHp_) < 4) {
					hp.SetScale(hp.GetScale() - Vector2(8.0f, 0.0f));
				}
				else if ((playerHp_) < 2) {
					hp.SetScale(hp.GetScale() - Vector2(4.0f, 0.0f));
				}
				else if ((playerHp_) < 1) {
					hp.SetScale(hp.GetScale() - Vector2(2.0f, 0.0f));
				}
			}
	
			hp.SpriteTransferVertexBuffer(hp, 2);
			hp.SpriteUpdate(hp, spriteCommon_);
		}

		//���C���Q�[����
		switch (gameState)
		{
			//���C���Q�[��
		case GameScene::MAIN:
			//�Q�[���X�^�[�g�����o
			if (gameTime > 0) {
				//SPACE�ŉ��o�X�L�b�v
				if (input->TriggerKey(DIK_SPACE)) {
					gameTime = 1;
				}
				railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + Vector3(0, 0.0f, 0.05f));
				gameTime--;
				if (gameTime <= 0) {
					player->SetPosition(Vector3(0, -1.0f, -5.5f));
					player->SetAlpha(0.0f);
				}
				player->worldTransform_.UpdateMatrix();
			}
			//�Q�[����
			if (gameTime == 0) {
				//����s��Ԃ�����
				if (isPlayable == false) {
					isPlayable = true;
				}
				//boss���
				if (railCamera->GetOnRail() == false) {
					if (isCheckPoint == false) {
						isCheckPoint = true;
						boss->Pop();
						gameState = BOSS;
						delete railCamera;
						railCamera = new RailCamera;
						railCamera->Initialize(player);
					}
				}
				/////�f�o�b�N�p/////
				if (input->TriggerKey(DIK_B)) {
					railCamera->SetOnRail(false);
				}

				//�X�V
				railCamera->Update(player, points);
				//�_���[�W����������Ƃ��ɉ�ʃV�F�C�N
				if (player->GetIsHit() == true) {
					railCamera->ShakeCamera(-0.2f, 0.2f);
				}
			}
			break;
			//�{�X��
		case GameScene::BOSS:
			if (boss->GetTimer() > 0) {
				//player�𑀍�s��
				if (isPlayable == true) {
					isPlayable = false;
					railCamera->GetView()->SetEye(Vector3(-40, 55, -150));
				}
				//SPACE�ŉ��o�X�L�b�v
				if (input->TriggerKey(DIK_SPACE)) {
					boss->SkipMovie();
				}
				//���o
				railCamera->GetView()->SetTarget(boss->GetPosition());
				if (boss->GetTimer() == 150) {
					railCamera->GetView()->SetEye(Vector3(-80, 55, -300));
				}
				else if (boss->GetTimer() < 150) {
					railCamera->GetView()->SetEye(railCamera->GetView()->GetEye() + Vector3(0.5f, 0.0f, 0.05f));
				}
			}
			else {
				//����\��Ԃ�
				if (isPlayable == false) {
					railCamera->GetView()->SetEye(Vector3(0, 60, -95));
					railCamera->GetView()->SetTarget(Vector3(0, 52, -200));
					railCamera->GetCamera()->SetPosition(Vector3(0, 59, -100));
					railCamera->GetCamera()->SetRotation(Vector3(0, 180, 0));
					player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
					fadeAlpha = 1.0f;
					fade.SetAlpha(fade, fadeAlpha);
					isPlayable = true;
				}
				//BossHP
				float bossHp_ = boss->GetHP() - (bossHP.GetScale().x / 4);
				if (bossHp_ > 0) {
					if ((bossHp_) > 4) {
						bossHP.SetScale(bossHP.GetScale() + Vector2(16.0f, 0.0f));
					}
					else if ((bossHp_) > 2) {
						bossHP.SetScale(bossHP.GetScale() + Vector2(8.0f, 0.0f));
					}
					else if ((bossHp_) > 1) {
						bossHP.SetScale(bossHP.GetScale() + Vector2(4.0f, 0.0f));
					}
				}
				else if (bossHp_ < 0) {
					if ((bossHp_) < 4) {
						bossHP.SetScale(bossHP.GetScale() - Vector2(8.0f, 0.0f));
					}
					else if ((bossHp_) < 2) {
						bossHP.SetScale(bossHP.GetScale() - Vector2(4.0f, 0.0f));
					}
					else if ((bossHp_) < 1) {
						bossHP.SetScale(bossHP.GetScale() - Vector2(2.0f, 0.0f));
					}
				}
				bossHP.SpriteTransferVertexBuffer(bossHP, 6);
				bossHP.SpriteUpdate(bossHP, spriteCommon_);
				//�J�����X�V
				if (railCamera->GetOnRail() == false) {
					gameTime++;
					if (gameTime == 300) {
						railCamera->SetOnRail(true);
						gameTime = 0;
					}
				}
				railCamera->Update(player, bossPoint);
				railCamera->GetView()->SetTarget(boss->GetPosition());
				//�J��������
				if (bossPass == 0) {
					if (railCamera->GetPasPoint() + 1.0f > 3.0f) {
						railCamera->SetOnRail(false);
						bossPass = 1;
					}
				}
				else if (bossPass == 1) {
					if (railCamera->GetPasPoint() + 1.0f > 5.0f) {
						railCamera->SetOnRail(false);
						bossPass = 2;
					}
				}
				else if (bossPass == 2) {
					if (railCamera->GetPasPoint() + 1.0f > 7.0f) {
						railCamera->SetOnRail(false);
						bossPass = 3;
					}
				}
				else if (bossPass == 3) {
					if (railCamera->GetPasPoint() + 1.0f >= 8.96f) {
						railCamera->SetOnRail(false);
						railCamera->RailReset();
						bossPass = 0;
					}
				}
			}
			//fadein
			if (fadeAlpha > 0.0f) {
				fadeAlpha -= 0.005f;
				fade.SetAlpha(fade, fadeAlpha);
			}
			//gameclear
			if (boss->GetIsDead() == true) {
				LockedClear();
				sceneNum = CLEAR;
			}
			//�X�V
			boss->Update(player->GetWorldPos());
			//�_���[�W����������Ƃ��ɉ�ʃV�F�C�N
			if (player->GetIsHit() == true) {
				railCamera->ShakeCamera(-2.0f, 2.0f);
			}
			break;
		}
		//////////////����\�Ȃ�X�V///////////////////
		//player
		if (input->PushMouseLeft()) {
			shotVec = GetScreenToWorldPos(crosshair[0], railCamera);
		}
		if (isPlayable == true) {
			SerchEnemy();
			player->Update(shotVec, infos);
			if (gameState == BOSS && railCamera->GetOnRail() == true) {
				player->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			}
			LockedClear();
		}
		//�f�X�t���O�̗������G���폜
		enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
			return enemy_->GetIsDead();
			});
		//�G�L�����̍X�V
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->Update(player->GetWorldPos(), railCamera->GetPasPoint());
		}
		//gameover
		if (player->GetHP() == 0) {
			LockedClear();
			sceneNum = OVER;
		}
		/*	pm->Update();
			pm_->Update();*/
			//�����蔻��`�F�b�N
		collisionManager->CheckAllCollisions();
		break;

	case GameScene::CLEAR:
		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = TITLE;
		}
		break;

	case GameScene::OVER:
		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = TITLE;
		}
		break;
	}
}

void GameScene::Draw() {
#pragma region 3D�I�u�W�F�N�g�`��

	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	if (sceneNum == GAME) {
		//�w�i�I�u�W�F�N�g
		for (auto& object : objects) {
			object->Draw(railCamera->GetView());
		}
		//�G�L�����̕`��
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->EnemyDraw(railCamera->GetView());
		}
		//�{�X
		if (gameState == BOSS) {
			boss->BossDraw(railCamera->GetView());
		}
		//�v���C���[
		player->PlayerDraw(railCamera->GetView());
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

#pragma endregion

#pragma region FBX3D�I�u�W�F�N�g�`��

	// 3D�I�u�W�F�N�g�`��O����
	FbxObject3d::PreDraw(dxCommon->GetCommandList());

	/*obj->Draw(railCamera->GetView());*/

	// 3D�I�u�W�F�N�g�`��㏈��
	FbxObject3d::PostDraw();

#pragma endregion

#pragma region �p�[�e�B�N���`��

	// �p�[�e�B�N���`��O����
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	///==== �p�[�e�B�N���`�� ====///
	//�p�[�e�B�N��
	/*pm->Draw();
	pm_->Draw();*/

	// �p�[�e�B�N���`��㏈��
	ParticleManager::PostDraw();

#pragma endregion

#pragma region �X�v���C�g�`��

	// �X�v���C�g�`��O����
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);

	///=== �X�v���C�g�`�� ===///
	switch (sceneNum)
	{
	case GameScene::TITLE:
		fade.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
		titleGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
		break;

	case GameScene::GAME:
		if (gameState == BOSS) {
			fade.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
			if (boss->GetTimer() == 0) {
				//�{�X��HP
				bossHP.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
			}
		}
		if (isPlayable == true) {
			hp.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
		}
		if (isPlayable == true) {
			for (int i = 0; i < 4; i++) {
				crosshair[i].SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
			}
		}
		for (int i = 0; i < infos.size(); i++) {
			lock[i].SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
		}
		break;

	case GameScene::CLEAR:
		clearGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
		break;

	case GameScene::OVER:
		overGH.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice());
		break;
	}

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}

void GameScene::LoadStage(int stageNum) {
	points.clear();
	bossPoint.clear();

	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/csv/stagePop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

	// �P�s���ǂݍ���
	string line;
	while (getline(file, line)) {

		// �P�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		// ���p�X�p�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');


		// �擪������st�Ȃ�X�e�[�W
		if (key == "st" + num) {
			// X,Y,Z���W�ǂݍ���
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// ���W�f�[�^�ɒǉ�
			points.emplace_back(position);
		}
		if (stageNum == 10) {
			if (key == "st10") {
				// X,Y,Z���W�ǂݍ���
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// ���W�f�[�^�ɒǉ�
				points.emplace_back(position);
			}
		}
		else if (stageNum > 10) {
			if (key == "st1" + stageNum - 10) {
				// X,Y,Z���W�ǂݍ���
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// ���W�f�[�^�ɒǉ�
				points.emplace_back(position);
			}
		}
		//�擪������bo�Ȃ�{�X
		if (key == "bo" + num) {
			// X,Y,Z���W�ǂݍ���
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// ���W�f�[�^�ɒǉ�
			bossPoint.emplace_back(position);
		}
		if (stageNum == 10) {
			if (key == "st10") {
				// X,Y,Z���W�ǂݍ���
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// ���W�f�[�^�ɒǉ�
				bossPoint.emplace_back(position);
			}
		}
		else if (stageNum > 10) {
			if (key == "st1" + stageNum - 10) {
				// X,Y,Z���W�ǂݍ���
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// ���W�f�[�^�ɒǉ�
				bossPoint.emplace_back(position);
			}
		}
	}
	// �t�@�C���ƕ���
	file.close();
}

void GameScene::Reset() {
	delete player;
	delete railCamera;
	delete enemy;
	delete boss;

	//player
	player = new Player;
	player->PlayerInitialize();
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));
	player->SetPosition({ 0,0.5f,495 });
	hp.SetScale(Vector2(0, 48 * 1));
	//boss
	boss = new Boss;
	boss->BossInitialize();
	boss->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 10.0f));
	bossHP.SetScale(Vector2(12 * 1, 48 * 1));
	//camera
	railCamera = new RailCamera;
	railCamera->Initialize(player);
	//enemy
	LoadEnemy(stageNum);
	//�ϐ�
	isCheckPoint = false;
	isPlayable = false;
	cursorRotate = 0.001f;
	LockedClear();
	infos.clear();
	gameState = MAIN;
	gameTime = 150;
	bossPass = 0;
	fadeAlpha = 1.0f;
	fade.SetAlpha(fade, fadeAlpha);
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

	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/csv/EnemyPop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

	// �P�s���ǂݍ���
	string line;
	while (getline(file, line)) {

		// �P�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		// ���p�X�p�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		string word;
		getline(line_stream, word, ' ');

		if (stageNum < 10) {
			// �擪�����񂪂��Ȃ璸�_���W
			if (key == "ea" + num) {
				//�G�̐���
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				//�G�̏�����
				newEnemy->EnemyInitialize();
				////�R���C�_�[�̒ǉ�
				newEnemy->SetCollider(new SphereCollider());
				// X,Y,Z���W�ǂݍ���
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

				// ���W�f�[�^�ɒǉ�
				newEnemy->SetPosition(position);
				newEnemy->SetScale({ 0.6f,0.6f,0.6f });
				//�o�^
				enemys_.push_back(std::move(newEnemy));
			}
		}
	}
	// �t�@�C���ƕ���
	file.close();
}

void GameScene::SerchEnemy()
{
	if (input->PushKey(DIK_LSHIFT)) {
		Vector3 epos1 = GetWorldToScreenPos(boss->GetWorldPos(), railCamera);
		Vector3 cur = input->GetMousePos();
		if (boss->GetIsInvisible() == false) {
			if (pow((epos1.x - cur.x), 2) + pow((epos1.y - cur.y), 2) < 100) {
				if (boss->GetIsLocked() == false && infos.size() < 10) {
					LockInfo info;
					info.vec = boss->GetWorldPos();
					info.obj = boss;
					infos.push_back(info);
					boss->SetIsLocked(true);
				}
			}
		}

		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			Vector3 epos2 = GetWorldToScreenPos(enemy->GetWorldPos(), railCamera);
			Vector3 len = enemy->GetWorldPos() - player->GetWorldPos();
			float len_ = len.length();
			if (pow((epos2.x - cur.x), 2) + pow((epos2.y - cur.y), 2) < (30)) {
				if (enemy->GetIsLocked() == false && infos.size() < 10) {
					LockInfo info;
					info.vec = enemy->GetWorldPos();
					info.obj = enemy->GetPointer();
					infos.push_back(info);
					enemy->SetIsLocked(true);
				}
			}
		}
		if (cursorRotate < 0.005f) {
			cursorRotate += 0.0001f;
		}
	}
	else {
		if (cursorRotate > 0.001f) {
			cursorRotate -= 0.0001f;
		}
	}
	//���b�N�I���摜�̍X�V
	for (int i = 0; i < infos.size(); i++) {
		lock[i].SetScale(GetWorldToScreenScale(infos[i].obj, railCamera));
		lock[i].SetPosition(GetWorldToScreenPos(infos[i].obj->GetWorldPos(), railCamera) - (Vector3(lock[i].GetScale().x, lock[i].GetScale().y, 0) / 2));
		lock[i].SpriteUpdate(lock[i], spriteCommon_);
		lock[i].SpriteTransferVertexBuffer(lock[i], 1);
	}
}

void GameScene::LockedClear()
{
	if (player->GetIsShooted() == true) {
		if (boss->GetIsLocked() == true) {
			boss->SetIsLocked(false);
		}

		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			if (enemy->GetIsLocked() == true) {
				enemy->SetIsLocked(false);
			}
		}
		infos.clear();
	}
}

void GameScene::GetCrosshair()
{
	Vector3 mPos = input->GetMousePos();
	//�}�E�X�J�[�\���̏ꏊ�ɃN���X�w�A��\��
	if (gameState == MAIN) {
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				crosshair[i].SetPosition(mPos);
			}
			else if (i == 1) {
				crosshair[i].SetPosition(mPos - (mPos - GetWorldToScreenPos(player->GetWorldPos(), railCamera)) * 0.1f);
			}
			else if (i == 2) {
				crosshair[i].SetPosition(mPos - (mPos - GetWorldToScreenPos(player->GetWorldPos(), railCamera)) * 0.25f);
			}
			else if (i == 3) {
				crosshair[i].SetPosition(mPos - (mPos - GetWorldToScreenPos(player->GetWorldPos(), railCamera)) * 0.55f);
			}
			if (i % 2 == 0) {
				crosshair[i].SetRotation(crosshair[i].GetRotation() + cursorRotate);
			}
			else {
				crosshair[i].SetRotation(crosshair[i].GetRotation() - cursorRotate);
			}
			if (crosshair[i].GetRotation() == 1.0f) {
				crosshair[i].SetRotation(0.0f);
			}
			crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
			crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			crosshair[i].SetPosition(mPos);
			if (i % 2 == 0) {
				crosshair[i].SetRotation(crosshair[i].GetRotation() + cursorRotate);
			}
			else {
				crosshair[i].SetRotation(crosshair[i].GetRotation() - cursorRotate);
			}
			if (crosshair[i].GetRotation() == 1.0f) {
				crosshair[i].SetRotation(0.0f);
			}
			crosshair[i].SpriteTransferVertexBuffer(crosshair[i], 1);
			crosshair[i].SpriteUpdate(crosshair[i], spriteCommon_);
		}
	}
}

Vector3 GameScene::GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector3(0, 0, 1);
	}

	//�r���[�|�[�g�s�񐶐�
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width, WinApp::window_height, Vector2(0.0f, 0.0f));

	//�r���[�v���W�F�N�V�����r���[�|�[�g�����s��
	Matrix4 invViewPort = viewPort;
	invViewPort.MakeInverse();
	//�v���W�F�N�V�����s��//
	float fovAngleY = 45.0f * (3.141592f / 180.0f);;
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	//�v���W�F�N�V�����s�񐶐�
	Matrix4 projection = projection.ProjectionMat(fovAngleY, aspectRatio, 0.1f, 200.0f);
	Matrix4 invProjection = projection;
	invProjection.MakeInverse();
	//�r���[�s��//
	Matrix4 view = railCamera->GetView()->GetMatView();
	Matrix4 invView = view;
	invView.MakeInverse();
	////�����s��̋t�s����v�Z����
	Matrix4 matInverseVPV = invViewPort * invProjection * invView;
	//�X�N���[�����W�n���烏�[���h���W�n
	Matrix4 mat1, mat2;
	//w���Z
	Vector3 posNear = Vector3(sprite_.GetPosition().x, sprite_.GetPosition().y, 0);
	Vector3 posFar = Vector3(sprite_.GetPosition().x, sprite_.GetPosition().y, 1);
	posNear = mat1.transform(posNear, matInverseVPV);
	posFar = mat2.transform(posFar, matInverseVPV);

	//�}�E�X���C�̕���
	Vector3 mouseDirection = posFar - posNear;
	mouseDirection = mouseDirection.normalize();
	//�J��������Ə��I�u�W�F�N�g�̋���
	const float kDistanceTestObject = 0.05f;

	Vector3 pos = player->GetWorldPos();
	Vector3 translate = (posFar - pos) * kDistanceTestObject;

	return translate;
}

Vector3 GameScene::GetWorldToScreenPos(Vector3 pos_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector3(0, 0, 0);
	}

	//�r���[�s��//
	Matrix4 view = railCamera->GetView()->GetMatView();
	//�v���W�F�N�V�����s��//
	float fovAngleY = 45.0f * (3.141592f / 180.0f);;
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	//�v���W�F�N�V�����s�񐶐�
	Matrix4 projection = projection.ProjectionMat(fovAngleY, aspectRatio, 0.1f, 200.0f);
	//�r���[�|�[�g�s�񐶐�
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width, WinApp::window_height, Vector2(0.0f, 0.0f));

	Matrix4 matVPV = view * projection * viewPort;

	Matrix4 mat;
	Vector3 posScreen = pos_;
	posScreen = mat.transform(posScreen, matVPV);
	posScreen.z = 0;

	return posScreen;
}

Vector2 GameScene::GetWorldToScreenScale(Object3d* obj, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector2(0, 0);
	}

	Vector3 v = obj->GetPosition() - rail->GetView()->GetEye();
	v.normalize();
	float len = v.length();

	float x = 64;
	x *= obj->GetScale().x;
	float y = 64;
	y *= obj->GetScale().y;


	return Vector2(x / len, y / len);
}

void GameScene::LoadObjFromLevelEditor(const std::string& fileName) {
	JsonLoader* file = nullptr;
	LevelData* levelData = file->LoadFile(fileName);

	//�I�u�W�F�N�g�z�u
	for (auto& objectData : levelData->objects) {
		//�t�@�C��������o�^�ς݃��f��������
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model = it->second; }
		//���f�����w�肵��3DObject�𐶐�
		Object3d* newObject = Object3d::Create();
		newObject->Initialize();
		newObject->SetModel(model);
		//���W
		Vector3 pos;
		pos = Vector3(objectData.translation.x, objectData.translation.y, objectData.translation.z);
		newObject->SetPosition(pos);
		//��]�p
		Vector3 rot;
		rot = Vector3(objectData.rotation.x, objectData.rotation.y, objectData.rotation.z);
		newObject->SetRotation(rot);
		//�X�P�[��
		Vector3 scale;
		scale = Vector3(objectData.scaling.x, objectData.scaling.y, objectData.scaling.z);
		newObject->SetScale(scale);
		//�z��ɓo�^
		objects.push_back(newObject);
	}
}