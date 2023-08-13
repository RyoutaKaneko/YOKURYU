#include "Boss.h"
#include "SphereCollider.h"
#include "time.h"
#include "stdlib.h"

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
	isDead_ = false;
	isInvisible = true;
	//�^�C�}�[
	appearTimer = 0;
	bossAlpha = 0.0f;
	hp = 30;
	isHit = false;
	hitTimer = 0;
	timer = 0;
	timeCount = 0;
	state = WAIT;
	//����
	srand((unsigned int)time(NULL));
}

void Boss::Update(Vector3 velo)
{
	//�o�ꎞ
	if (appearTimer > 0) {
		if (appearTimer > 150) {
			SetPosition(GetPosition() + Vector3(0.5f, -0.1f, 0));
		}
		if (appearTimer > 100) {
			bossAlpha += 0.02f;
		}
		appearTimer--;
	}
	//��{����
	Move();
	ChangeState();

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
	if (hp == 0) {
		isDead_ = true;
	}
	//�X�V
	worldTransform_.UpdateMatrix();
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	//�J�E���g���Z�b�g
	if (timeCount == 4) {
		timeCount = 0;
	}
}

void Boss::Pop()
{
	if (isInvisible == true) {
		isInvisible = false;
	}
	appearTimer = 300;
}

void Boss::Attack()
{
	//�e�𐶐���������
//����
	std::unique_ptr<BossBullet> newBullet = std::make_unique<BossBullet>();

	//�P��													   
	newBullet->BulletInitialize(GetPosition());
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
		if (timer < 75) {
			SetPosition(GetPosition() + Vector3(0.0f, 0.01f, 0.0f));
		}
		else if (timer < 150) {
			SetPosition(GetPosition() + Vector3(0.0f, -0.01f, 0.0f));
		}
		else {
			timer = 0;
			timeCount++;
		}
		timer++;
	}
}

void Boss::ChangeState()
{
	//�ҋ@���
	if (state == WAIT) {
		if (timeCount == 4) {
			//�����ɂ��s��������
			int random = rand() % 1 + 1;
			//���I���ꂽ�s��
			state = (State)random;
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

void Boss::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class PlayerBullet";

	//���肪player�̒e
	if (strcmp(toCollisionName, str1) == 0) {
		if (isHit == false && isInvisible == false) {
			isHit = true;
			hitTimer = 30;
			hp--;
		}
	}
}

void Boss::SkipMovie()
{
	appearTimer = 0;
	SetPosition({ 0.0f,49.99f,-200.0f });
	bossAlpha = 1.0f;
}
