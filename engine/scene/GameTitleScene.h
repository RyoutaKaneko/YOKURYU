#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "GameBaseScene.h"
#include "GameSceneManager.h"
#include "GameScene.h"
#include "viewProjection.h"


#include <DirectXMath.h>

class GameTitleScene : public GameBaseScene
{
public: // メンバ関数
	// コンストラクタ
	GameTitleScene();

	// デストラクタ
	~GameTitleScene();

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
	// 入力
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;


	//カメラ
	ViewProjection* viewProjection = nullptr;

	//カーソル
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite title;
	Sprite black;

	int effectTime;
	bool isShow1[120];
	bool isShow2[120];
	bool effectSwitch;
	bool isNext;
	bool curHit;
	bool isUp;
	float logoTime;
	float logoY;
};
