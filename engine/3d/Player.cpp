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
	SetPosition(Vector3(0, 0, -790));

	hp = 3;
	len = 6.0f;

	return true;
}

void Player::Update(std::vector <Vector3>& point)
{
	input = Input::GetInstance();

	
}

void Player::Move(std::vector <Vector3>& point)
{
	
}