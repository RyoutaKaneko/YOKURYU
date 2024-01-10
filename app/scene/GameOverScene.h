#pragma once
#include "Input.h"
#include "DirectXCommon.h"
#include "GameBaseScene.h"
#include "Sprite.h"
#include "GameSceneManager.h"
#include "GameTitleScene.h"
#include "Object3d.h"

#include <DirectXMath.h>

enum Health {
	FINE,
	WEEKNESS,
	DYING,
	DIE
};

class GameOverScene : public GameBaseScene
{
public: // メンバ関数
	// コンストラクタ
	GameOverScene();
	// デストラクタ
	~GameOverScene();

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="dXCommon"></param>
	void Draw() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize() override;

private: // メンバ変数
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Sprite* cross = nullptr;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	//score
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite overGH;
	Sprite fade;
	Sprite textGH;
	Object3d* sky = nullptr;
	Model* skyModel = nullptr;
	Player* player = nullptr;
	Object3d* stage = nullptr;
	Model* stageModel = nullptr;
	int gameTimer;
	float fadeAlpha;
	float textAlpha;

};

