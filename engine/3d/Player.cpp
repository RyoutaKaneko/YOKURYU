#include "Player.h"
#include "string.h"
#include "RailCamera.h"

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

void Player::Update(Vector3 cameraPos,Vector3 velo)
{
	input = Input::GetInstance();

	Move();
	Attack(cameraPos,velo);
	//�f�X�t���O�̗������G���폜
	bullets_.remove_if([](std::unique_ptr < PlayerBullet>& bullets_) {
		return bullets_->IsDead();
		});
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		if (bullet->IsDead() == false) {
			bullet->Update();
		}
	}
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

void Player::Attack(Vector3 cameraPos ,Vector3 velo) {
	
	if (input->PushKey(DIK_SPACE)) {
		if (coolTime == 0) {
			//�e�𐶐���������
		//����
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

			//�P��
			/*PlayerBullet* newBullet = new PlayerBullet();*/
			newBullet->BulletInitialize(GetPosition(),velo);

			//�e�̓o�^										 
		   //����
			newBullet->SetPosition(cameraPos + Vector3{-worldTransform_.position_.x * 1.5f,worldTransform_.position_.y,worldTransform_.position_.z });
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));

			//�P��
			/*bullet_.reset(newBullet);*/

			//�N�[���^�C����ݒ�
			coolTime = 10;
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
		if (bullet->IsDead() == false) {
			bullet->Draw(viewProjection_);
		}
	}
}