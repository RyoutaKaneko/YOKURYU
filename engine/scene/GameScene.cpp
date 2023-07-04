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
	player->SetCollider(new SphereCollider);
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
	obj->SetScale(Vector3((float)0.01, (float)0.01, (float)0.01));

	//�X�v���C������_�̓ǂݍ���
	stageNum = 1;
	LoadStage(stageNum);
	LoadEnemy(stageNum);

}

///-----�X�V����-----///
void GameScene::Update() {
	input->Update();

	////�p�[�e�B�N��
	//if (input->PushKey(DIK_SPACE))
	//{
	//	pm->Fire(particle, 30, 0.2f, 0, 2, { 8.0f, 0.0f });
	//	pm_->Fire(particle_, 30, 0.2f, 0, 1, { 8.0f, 0.0f });
	//}

	//���Z�b�g
	if (input->TriggerKey(DIK_R)) {
		Reset();
	}

	//�����蔻��`�F�b�N
	collisionManager->CheckAllCollisions();

	//�X�V
	if (railCamera->GetIsEnd() == false) {
		railCamera->Update(player, points);
	}
	player->Update(railCamera->GetFrontVec());
	//�f�X�t���O�̗������G���폜
	enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
		return enemy_->GetIsDead();
		});
	//�G�L�����̍X�V
	for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Update();
	}
	sky->Update();
	floor->Update();
	pm->Update();
	pm_->Update();
	obj->Update();
}

void GameScene::Draw() {
#pragma region 3D�I�u�W�F�N�g�`��

// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	sky->Draw(railCamera->GetView());
	floor->Draw(railCamera->GetView());
	//�G�L�����̕`��
	for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw(railCamera->GetView());
	}
	player->PlayerDraw(railCamera->GetView());

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
	pm->Draw();
	pm_->Draw();

	// �p�[�e�B�N���`��㏈��
	ParticleManager::PostDraw();

#pragma endregion

#pragma region �X�v���C�g�`��

	// �X�v���C�g�`��O����
	Sprite::PreDraw(dxCommon->GetCommandList(), spriteCommon_);

	///=== �X�v���C�g�`�� ===///
	/*wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);
	reimu.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), reimu.vbView);*/

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}

void GameScene::LoadStage(int stageNum) {
	points.clear();

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


		// �擪�����񂪂��Ȃ璸�_���W
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
	}
	// �t�@�C���ƕ���
	file.close();
}

void GameScene::Reset() {
	delete player;
	delete railCamera;
	delete enemy;

	//player
	player = new Player;
	player->PlayerInitialize();

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
		pointsL[i] += Vector3(-4, 0, 0);
		pointsR[i] += Vector3(4, 0, 0);
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
					position = spline.EnemyPosition(pointsL, t);
				}
				else if (word.find("M") == 0)
				{
					line_stream >> t;
					position = spline.EnemyPosition(points, t);
				}
				else if (word.find("R") == 0)
				{
					line_stream >> t;
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