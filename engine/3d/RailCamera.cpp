#include "RailCamera.h"

RailCamera::RailCamera() {
	isEnd = false;
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//������
void RailCamera::Initialize(Player* player_) {
	viewProjection = new ViewProjection;
	input = Input::GetInstance();
	viewProjection->Initialize();
	camera = Object3d::Create();
	viewProjection->eye = { 0, 1, 505 };
	viewProjection->target = { 0.3f,0.5f,499 };
	camera->SetPosition({0,0,500});
	camera->SetRotation(Vector3(0, 0, 0));
	SetPlayer(player_);
	oldCamera = { 0,0,0 };
	isEnd = false;
	OnRail = true;
}

void RailCamera::ViewUpdate() {
	viewProjection->UpdateMatrix();
}

//�X�V
void RailCamera::Update(Player* player_, std::vector<Vector3>& point) {

	if (OnRail == true) {
		Vector3 target_ = spline_.Update(point, 0.00001f);
		camera->SetPosition(splineCam.Update(point, 0.0f));
		//�ŏ���1���[�v�̂݌��݈ʒu������
		if (oldCamera.x == 0 && oldCamera.y == 0 && oldCamera.z == 0) {
			oldCamera = camera->GetPosition();
		}

		//�����x�N�g���̎擾
		GetVec(camera->GetPosition(), target_);

		//�J���������ɍ��킹��Y���̉�]
		float radY = std::atan2(frontVec.x, frontVec.z);
		camera->SetRotationY(radY * 180.0f / 3.1415f);
		//�J���������ɍ��킹��X���̉�]
		Vector3 rotaVec = { frontVec.x,0,frontVec.z };
		float length = rotaVec.length();
		float radX = std::atan2(-frontVec.y, length);
		camera->SetRotationX(radX * 180.0f / 3.1415f);

		if (spline_.GetIsEnd() == true) {
			OnRail = false;
		}
		Vector3 eyeTmp = camera->GetPosition() - frontVec * player_->GetLen();

		//�X�V
		camera->Update();
		viewProjection->target = ((target_ + frontVec));
		viewProjection->eye = (camera->GetPosition() - frontVec * player_->GetLen());
		if (viewProjection->eye.y > (eyeTmp.y + 1)) {
			viewProjection->eye.y += 0.05f;
		}

		viewProjection->UpdateMatrix();
		oldCamera = camera->GetPosition();
	}
	else {
		viewProjection->UpdateMatrix();
		camera->Update();
	}
}

void RailCamera::TitleR(Player* player_)
{
	viewProjection->eye.z -= 1.5;
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
	player_->worldTransform_.SetParent3d(&camera->worldTransform_);
	//�g���]���W�ϊ�
	player_->SetPosition(Vector3(0, 0, -1.5f));
	player_->SetScale(Vector3(0.3f, 0.3f, 0.3f));
}

void RailCamera::SetEye(Vector3 view) {
	this->viewProjection->eye = view;
	viewProjection->UpdateMatrix();
}

void RailCamera::SetTarget(Vector3 target_)
{
	this->viewProjection->target = target_;
	viewProjection->UpdateMatrix();
}

void RailCamera::ShakeCamera(float x, float y) {

	//�����������u
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(x, y);
	std::uniform_real_distribution<float>dist2(x, y);


	viewProjection->eye = viewProjection->eye + Vector3(dist(engine), dist2(engine), dist2(engine));
	viewProjection->UpdateMatrix();
}