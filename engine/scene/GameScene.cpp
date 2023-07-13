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
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));
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
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon->GetDevice());

	//�؂̉摜
	wood.LoadTexture(spriteCommon_, 0, L"Resources/wood.png", dxCommon->GetDevice());
	wood.SetColor(Vector4(1, 1, 1, 1));
	wood.SpriteCreate(dxCommon->GetDevice(), 50, 50, 0, Vector2(0.0f, 0.0f), false, false);
	wood.SetPosition(Vector3(0, 0, 0));
	wood.SetScale(Vector2(128 * 1, 128 * 1));
	wood.SetRotation(0.0f);
	wood.SpriteTransferVertexBuffer(wood, 0);
	wood.SpriteUpdate(wood, spriteCommon_);

	//�N���X�w�A�̉摜
	crosshair.LoadTexture(spriteCommon_, 1, L"Resources/crosshair.png", dxCommon->GetDevice());
	crosshair.SetColor(Vector4(1, 1, 1, 1));
	crosshair.SpriteCreate(dxCommon->GetDevice(), 50, 50, 1, Vector2(0.0f, 0.0f), false, false);
	crosshair.SetPosition(Vector3(1100, 0, 0));
	crosshair.SetScale(Vector2(64 * 1, 64 * 1));
	crosshair.SetRotation(0.0f);
	crosshair.SpriteTransferVertexBuffer(crosshair, 1);
	crosshair.SpriteUpdate(crosshair, spriteCommon_);

	//HP�p�摜
	for (int i = 0; i < 5; i++) {
		hp[i].LoadTexture(spriteCommon_, 2, L"Resources/hitPoint.png", dxCommon->GetDevice());
		hp[i].SetColor(Vector4(1, 1, 1, 1));
		hp[i].SpriteCreate(dxCommon->GetDevice(), 50, 50, 2, Vector2(0.0f, 0.0f), false, false);
		hp[i].SetPosition(Vector3(0 + i * 68.0f, 0, 0));
		hp[i].SetScale(Vector2(64 * 1, 64 * 1));
		hp[i].SetRotation(0.0f);
		hp[i].SpriteTransferVertexBuffer(hp[i], 2);
		hp[i].SpriteUpdate(hp[i], spriteCommon_);
	}

	//�p�[�e�B�N��������
	particle = Particle::LoadParticleTexture("wood.png");
	pm_ = ParticleManager::Create();
	particle_ = Particle::LoadParticleTexture("crosshair.png");
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
	//�f�o�b�N�J����
	/*if (input->PushMouseRight()) {
		Vector3 v = input->GetMouseVelo();
		v.x *= -1;
		railCamera->GetView()->SetTarget(railCamera->GetView()->GetTarget() + v);
	}*/

	//�}�E�X�J�[�\���̏ꏊ�ɃN���X�w�A��\��
	Vector3 v = input->GetMousePos();
	crosshair.SetPosition( v - Vector3(32, 32, 0));
	/*crosshair.SetPosition(Vector3(640, 360, 0));*/
	crosshair.SpriteUpdate(crosshair, spriteCommon_);
	crosshair.SpriteTransferVertexBuffer(crosshair, 1);

	//�����蔻��`�F�b�N
	collisionManager->CheckAllCollisions();

	if (player->GetHP() == 0) {
		Reset();
	}

	//�X�V
	if (railCamera->GetIsEnd() == false) {
		railCamera->Update(player, points);
	}
	/*railCamera->ViewUpdate();*/
	Vector3 shotVec = { 0,0,0 };
	if (input->PushMouseLeft()) {
		shotVec = GetScreenToWorldPos(crosshair, railCamera);
	}
	player->Update(shotVec);
	//�f�X�t���O�̗������G���폜
	enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
		return enemy_->GetIsDead();
		});
	//�G�L�����̍X�V
	for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		enemy->Update(player->GetWorldPos(),railCamera->GetPasPoint());
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
		enemy->EnemyDraw(railCamera->GetView());
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
	/*wood.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), wood.vbView);*/
	for (int i = 0; i < player->GetHP(); i++) {
		hp[i].SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), hp[i].vbView);
	}
	crosshair.SpriteDraw(dxCommon->GetCommandList(), spriteCommon_, dxCommon->GetDevice(), crosshair.vbView);

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
	player->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.7f));

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

Vector3 GameScene::GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail)
{
	if (rail == nullptr) {
		return Vector3(0,0,1);
	}

	//�r���[�|�[�g�s�񐶐�
	Matrix4 viewPort = viewPort.ViewPortMat(WinApp::window_width,WinApp::window_height,Vector2(0.0f,0.0f));

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
	const float kDistanceTestObject = 0.01f;

	Vector3 pos = player->GetWorldPos();
	Vector3 translate = (posFar - posNear) * kDistanceTestObject;

	return translate;
}