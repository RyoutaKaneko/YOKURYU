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

	hp = 5;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;
	isHit = false;
	hitTime = 0;

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

	if (isHit == true) {
		hitTime++;
		if (hitTime == 15) {
			hitTime = 0;
			isHit = false;
		}
	}

	worldTransform_.UpdateMatrix();
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };

	//player�ړ�
	if (input->PushKey(DIK_W)) {
		if (input->PushKey(DIK_A) == true && input->PushKey(DIK_D) == false) {
			move = { -0.03f, 0.03f, 0 };
		}
		else if (input->PushKey(DIK_A) == false && input->PushKey(DIK_D) == true) {
			move = { 0.03f, 0.03f, 0 };
		}
		else {
			move = { 0, 0.04f, 0 };
		}
	}
	else if (input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { -0.03f, -0.03f, 0 };
		}
		else {
			move = { -0.04f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_D)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { 0.03f, -0.03f, 0 };
		}
		else {
			move = { 0.04f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_S)) {
		move = { 0, -0.04f, 0 };
	}

	//player�ӂ�ӂ�
	if (pTimer < 75) {
		move += Vector3(0, 0.005f, 0);
	}
	else if (pTimer < 150) {
		move += Vector3(0, -0.005f, 0);
	}
	else {
		pTimer = 0;
	}

	Vector3 tmp = GetPosition() + move;
	//
	if (abs(tmp.x) <= 3.0f) {
		if (tmp.y >= -1.5f && tmp.y <= 2.0f) {
			SetPosition(GetPosition() + move);
		}
	}
	pTimer++;
}

void Player::Attack(Vector3 velo) {
	
	if (input->PushMouseLeft()) {
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
			coolTime = 8;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::PlayerDraw(ViewProjection* viewProjection_) {
	if (hitTime % 5 == 0) {
		Draw(viewProjection_);
	}
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Enemy";
	const char* str2 = "class EnemyBullet";

	//���肪enemy
	if (strcmp(toCollisionName, str1) == 0) {
	}
	//���肪enemy�̒e
	if (strcmp(toCollisionName, str2) == 0) {
		if (isHit == false) {
			hp--;
			isHit = true;
		}
	}
}