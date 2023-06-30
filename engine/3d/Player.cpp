#include "Player.h"
#include "string.h"

//デストラクタ
Player::~Player() {
	delete playerModel;
}

//初期化
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
		return false;
	}

	Initialize();

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("triangle_mat");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, 0));

	hp = 3;
	len = 6.0f;

	return true;
}

void Player::Update()
{
	input = Input::GetInstance();

	Vector3 move = {0,0,0};

	//player移動
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

	worldTransform_.UpdateMatrix();
}

void Player::Move(std::vector <Vector3>& point)
{
	
}