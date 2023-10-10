#include "Player.h"
#include "string.h"
#include "RailCamera.h"
#include "SphereCollider.h"
#include"Input.h"

//�f�X�g���N�^
Player::~Player() {
	delete playerModel;
}

//������
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
		return false;
	}

	input = Input::GetInstance();
	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	playerModel = Model::LoadFromOBJ("box");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, 500));
	SetRotation(Vector3(0, 270, 0));

	hp = 100;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;
	isHit = false;
	isShooted = false;
	hitTime = 0;
	alpha = 1.0f;
	energy = 0;
	isUltimate = false;
	ultTime = 0;
	pos_ = { 0,0,0 };
	rot_ = { 0,0,0 };

	return true;
}

void Player::Update(Vector3 velo, std::vector<LockInfo>& info)
{
	if (isShooted == true) {
		isShooted = false;
	}


	Move();
	LockAttack(info);
	Attack(velo);
	//ULT
	if (energy >= 100) {
		if (input->TriggerKey(DIK_Q)) {
			if (isUltimate == false) {
				pos_ = GetPosition();
				rot_ = GetRotation();
				isUltimate = true;
			}
		}
	}
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		if (bullet->GetIsHoming() == true) {
			bullet->HomingVec();
		}
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
	if (alpha < 1.0f) {
		alpha += 0.01f;
	}
}

void Player::Move()
{
	move = { 0,0,0 };

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

	Vector3 floating(0, 0, 0);
	//player�ӂ�ӂ�
	if (pTimer < 75) {
		floating += Vector3(0, 0.005f, 0);
	}
	else if (pTimer < 150) {
		floating += Vector3(0, -0.005f, 0);
	}
	else {
		pTimer = 0;
	}

	Vector3 tmp = GetPosition() + move + floating;
	//
	if (abs(tmp.x) <= 3.0f) {
		if (tmp.y >= -1.5f && tmp.y <= 2.0f) {
			if (GetPosition().z < -1.6f) {
				SetPosition(GetPosition() + move + floating + Vector3(0.0f,0.0f,0.05f));
			}
			else {
				SetPosition(GetPosition() + move + floating);
			}
		}
	}
	else {
		move = { 0,0,0 };
	}
	pTimer++;
}

void Player::Attack(Vector3 velo) {
	
	if (Input::GetInstance()->PushMouseLeft()) {
		if (coolTime == 0) {
			//�e�𐶐���������
		//����
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

			//�P��
			newBullet->BulletInitialize(velo + Vector3(0,0.05f,0));
			newBullet->SetCollider(new SphereCollider());

			//�e�̓o�^
		   //����
			newBullet->SetPosition(GetWorldPos());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));


			//�N�[���^�C����ݒ�
			coolTime = 6;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::LockAttack(std::vector<LockInfo>& info)
{
	if (Input::GetInstance()->TriggerMouseRight() == true) {
		for (int i = 0; i < info.size(); i++) {
			//�e�𐶐���������
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			Vector3 shotVec = (info[i].vec - GetWorldPos());
			//�P��
			newBullet->BulletInitialize(shotVec);
			newBullet->SetCollider(new SphereCollider());

			//�e�̓o�^
		   //����
			newBullet->SetPosition(GetWorldPos());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			newBullet->SetLock(info[i].obj);
			newBullet->SetisHoming(true);
			bullets_.push_back(std::move(newBullet));
		}
		isShooted = true;
	}
}

void Player::Ultimate()
{
	if (ultTime > 50 && ultTime < 175) {
		SetPosition(GetPosition() + Vector3(0.0f, 0.05f, 0.0f));
	}
	else if (ultTime == 175) {
		ultTime = 0;
		isUltimate = false;
		energy = 0;
	}
	worldTransform_.UpdateMatrix();
	ultTime++;
}

void Player::PlayerDraw(ViewProjection* viewProjection_) {
	if (hitTime % 5 == 0) {
		Draw(viewProjection_,alpha);
	}
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

void Player::BackRail()
{
	SetPosition(pos_);
	SetRotation(rot_);
}

void Player::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Enemy";
	const char* str2 = "class EnemyBullet";
	const char* str3 = "class BossBullet";
	const char* str4 = "class Energy";

	//���肪enemy
	if (strcmp(toCollisionName, str1) == 0) {
	}
	//���肪enemy�̒e
	if (strcmp(toCollisionName, str2) == 0) {
		if (isHit == false) {
			hp-=10;
			isHit = true;
		}
	}
	//���肪boss�̒e
	if (strcmp(toCollisionName, str3) == 0) {
		if (isHit == false) {
			hp-=25;
			isHit = true;
		}
	}

	//���肪energy
	if (strcmp(toCollisionName, str4) == 0) {
		if (energy < 100) {
			energy += 5;
		}
	}
}