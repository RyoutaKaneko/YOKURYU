#include "Enemy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"

//�f�X�g���N�^
Enemy::~Enemy() {
	delete enemyModel;
}

//������
void Enemy::EnemyInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("triangle_mat");
	enemyModel->LoadTexture("Resources/red.png");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(enemyModel);
	isDead_ = false;
	timer = 0;
	isAttack = false;
	timeCount = 0;
}

void Enemy::Update(Vector3 velo,float t) {
	float moveX;
	if (timeCount == 0) {
		moveX = -0.05f;
	}
	else if (timeCount == 1) {
		moveX = 0.05f;
	}
	else if (timeCount == 2) {
		moveX = 0.05f;
	}
	else {
		moveX = -0.05f;
	}

	if (timer < 75) {
		SetPosition(GetPosition() + Vector3(moveX, 0.005f, 0 ));
	}
	else if (timer < 150) {
		SetPosition(GetPosition() + Vector3(moveX, -0.005f, 0));
	}
	else {
		timer = 0;
		if (timeCount == 4) {
			timeCount = 0;
		}
		else {
			timeCount++;
		}
	}
	//player���G��ǂ��z������U�����Ȃ�
	if (stagePoint < t + 1.0f) {
		if (isAttack == true) {
			isAttack = false;
		}
	}
	//�U��
	if (isAttack == false) {
		Vector3 playerVec = velo - GetPosition();
		float len = playerVec.length();
		if (len < 70.0f) {
			isAttack = true;
		}
	}
	else {
		Attack();
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update(velo);
	}
	//�f�X�t���O�̗������G���폜
	bullets_.remove_if([](std::unique_ptr <EnemyBullet>& bullets_) {
		return bullets_->IsDead();
		});
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	worldTransform_.UpdateMatrix();
	timer++;
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class PlayerBullet";

	//���肪player�̒e
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}

void Enemy::Attack() {

		if (coolTime == 0) {
			//�e�𐶐���������
		//����
			std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();

			//�P��													   
			newBullet->BulletInitialize(GetPosition());
			newBullet->SetCollider(new SphereCollider(Vector3{0,0,0},0.5f));

			//�e�̓o�^										 
		   //����
			newBullet->SetPosition(GetPosition());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));


			//�N�[���^�C����ݒ�
			coolTime = 100;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

}

void Enemy::EnemyDraw(ViewProjection* viewProjection_) {
	Draw(viewProjection_);
	//�e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}