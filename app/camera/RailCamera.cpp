/**											  p
 * @file RaikCamera.h
 * @brief �Q�[�����̃��[���J��������Ɏg���֐��Q���܂Ƃ߂Ă���
 * @author �J�l�R_�����E�^
 */

#include "RailCamera.h"
   
const float RailCamera::PI = 3.1415f;
const float RailCamera::DEGREES = 180.0f;
const float RailCamera::DELAY = 0.05f;
const float RailCamera::ADD_DELAY = 0.02f;

RailCamera::RailCamera() {
	isEnd = false;
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//������
void RailCamera::Initialize() {
	viewProjection = new ViewProjection;
	input = Input::GetInstance();
	viewProjection->Initialize();
	camera = Object3d::Create();
	viewProjection->SetEye({ 0, 1, 505 });
	viewProjection->SetTarget({ 0.3f,0.5f,499 });
	camera->SetPosition({0,0,500});
	camera->SetRotation(Vector3(0, 0, 0));
	oldCamera = { 0,0,0 };
	isEnd = false;
	OnRail = true;
	playerMoveVel = { 0,0,0 };
	cameraDelay = { 0,0,0 };
	targetVel = 0.001f;
	cameraVel = 0.0001f;
	up = { 1,-1,1 };
}

void RailCamera::ViewUpdate() {
	viewProjection->UpdateMatrix();
}

//�X�V
void RailCamera::Update(Player* player_, std::vector<Vector3>& point) {

	if (OnRail == true) {
		Vector3 target = spline_.Update(point, targetVel);
		camera->SetPosition(splineCam.Update(point, cameraVel));
		//�ŏ���1���[�v�̂݌��݈ʒu������
		if (oldCamera.x == 0 && oldCamera.y == 0 && oldCamera.z == 0) {
			oldCamera = camera->GetPosition();
		}

		//�����x�N�g���̎擾
		GetVec(camera->GetPosition(), target);

		Vector3 camRot = camera->GetRotation();
		//�J���������ɍ��킹��Y���̉�]
		float radY = std::atan2(frontVec.x, frontVec.z);
		camera->SetRotation({ camRot.x,radY * DEGREES / PI,camRot.z });
		//�J���������ɍ��킹��X���̉�]
		Vector3 rotaVec = { frontVec.x,0,frontVec.z };
		float length = rotaVec.length();
		float radX = std::atan2(-frontVec.y, length);
		camera->SetRotation({ radX * DEGREES / PI ,radY * DEGREES / PI,camRot.z });

		if (spline_.GetIsEnd() == true) {
			OnRail = false;
		}
		Vector3 eyeTmp_ = camera->GetPosition() - frontVec * player_->GetLen();

		//�X�V
		camera->Update();
		viewProjection->SetTarget((target + frontVec));
		//player�̈ړ������ƂɃf�B���C�������čX�V
		viewProjection->SetEye((camera->GetPosition() + cameraDelay) - frontVec * player_->GetLen());

		viewProjection->UpdateMatrix();
		oldCamera = camera->GetPosition();
	}
	else {
		viewProjection->UpdateMatrix();
		camera->Update();
	}
	//cameraDelay
	playerMoveVel += (player_->GetMove() *= up);
	//�J�����̃f�B���C�����t���[���̂��߂ɕۑ�
	if (abs((playerMoveVel.x - cameraDelay.x)) > abs(DELAY)) {
		if (playerMoveVel.x > cameraDelay.x) {
			cameraDelay.x += ADD_DELAY;
		}
		else if (playerMoveVel.x < cameraDelay.x) {
			cameraDelay.x += -ADD_DELAY;
		}
		else{}
	}
	if (abs((playerMoveVel.y - cameraDelay.y)) > abs(DELAY)) {
		if (playerMoveVel.y > cameraDelay.y) {
			cameraDelay.y += ADD_DELAY;
		}
		else if (playerMoveVel.y < cameraDelay.y) {
			cameraDelay.y += -ADD_DELAY;
		}
		else {}
	}

}

void RailCamera::TitleR()
{
	Vector3 eye_ = viewProjection->GetEye();
	const float length = 1.5f;
	viewProjection->SetEye({ eye_.x,eye_.y,length });
}

void RailCamera::RailReset()
{
	splineCam.Reset();
	spline_.Reset();
}

////////////////////--------�N���X���֗��֐�--------///////////////////////

//�����x�N�g�����擾
void RailCamera::GetVec(Vector3 a, Vector3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	//Y�����x�N�g��
	yTmpVec.normalize();
	//���ʉ��x�N�g��
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//�E�x�N�g��
	rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//���x�N�g��
	leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();
	//���ʃx�N�g��(Y���W��0�ɂ���)
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();
}

void RailCamera::SetPlayer(Player* player_) {
	//�e�q�\���̃Z�b�g
	player_->GetWorldTransform().SetParent3d(&camera->GetWorldTransform());
	//�g���]���W�ϊ�
	player_->SetPosition(Vector3(0, 0, -1.5f));
	player_->SetScale(Vector3(0.3f, 0.3f, 0.3f));
}

void RailCamera::SetEye(Vector3 view) {
	this->viewProjection->SetEye(view);
	viewProjection->UpdateMatrix();
}

void RailCamera::SetTarget(Vector3 target_)
{
	this->viewProjection->SetTarget(target_);
	viewProjection->UpdateMatrix();
}

//�J�����V�F�C�N
void RailCamera::ShakeCamera(float x, float y) {

	//�����������u
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(x, y);
	std::uniform_real_distribution<float>dist2(x, y);
	Vector3 randomNum(dist(engine), dist2(engine), dist2(engine));

	viewProjection->SetEye(viewProjection->GetEye() + randomNum);
	viewProjection->UpdateMatrix();
}