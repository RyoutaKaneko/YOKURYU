/**
 * @file Boss.h
 * @brief �{�X�S��(�X�e�[�^�X�A�s���A�`��)���܂Ƃ߂�����
 * @author �J�l�R_�����E�^
 */

#include "Boss.h"
#include "SphereCollider.h"
#include "time.h"
#include "stdlib.h"
#include "GameScene.h"

Boss::~Boss()
{
	delete bossModel;
}

void Boss::BossInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	bossModel = Model::LoadFromOBJ("fighter");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bossModel);
	SetPosition({ -75,65,-200 });
	SetScale({ 10,10,10 });
	//�p�[�c�̏�����
	for (int i = 0; i < PARTS_NUM; i++) {
		parts[i] = Create();
		parts[i]->GetWorldTransform().SetParent3d(&GetWorldTransform());
		parts[i]->SetCollider(new SphereCollider());
	}
	parts[0]->SetPosition({ -2.0f,0.0f,-0.5f });
	parts[1]->SetPosition({ 2.0f,0.0f,-0.5f });
	parts[2]->SetPosition({ 0.0f,0.0f,1.0f });
	parts[3]->SetPosition({ -3.0f,0.0f,-1.0f });
	parts[4]->SetPosition({ 3.0f,0.0f,-1.0f });

	isDead_ = false;
	isInvisible = true;
	//�^�C�}�[
	appearTimer = 0;
	bossAlpha = 0.0f;
	hp = 300;
	isHit = false;
	hitTimer = 0;
	timer = 0;
	timeCount = 0;
	state = WAIT;
	slainTimer = 0;
	isSlained = false;
	//����
	srand((unsigned int)time(NULL));
}

void Boss::Update(Vector3 velo)
{
	//�o�ꎞ
	if (appearTimer > 0) {
		if (appearTimer > 75) {
			SetPosition(GetPosition() + Vector3(1.0f, -0.2f, 0));
		}
		if (bossAlpha < 1.0f) {
			bossAlpha += 0.04f;
		}
		appearTimer--;
	}
	//��{����
	Move();
	if (appearTimer == 0) {
		ChangeState();
	}

	//�e������Ȃ�X�V
	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Update(velo);
	}
	//�f�X�t���O�̗������G���폜
	bullets_.remove_if([](std::unique_ptr <BossBullet>& bullets_) {
		return bullets_->IsDead();
		});
	
	 //�_���[�W����
	if (hitTimer > 0) {
		hitTimer--;
		if (hitTimer == 0) {
			isHit = false;
		}
	}
	//HP��0�Ȃ玀�S
	if (hp <= 0) {
		isDead_ = true;
	}
	//�X�V
	//Vector3 rot = velo - GetPosition();
	//SetRotation({0,rot.x,0});
	GetWorldTransform().UpdateMatrix();
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	//�{�X�p�[�c�A�b�v�f�[�g
	for (int i = 0; i < PARTS_NUM; i++) {
		parts[i]->Update();
	}
}

void Boss::Pop()
{
	if (isInvisible == true) {
		isInvisible = false;
	}
	appearTimer = 150;
}

void Boss::Attack()
{
	//�e�𐶐���������
	std::unique_ptr<BossBullet> newBullet = std::make_unique<BossBullet>();

	//�P��													   
	newBullet->BulletInitialize();
	newBullet->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 5.0f));

	//�e�̓o�^										 
   //����
	newBullet->SetPosition(GetPosition());
	newBullet->SetScale({ 1.2f,1.2f,1.2f });
	bullets_.push_back(std::move(newBullet));
}

void Boss::Move()
{
	//�{�X�o���
	if (isInvisible == false) {
		if (timer < 35) {
			SetPosition(GetPosition() + Vector3(0.0f, 0.01f, 0.0f));
		}
		else if (timer < 70) {
			SetPosition(GetPosition() + Vector3(0.0f, -0.01f, 0.0f));
		}
		else {
			timer = 0;
		}
		timer++;
	}
}

void Boss::ChangeState()
{
	//�ҋ@���
	if (state == WAIT) {
		if (timeCount >= 125) {
			//�����ɂ��s��������
			/*int random = rand() % 1 + 1;*/
			//���I���ꂽ�s��
			/*state = (State)random;*/
			state = SHOT;
			timeCount = 0;
		}	
		else {
			timeCount++;
		}
	}
	//�ˌ����
	else if (state == SHOT) {
		Attack();
		state = WAIT;
	}
}

void Boss::BossDraw(ViewProjection* viewProjection_)
{
	Draw(viewProjection_, bossAlpha);
	//�e�`��
	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

void Boss::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class PlayerBullet";

	//���肪player�̒e
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isHit == false && isInvisible == false) {
			isHit = true;
			hitTimer = 30;
			hp-= 5;
			for (int i = 0; i < PARTS_NUM; i++) {
				if (parts[i]->GetIsLocked() == true) {
					parts[i]->SetIsLocked(false);
					hp -= 5;
				}
			}
		}
	}
}

void Boss::SkipMovie()
{
	appearTimer = 0;
	SetPosition({ 0.0f,49.99f,-200.0f });
	bossAlpha = 1.0f;
}

void Boss::SlainUpdate()
{
	//�����������u
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(-5.0f, 5.0f);
	Vector3 randomNum(dist(engine), dist(engine), dist(engine));

	if (slainTimer < 30) {
		SetRotation(randomNum);		
	}
	else{
		isSlained = true;
	}

	GetWorldTransform().UpdateMatrix();
	slainTimer++;
}
