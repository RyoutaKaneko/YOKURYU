#include "Player.h"
#include "string.h"
#include "RailCamera.h"
#include "SphereCollider.h"

//�f�X�g���N�^
Player::~Player() {
	delete playerModel;
}

//������
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
		return false;
	}

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	playerModel = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, 0));

	hp = 3;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;

	return true;
}

void Player::Update(Vector3 velo)
{
	input = Input::GetInstance();

	Move();
	Attack(velo);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}
	//�f�X�t���O�̗������G���폜
	bullets_.remove_if([](std::unique_ptr < PlayerBullet>& bullets_) {
		return bullets_->IsDead();
		});
	//player�ӂ�ӂ�
	if (pTimer < 75) {
		SetPosition(GetPosition() + Vector3(0, 0.005f, 0));
	}
	else if (pTimer < 150) {
		SetPosition(GetPosition() + Vector3(0, -0.005f, 0));
	}
	else {
		pTimer = 0;
	}

	worldTransform_.UpdateMatrix();
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	pTimer++;
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };

	//player�ړ�
	if (input->PushKey(DIK_W)) {
		if (input->PushKey(DIK_A) == true && input->PushKey(DIK_D) == false) {
			move = { -0.02f, 0.02f, 0 };
		}
		else if (input->PushKey(DIK_A) == false && input->PushKey(DIK_D) == true) {
			move = { 0.02f, 0.02f, 0 };
		}
		else {
			move = { 0, 0.03f, 0 };
		}
	}
	else if (input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { -0.02f, -0.02f, 0 };
		}
		else {
			move = { -0.03f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_D)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { 0.02f, -0.02f, 0 };
		}
		else {
			move = { 0.03f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_S)) {
		move = { 0, -0.03f, 0 };
	}

	Vector3 tmp = GetPosition() + move;
	//
	if (abs(tmp.x) <= 3.5f) {
		if (abs(tmp.y) <= 2.0f) {
			SetPosition(GetPosition() + move);
		}
	}
}

void Player::Attack(Vector3 velo) {
	
	if (input->PushKey(DIK_SPACE)) {
		if (coolTime == 0) {
			//�e�𐶐���������
		//����
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

			//�P��													   
			newBullet->BulletInitialize(GetPosition(),velo);
			newBullet->SetCollider(new SphereCollider());

			//�e�̓o�^										 
		   //����
			newBullet->SetPosition(GetWorldPos());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));


			//�N�[���^�C����ݒ�
			coolTime = 12;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::PlayerDraw(ViewProjection* viewProjection_) {
	Draw(viewProjection_);
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

Vector3 Player::GetWorldPos() {
	Vector3 worldPos{ 0,0,0 };

	//���[���h�s�񂩂���W���擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Enemy";

	//���肪enemy
	if (strcmp(toCollisionName, str1) == 0) {
		int a = 0;
	}
}