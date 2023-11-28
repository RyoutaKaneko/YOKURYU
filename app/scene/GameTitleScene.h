/**
 * @file GameTitleScene.cpp
 * @brief タイトル画面のシーンクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "GameBaseScene.h"
#include "GameSceneManager.h"
#include "GameScene.h"
#include "viewProjection.h"
#include "Player.h"
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

	/// <summary>
	/// 終了リクエスト
	/// </summary>
	static bool GetIsEnd() { return isEnd; }

private: // メンバ変数
	// 入力
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;


	//カメラ
	ViewProjection* viewProjection = nullptr;

	//定数
	static const int TITLE_BACK_MAX = 3;
	static const int CURSOR_MAX = 9;
	static const int CLICK_MAX = 2;
	static const float ALPHA_MAX;

	//カーソル
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite title;
	Sprite titleBack[TITLE_BACK_MAX];
	Sprite cursor[CURSOR_MAX];
	Sprite click[CLICK_MAX];
	Sprite circle;
	Sprite fade;
	Sprite loading;
	Sprite clickEffect;
	Sprite clickOutline;
	Sprite black;
	Sprite tips;
	//UI
	GameSceneUI* UIs = nullptr;

	Model* skyModel = nullptr;
	Model* seaModel = nullptr;
	Model* block01Model = nullptr;
	Model* block02Model = nullptr;
	Model* stoneModel = nullptr;
	Player* player = nullptr;

	int gameTimer;
	int isBackNum;
	int endTimer;
	bool onCursor;
	bool isNext;
	float circleSize;
	float clickEffectAlpha;
	float outlineSize;
	float circleAlpha;
	float blackAlpha;
	float titleAlpha;
	int fadeTimer;
	bool isShowTitle;
	bool isShowEnd;
	static bool isEnd;
	bool isPushEsc;
	bool isOpenEndText;
};
