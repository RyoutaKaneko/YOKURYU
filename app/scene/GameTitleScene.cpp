/**
 * @file GameTitleScene.h
 * @brief タイトル画面のシーンクラス
 * @author カネコ_リョウタ
 */

#include "GameTitleScene.h"

using namespace DirectX;
const float GameTitleScene::ALPHA_MAX = 1.0f;
const float GameTitleScene::SUB_ALPHA = 0.025f;
const float GameTitleScene::CIRCLE_ADD_ALPHA = 0.05f;
const float GameTitleScene::CIRCLE_ADD_SCALE = 0.2f;
const float GameTitleScene::OUTLINE_MAX = 1.04f;
const float GameTitleScene::ADD_OUTLINE = 0.0015f;
const float GameTitleScene::SUB_TITLEBACK = 0.15f;


bool GameTitleScene::isEnd = false;

GameTitleScene::GameTitleScene()
{
	//// サウンドの静的初期化
	//Sound::StaticInitialize();
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Initialize()
{
	//基盤の初期化
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dxCommon_->GetDevice());

	//titleの画像
	title.SpriteCreate(dxCommon_->GetDevice(), 0, Vector2(0.0f, 0.0f), false, false);
	title.SetScale(Vector2(1280 * 1, 720 * 1));
	title.SetPosition({ -354,-32,0 });
	title.SetAlpha(title, titleAlpha);
	title.SpriteTransferVertexBuffer(title, 0);
	title.SpriteUpdate(title, spriteCommon_);
	title.LoadTexture(spriteCommon_, 0, L"Resources/title.png", dxCommon_->GetDevice());
	//title背景
	for (int i = 0; i < TITLE_BACK_MAX; i++) {
		titleBack[i].SpriteCreate(dxCommon_->GetDevice(), i + 1, Vector2(0.0f, 0.0f), false, false);
		titleBack[i].SetScale(Vector2(1280 * 1.1, 720 * 1.7));
		titleBack[i].SetPosition({ -418,-192,0 });
		titleBack[i].SpriteTransferVertexBuffer(titleBack[i], i + 1);
		titleBack[i].SpriteUpdate(titleBack[i], spriteCommon_);
	}
	titleBack[0].LoadTexture(spriteCommon_, 1, L"Resources/titleBack.png", dxCommon_->GetDevice());
	titleBack[1].LoadTexture(spriteCommon_, 2, L"Resources/titleBack2.png", dxCommon_->GetDevice());
	titleBack[2].LoadTexture(spriteCommon_, 3, L"Resources/titleBack3.png", dxCommon_->GetDevice());
	//カーソル
	for (int i = 0; i < CURSOR_MAX; i++) {
		cursor[i].SpriteCreate(dxCommon_->GetDevice(), 4, Vector2(0.5f, 0.5f), false, false);
		cursor[i].SetScale(Vector2(48 * 1, 48 * 1));
		cursor[i].SetPosition(Input::GetInstance()->GetMousePos());
		cursor[i].SetAlpha(cursor[i], 1 - (i * 0.1f));
		cursor[i].SpriteTransferVertexBuffer(cursor[i], 4);
		cursor[i].SpriteUpdate(cursor[i], spriteCommon_);
		cursor[i].LoadTexture(spriteCommon_, 4, L"Resources/cursor.png", dxCommon_->GetDevice());
	}
	//クリック
	for (int i = 0; i < CLICK_MAX; i++) {
		click[i].SpriteCreate(dxCommon_->GetDevice(), 5 + i, Vector2(0.5f, 0.5f), false, false);
		click[i].SetScale(Vector2(312.0f * 1.2f, 52.0f * 1.2f));
		click[i].SetPosition({ 640,640,0 });
		click[i].SpriteTransferVertexBuffer(click[i], 5 + i);
		click[i].SpriteUpdate(click[i], spriteCommon_);
	}
	click[0].LoadTexture(spriteCommon_, 5, L"Resources/click1.png", dxCommon_->GetDevice());
	click[1].LoadTexture(spriteCommon_, 6, L"Resources/click2.png", dxCommon_->GetDevice());
	//カーソルエフェクト
	circle.SpriteCreate(dxCommon_->GetDevice(), 7, Vector2(0.5f, 0.5f), false, false);
	circle.SetScale(Vector2(48 * circleSize, 48 * circleSize));
	circle.SetPosition({ 0,0,0 });
	circle.SpriteTransferVertexBuffer(circle, 7);
	circle.SpriteUpdate(circle, spriteCommon_);
	circle.LoadTexture(spriteCommon_, 7, L"Resources/circle.png", dxCommon_->GetDevice());
	//フェードイン
	fade.SpriteCreate(dxCommon_->GetDevice(), 8, Vector2(0.0f, 0.0f), false, false);
	fade.SetScale(Vector2(1280 * 1, 1120 * 1));
	fade.SetPosition({ 0,-1120,0 });
	fade.SpriteTransferVertexBuffer(fade, 8);
	fade.SpriteUpdate(fade, spriteCommon_);
	fade.LoadTexture(spriteCommon_, 8, L"Resources/fade.png", dxCommon_->GetDevice());
	//loading
	loading.SpriteCreate(dxCommon_->GetDevice(), 9, Vector2(0.0f, 0.0f), false, false);
	loading.SetScale(Vector2(256 * 1, 48 * 1));
	loading.SetPosition({ 1000,640,0 });
	loading.SpriteTransferVertexBuffer(loading, 9);
	loading.LoadTexture(spriteCommon_, 9, L"Resources/loading.png", dxCommon_->GetDevice());
	//clickEffect
	clickEffect.SpriteCreate(dxCommon_->GetDevice(), 10, Vector2(0.5f, 0.5f), false, false);
	clickEffect.SetScale(Vector2(312.0f * 1.2f, 52.0f * 1.2f));
	clickEffect.SetPosition({ 640,640,0 });
	clickEffect.SpriteTransferVertexBuffer(clickEffect, 10);
	clickEffect.LoadTexture(spriteCommon_, 10, L"Resources/clickEffect.png", dxCommon_->GetDevice());
	//clickOutline
	clickOutline.SpriteCreate(dxCommon_->GetDevice(), 11, Vector2(0.5f, 0.5f), false, false);
	clickOutline.SetScale(Vector2(312.0f * 1.2f, 52.0f * 1.2f));
	clickOutline.SetPosition({ 640,640,0 });
	clickOutline.SetAlpha(clickOutline, 0.8f);
	clickOutline.SpriteTransferVertexBuffer(clickOutline, 11);
	clickOutline.LoadTexture(spriteCommon_, 11, L"Resources/clickOutline.png", dxCommon_->GetDevice());
	//black
	black.SpriteCreate(dxCommon_->GetDevice(), 12, Vector2(0.5f, 0.5f), false, false);
	black.SetScale(Vector2(1280, 720));
	black.SetPosition({ 640,360,0 });
	black.SetAlpha(black, 1.0f);
	black.SpriteTransferVertexBuffer(black, 12);
	black.LoadTexture(spriteCommon_, 12, L"Resources/black.png", dxCommon_->GetDevice());
	black.SpriteUpdate(black, spriteCommon_);
	//tips
	tips.SpriteCreate(dxCommon_->GetDevice(), 13, Vector2(0.0f, 0.0f), false, false);
	tips.SetScale(Vector2(800, 48));
	tips.SetPosition({ 150,620,0 });
	tips.SpriteTransferVertexBuffer(tips, 13);
	tips.LoadTexture(spriteCommon_, 13, L"Resources/tips.png", dxCommon_->GetDevice());

	//UI初期化
	UIs = new MyEngine::GameSceneUI();
	UIs->Initialize(dxCommon_->GetDevice());


	//player
	player = new MyEngine::Player;
	player->PlayerInitialize();
	player->SetPosition({ 0.0f,34.0f,288.0f });
	player->SetRotation({ 0,70,0 });
	player->SetScale({ 1.5f,1.5f,1.5f });

	//カメラ初期化
	viewProjection = new ViewProjection();
	viewProjection->Initialize();
	viewProjection->SetEye({ 4.0f,34.7f,298.0f });
	viewProjection->SetTarget({ 0,40,-400 });

	//モデル読み込み
	skyModel = Model::LoadFromOBJ("sky");
	seaModel = Model::LoadFromOBJ("sea");
	block01Model = Model::LoadFromOBJ("block01");
	block02Model = Model::LoadFromOBJ("block02");
	stoneModel = Model::LoadFromOBJ("stone");
	models.insert(std::make_pair("sky", skyModel));
	models.insert(std::make_pair("sea", seaModel));
	models.insert(std::make_pair("block01", block01Model));
	models.insert(std::make_pair("block02", block02Model));
	models.insert(std::make_pair("stone", stoneModel));
	//レベルエディタ読み込み
	LoadObjFromLevelEditor("title");
	floating = { 0.0f,0.01f,0.0f };
	addScale = { 2.0f,2.0f }; 
	fadeDown = { 0 ,80 , 0 };
	cameraUp = { 0, 6.0f, 0 };
	upforce = {0,1.6f,0};
	playerUp = { 0, 0.015f, 0 };
	playerDown = { 0, -0.005f, 0 };
	Downforce = { 0, -0.02f, 0 };
	gameTimer = 0;
	isBackNum = 0;
	onCursor = false;
	isNext = false;
	circleSize = 1.0f;
	clickEffectAlpha = 1.0f;
	outlineSize = 1.0f;
	circleAlpha = 1.0f;
	titleAlpha = 0.0f;
	blackAlpha = 1.0f;
	fadeTimer = 0;
	isShowTitle = false;
	isShowEnd = false;
	endTimer = 0;
	isPushEsc = false;
	isOpenEndText = false;
	rotateCircle = 0.005f;
}

void GameTitleScene::Update()
{
	//カーソルを画面内固定を解除
	if (Input::GetInstance()->GetIsVailCursor() == true) {
		Input::GetInstance()->IsClipCursor(false);
	}
	if (isPushEsc == true) {
		isPushEsc = false;
	}
	//マウス更新
	Vector3 cur = Input::GetInstance()->GetMousePos();
	//残像
	for (int i = CURSOR_MAX - 1; i > 0; i--) {
		cursor[i].SetPosition(cursor[i - 1].GetPosition());
	}
	cursor[0].SetPosition(cur);
	circle.SetPosition(cur);
	if (Input::GetInstance()->TriggerMouseLeft() == true) {
		circleSize = CIRCLE_MIN;
		circleAlpha = ALPHA_MAX;
	}
	else if (circleSize < CIRCLE_MAX) {
		circleSize += CIRCLE_ADD_SCALE;
		circleAlpha -= CIRCLE_ADD_ALPHA;
	}
	else {
		circleSize = CIRCLE_MIN;
		circleAlpha = ALPHA_MAX;
	}
	circle.SetScale(Vector2(CIRCLE_GRAPH_SCALE * circleSize, CIRCLE_GRAPH_SCALE * circleSize));
	circle.SetRotation(circle.GetRotation() + rotateCircle);
	circle.SetAlpha(circle, circleAlpha);
	circle.SpriteTransferVertexBuffer(circle, 7);
	circle.SpriteUpdate(circle, spriteCommon_);
	for (int i = 0; i < CURSOR_MAX; i++) {
		cursor[i].SpriteUpdate(cursor[i], spriteCommon_);
	}


	//タイトルふわっと描画
	if (isNext == false) {
		if (titleAlpha < ALPHA_MAX) {
			titleAlpha += CIRCLE_ADD_ALPHA;
			title.SetAlpha(title, titleAlpha);
			title.SpriteTransferVertexBuffer(title, 0);
			title.SpriteUpdate(title, spriteCommon_);
		}
		else if (titleAlpha >= ALPHA_MAX && fadeTimer < FADE_TIME) {
			fadeTimer++;
		}
		else if (fadeTimer == FADE_TIME) {
			if (blackAlpha >= 0.0f) {
				blackAlpha -= SUB_TITLEBACK;
				black.SetAlpha(black, blackAlpha);
				black.SpriteTransferVertexBuffer(black, 12);
				black.SpriteUpdate(black, spriteCommon_);
			}
			else {
				isShowTitle = true;
			}
		}

		//つぎへのアウトライン
		if (outlineSize < OUTLINE_MAX) {
			outlineSize += ADD_OUTLINE;
		}
		else {
			outlineSize = CIRCLE_MIN;
		}
		clickOutline.SetScale(clickEffect.GetScale() * outlineSize);
		clickOutline.SpriteTransferVertexBuffer(clickOutline, 11);
		clickOutline.SpriteUpdate(clickOutline, spriteCommon_);
		//クリック判定
		if (cur.x > click[0].GetPosition().x - click[0].GetScale().x / 2 && cur.x < click[0].GetPosition().x + click[0].GetScale().x / 2) {
			if (cur.y > click[0].GetPosition().y - click[0].GetScale().y / 2 && cur.y < click[0].GetPosition().y + click[0].GetScale().y / 2) {
				if (onCursor == false) {
					onCursor = true;
				}
			}
			else {
				if (onCursor == true) {
					onCursor = false;
				}
			}
		}
		else {
			if (onCursor == true) {
				onCursor = false;
			}
		}
		if (Input::GetInstance()->TriggerMouseLeft() && isShowEnd == false) {
			isNext = true;
			gameTimer = 0;
		}
		//クリック
		for (int i = 0; i < CLICK_MAX; i++) {
			click[i].SpriteUpdate(click[i], spriteCommon_);
		}

		//更新
		for (auto& object : objects) {
			object->Update();
		}
		if (gameTimer < WAIT_TITLE_ONE) {
			player->SetPosition(player->GetPosition() + floating);
		}
		else if (gameTimer < WAIT_TITLE_TWO) {
			player->SetPosition(player->GetPosition() - floating);
		}
		gameTimer++;
		if (gameTimer > WAIT_TITLE_TWO) {
			gameTimer = 0;
		}
	}
	else {
		//タイトルをすっと消す
		if (titleAlpha > 0.0f) {
			titleAlpha -= SUB_ALPHA;
			title.SetAlpha(title, titleAlpha);
			title.SpriteTransferVertexBuffer(title, 0);
			title.SpriteUpdate(title, spriteCommon_);
			for (int i = 0; i < TITLE_BACK_MAX; i++) {
				titleBack[i].SetAlpha(titleBack[i], titleAlpha);
				titleBack[i].SpriteTransferVertexBuffer(titleBack[i], i + 1);
				titleBack[i].SpriteUpdate(titleBack[i], spriteCommon_);
			}

		}
		if (clickEffectAlpha > 0) {
			clickEffectAlpha -= SUB_ALPHA;
			clickEffect.SetScale(clickEffect.GetScale() + addScale);
			clickEffect.SpriteTransferVertexBuffer(clickEffect, 10);
			clickEffect.SetAlpha(clickEffect, clickEffectAlpha);
			click[1].SetAlpha(click[1], clickEffectAlpha);
			click[1].SpriteUpdate(click[1], spriteCommon_);
		}
		clickEffect.SpriteUpdate(clickEffect, spriteCommon_);
		//シーン遷移
		if (gameTimer < NEXT_TIME_ONE) {
			player->SetPosition(player->GetPosition() + playerUp);
		}
		else if (gameTimer < NEXT_TIME_TWO) {
			player->SetPosition(player->GetPosition() + Downforce);
		}
		else if (gameTimer < NEXT_TIME_THREE) {
			player->SetPosition(player->GetPosition() + playerDown);
		}
		else if (player->GetPosition().y < PLAYER_LIMIT) {
			player->SetPosition(player->GetPosition() + upforce);
			viewProjection->SetTarget(viewProjection->GetTarget() + cameraUp);
		}
		else if (fade.GetPosition().y < 0) {
			fade.SetPosition(fade.GetPosition() +fadeDown);
			fade.SpriteUpdate(fade, spriteCommon_);
		}
		else {
			loading.SpriteUpdate(loading, spriteCommon_);
			tips.SpriteUpdate(tips, spriteCommon_);
			//次シーンへ
			GameSceneManager::GetInstance()->ChangeScene("GAMEPLAY");
		}
		gameTimer++;
	}
	//タイトル演出
	if (gameTimer % 4 == 0) {
		if (isBackNum < TITLEBACK_MAX) {
			isBackNum++;
		}
		else if (isBackNum == TITLEBACK_MAX) {
			isBackNum = 0;
		}
	}
	title.SpriteUpdate(title, spriteCommon_);
	for (int i = 0; i < TITLE_BACK_MAX; i++) {
		titleBack[i].SpriteUpdate(titleBack[i], spriteCommon_);
	}
	
	if (isShowTitle == true && isNext == false) {
		//ゲーム終了
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE) && isShowEnd == false) {
			isShowEnd = true;
			isPushEsc = true;
			isOpenEndText = true;
			endTimer = END_MAX;
		}
		if (isOpenEndText == true) {
			UIs->EndText();


			if (UIs->GetIsGameSceneReset() == true) {
				isEnd = true;
			}

			if (UIs->GetIsGameOver() == true) {
				isOpenEndText = false;
			}

			if (Input::GetInstance()->TriggerKey(DIK_ESCAPE) && isPushEsc == false) {
				isOpenEndText = false;
			}

		}
		else {
			UIs->CloseText();
			if (UIs->GetIsClose() == true) {
				isShowEnd = false;
			}
		}
	}
	

	//更新
	player->ViewUpdate();
	viewProjection->UpdateMatrix();
}

void GameTitleScene::Draw()
{
	dxCommon_->PreDraw();

	Object3d::PreDraw(dxCommon_->GetCommandList());

	player->PlayerDraw(viewProjection);
	//背景オブジェクト
	for (auto& object : objects) {
		object->Draw(viewProjection);
	}

	Object3d::PostDraw();

	//スプライト描画
	Sprite::PreDraw(dxCommon_->GetCommandList(), spriteCommon_);
	titleBack[isBackNum].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	if (isNext == false) {
		if (isShowEnd == false) {
			click[onCursor].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
		else {
			click[0].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		}
		clickOutline.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		black.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		title.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	else {
		click[1].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		clickEffect.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		fade.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		tips.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
		loading.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
	}
	title.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());

	if (isNext == false) {
		if (isShowTitle == true && isShowEnd == false) {
			circle.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
			for (int i = 0; i < CURSOR_MAX; i++) {
				cursor[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice());
			}
		}
	}

	Sprite::PostDraw();

	if (isNext == false && isShowEnd == true) {
		UIs->DrawEnd(dxCommon_->GetDevice(), dxCommon_->GetCommandList());
	}

	dxCommon_->PostDraw();
}

void GameTitleScene::Finalize()
{

}