#include "GameSceneUI.h"

void GameSceneUI::Initialize(ID3D12Device* device)
{
	// スプライトの初期化
// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(device);


	//HP用画像
	hp.SpriteCreate(device, 2, Vector2(0.0f, 0.0f), false, false);
	hp.SetPosition(Vector3(28, 650, 0));
	hp.SetScale(Vector2(4 * 1, 48 * 1));
	hp.LoadTexture(spriteCommon_, 2, L"Resources/life.png", device);
	hp.SpriteTransferVertexBuffer(hp, 2);
	hp.SpriteUpdate(hp, spriteCommon_);
	//boosHP
	bossHP.LoadTexture(spriteCommon_, 6, L"Resources/hp.png", device);
	bossHP.SpriteCreate(device, 6, Vector2(0.0f, 0.5f), false, false);
	bossHP.SetPosition(Vector3(25, 50, 0));
	bossHP.SetScale(Vector2(2 * 1, 48 * 1));
	bossHP.SpriteTransferVertexBuffer(bossHP, 6);
	bossHP.SpriteUpdate(bossHP, spriteCommon_);
	//gage
	gage.LoadTexture(spriteCommon_, 7, L"Resources/green.png", device);
	gage.SpriteCreate(device, 7, Vector2(0.0f, 0.5f), false, false);
	gage.SetPosition(Vector3(28, 618, 0));
	gage.SetScale(Vector2(2 * 1, 18 * 1));
	gage.SpriteTransferVertexBuffer(gage, 7);
	gage.SpriteUpdate(gage, spriteCommon_);
	//
	gageBack.LoadTexture(spriteCommon_, 8, L"Resources/green.png", device);
	gageBack.SpriteCreate(device, 8, Vector2(0.0f, 0.5f), false, false);
	gageBack.SetPosition(Vector3(28, 618, 0));
	gageBack.SetScale(Vector2(358, 18 * 1));
	gageBack.SpriteTransferVertexBuffer(gageBack, 8);
	gageBack.SpriteUpdate(gageBack, spriteCommon_);
	//
	hpBack.SpriteCreate(device, 9, Vector2(0.0f, 0.0f), false, false);
	hpBack.SetPosition(Vector3(28, 650, 0));
	hpBack.SetScale(Vector2(396, 48 * 1));
	hpBack.LoadTexture(spriteCommon_, 9, L"Resources/life.png", device);
	hpBack.SpriteTransferVertexBuffer(hpBack, 9);
	hpBack.SpriteUpdate(hpBack, spriteCommon_);
	//hpフレーム
	hpFrame.SpriteCreate(device, 11, Vector2(0.5f, 0.5f), false, false);
	hpFrame.SetScale(Vector2(428 * 1, 127 * 1));
	hpFrame.SetPosition(Vector3(226, 851, 0));
	hpFrame.SpriteTransferVertexBuffer(hpFrame, 11);
	hpFrame.SpriteUpdate(hpFrame, spriteCommon_);
	hpFrame.LoadTexture(spriteCommon_, 11, L"Resources/hpFrame.png", device);
	//攻撃UI
	attackUI.SpriteCreate(device, 12, Vector2(0.5f, 0.0f), false, false);
	attackUI.SetScale(Vector2(100 * 1, 100 * 1));
	attackUI.SetPosition(Vector3(1020, 800, 0));
	attackUI.SetAlpha(attackUI, 0.6f);
	attackUI.SpriteTransferVertexBuffer(attackUI, 12);
	attackUI.SpriteUpdate(attackUI, spriteCommon_);
	attackUI.LoadTexture(spriteCommon_, 12, L"Resources/attackUI.png", device);
	//攻撃Icon
	attackIcon.SpriteCreate(device, 13, Vector2(0.5f, 0.0f), false, false);
	attackIcon.SetScale(attackUI.GetScale() - Vector2(16, 16));
	attackIcon.SetPosition(Vector3(1020, 808, 0));
	attackIcon.SetAlpha(attackIcon, 0.6f);
	attackIcon.SpriteTransferVertexBuffer(attackIcon, 13);
	attackIcon.SpriteUpdate(attackIcon, spriteCommon_);
	attackIcon.LoadTexture(spriteCommon_, 13, L"Resources/attackIcon.png", device);
	//ロックUI
	lockUI.SpriteCreate(device, 14, Vector2(0.5f, 0.0f), true, false);
	lockUI.SetScale(Vector2(160 * 1, 160 * 1));
	lockUI.SetPosition(Vector3(1160, 740, 0));
	lockUI.SetAlpha(lockUI, 0.6f);
	lockUI.SpriteTransferVertexBuffer(lockUI, 14);
	lockUI.SpriteUpdate(lockUI, spriteCommon_);
	lockUI.LoadTexture(spriteCommon_, 14, L"Resources/attackUI.png", device);
	//ロックIcon
	lockIcon.SpriteCreate(device, 15, Vector2(0.5f, 0.0f), false, false);
	lockIcon.SetScale(lockUI.GetScale() - Vector2(12, 12));
	lockIcon.SetPosition(Vector3(1156, 742, 0));
	lockIcon.SetAlpha(lockIcon, 0.6f);
	lockIcon.SpriteTransferVertexBuffer(lockIcon, 15);
	lockIcon.SpriteUpdate(lockIcon, spriteCommon_);
	lockIcon.LoadTexture(spriteCommon_, 15, L"Resources/lockIcon.png", device);
	//continueTextbox
	continueTextbox.SpriteCreate(device, 16, Vector2(0.5f, 0.5f), false, false);
	continueTextbox.SetScale(Vector2(64,32));
	continueTextbox.SetPosition(Vector3(640, 360, 0));
	continueTextbox.SpriteTransferVertexBuffer(continueTextbox, 16);
	continueTextbox.LoadTexture(spriteCommon_, 16, L"Resources/continueBox.png", device);
	//continueYes
	continueYes.SpriteCreate(device, 17, Vector2(0.5f, 0.5f), false, false);
	continueYes.SetScale(Vector2(128, 64));
	continueYes.SetPosition(Vector3(460, 410, 0));
	continueYes.SetColor(continueYes, Vector4(0.7f, 0.9f, 0.0f, 1.0f));
	continueYes.SpriteTransferVertexBuffer(continueYes, 17);
	continueYes.LoadTexture(spriteCommon_, 17, L"Resources/continueYes.png", device);
	//continueNo
	continueNo.SpriteCreate(device, 18, Vector2(0.5f, 0.5f), false, false);
	continueNo.SetScale(Vector2(196, 64));
	continueNo.SetPosition(Vector3(800, 410, 0));
	continueNo.SpriteTransferVertexBuffer(continueNo, 18);
	continueNo.LoadTexture(spriteCommon_, 18, L"Resources/continueNo.png", device);
	//continueText
	continueText.SpriteCreate(device, 19, Vector2(0.5f, 0.5f), false, false);
	continueText.SetScale(Vector2(512, 64));
	continueText.SetPosition(Vector3(640, 250, 0));
	continueText.SpriteTransferVertexBuffer(continueText, 19);
	continueText.LoadTexture(spriteCommon_, 19, L"Resources/continue.png", device);
	//カーソル
	for (int i = 0; i < CURSOR_MAX; i++) {
		cursorGH[i].SpriteCreate(device, 20, Vector2(0.5f, 0.5f), false, false);
		cursorGH[i].SetScale(Vector2(48 * 1, 48 * 1));
		cursorGH[i].SetPosition(Input::GetInstance()->GetMousePos());
		cursorGH[i].SetAlpha(cursorGH[i], 1 - (i * 0.1f));
		cursorGH[i].SpriteTransferVertexBuffer(cursorGH[i], 20);
		cursorGH[i].SpriteUpdate(cursorGH[i], spriteCommon_);
		cursorGH[i].LoadTexture(spriteCommon_, 20, L"Resources/cursor.png", device);
	}
	//カーソルエフェクト
	circle.SpriteCreate(device, 21, Vector2(0.5f, 0.5f), false, false);
	circle.SetScale(Vector2(48 * circleSize, 48 * circleSize));
	circle.SetPosition({ 0,0,0 });
	circle.SpriteTransferVertexBuffer(circle, 21);
	circle.SpriteUpdate(circle, spriteCommon_);
	circle.LoadTexture(spriteCommon_, 21, L"Resources/circle.png", device);
	//コンティニューセレクト
	contSelect.SpriteCreate(device, 22, Vector2(0.5f, 0.5f), false, false);
	contSelect.SetScale(Vector2(196,64));
	contSelect.SetPosition({ 460, 410, 0 });
	contSelect.SpriteTransferVertexBuffer(contSelect, 22);
	contSelect.SpriteUpdate(contSelect, spriteCommon_);
	contSelect.LoadTexture(spriteCommon_, 22, L"Resources/continueSelect.png", device);
	//クリア
	congrat.LoadTexture(spriteCommon_, 23, L"Resources/congrat.png", device);
	congrat.SpriteCreate(device, 23, Vector2(0.5f, 0.5f), false, false);
	congrat.SetScale(Vector2(1055, 96));
	congrat.SetPosition({ 640, 305, 0 });
	congrat.SetAlpha(congrat, congratAlpha);
	congrat.SpriteTransferVertexBuffer(congrat, 23);
	congrat.SpriteUpdate(congrat, spriteCommon_);
	//クリア
	clearNext.LoadTexture(spriteCommon_, 24, L"Resources/clearNext.png", device);
	clearNext.SpriteCreate(device, 24, Vector2(0.5f, 0.5f), false, false);
	clearNext.SetScale(Vector2(312.0f * 1.2f, 52.0f * 1.2f));
	clearNext.SetPosition({ 640,640,0 });
	clearNext.SetAlpha(clearNext, congratAlpha);
	clearNext.SpriteTransferVertexBuffer(clearNext, 24);
	clearNext.SpriteUpdate(clearNext, spriteCommon_);
	//congratBack
	congratBack.SpriteCreate(device, 25, Vector2(0.5f, 0.5f), false, false);
	congratBack.SetScale(Vector2(1280, 96));
	congratBack.SetPosition({ 640, 305, 0 });
	congratBack.SetAlpha(congratBack, congratAlpha);
	congratBack.SpriteTransferVertexBuffer(congratBack, 25);
	congratBack.SpriteUpdate(congratBack, spriteCommon_);
	congratBack.LoadTexture(spriteCommon_, 25, L"Resources/congrat_bak.png", device);
	congratAlpha = 0.0f;


	isPlayable = false;
	frameAlpha = 1.0f;
	barAlpha = 0.4f;
	isContinue = true;
	isShowContinue = false;
	circleSize = 1.0f;
	clickEffectAlpha = 1.0f;
	circleAlpha = 1.0f;
	isGameSceneReset = false;
	isGameOver = false;
}

void GameSceneUI::ShowUI()
{
	hpFrame.SetPosition(hpFrame.GetPosition() + Vector3(0, -4, 0));
	hpFrame.SpriteUpdate(hpFrame, spriteCommon_);

	attackIcon.SetPosition(attackIcon.GetPosition() + Vector3(0, -4, 0));
	attackIcon.SpriteUpdate(attackIcon, spriteCommon_);
	attackUI.SetPosition(attackUI.GetPosition() + Vector3(0, -4, 0));
	attackUI.SpriteUpdate(attackUI, spriteCommon_);

	lockIcon.SetPosition(lockIcon.GetPosition() + Vector3(0, -4, 0));
	lockIcon.SpriteUpdate(lockIcon, spriteCommon_);
	lockUI.SetPosition(lockUI.GetPosition() + Vector3(0, -4, 0));
	lockUI.SpriteUpdate(lockUI, spriteCommon_);
}

void GameSceneUI::Update(bool isPlayable_, Player* player)
{
	isPlayable = isPlayable_;

	//操作可能状態ならHPを更新
	if (isPlayable == true) {
		//playerhp
		float playerHp_ = player->GetHP() - (hp.GetScale().x / 4);
		if (playerHp_ > 0) {
			if ((playerHp_) > 4) {
				hp.SetScale(hp.GetScale() + Vector2(16.0f, 0.0f));
			}
			else if ((playerHp_) > 2) {
				hp.SetScale(hp.GetScale() + Vector2(8.0f, 0.0f));
			}
			else if ((playerHp_) > 1) {
				hp.SetScale(hp.GetScale() + Vector2(4.0f, 0.0f));
			}
		}
		else if (playerHp_ < 0) {
			if ((playerHp_) < 4) {
				hp.SetScale(hp.GetScale() - Vector2(8.0f, 0.0f));
			}
			else if ((playerHp_) < 2) {
				hp.SetScale(hp.GetScale() - Vector2(4.0f, 0.0f));
			}
			else if ((playerHp_) < 1) {
				hp.SetScale(hp.GetScale() - Vector2(2.0f, 0.0f));
			}
		}

		//playerの状態により表示変化
		if (player->GetHealthState() == 0) {
			hp.SetColor(hp, { 0.2f,1.0f,0.2f,1.0f });
			hpBack.SetColor(hpBack, { 0.2f,1.0f,0.2f,0.4f });
		}
		else if (player->GetHealthState() == 1) {
			hp.SetColor(hp, { 0.7f,1.0f,0.0f,1.0f });
			hpBack.SetColor(hpBack, { 0.7f,1.0f,0.0f,0.4f });
		}
		else {
			hp.SetColor(hp, { 0.5f,0.0f,0.0f,1.0f });
			hpBack.SetColor(hpBack, { 0.5f,0.0f,0.0f,0.4f });
		}

		hp.SetAlpha(hp, frameAlpha);
		hpBack.SetAlpha(hpBack, barAlpha);
		hpFrame.SetAlpha(hpFrame, frameAlpha);
		hp.SpriteTransferVertexBuffer(hp, 2);
		hp.SpriteUpdate(hp, spriteCommon_);
		hpBack.SpriteTransferVertexBuffer(hpBack, 9);
		hpBack.SpriteUpdate(hpBack, spriteCommon_);
		hpFrame.SpriteUpdate(hpFrame, spriteCommon_);
		//gage
		float gage_ = player->GetEnergy() - (gage.GetScale().x / 4);
		if (gage_ > 0) {
			if (gage.GetScale().x < 358) {
				if ((gage_) > 4) {
					gage.SetScale(gage.GetScale() + Vector2(16.0f, 0.0f));
				}
				else if ((gage_) > 2) {
					gage.SetScale(gage.GetScale() + Vector2(8.0f, 0.0f));
				}
				else if ((gage_) > 1) {
					gage.SetScale(gage.GetScale() + Vector2(4.0f, 0.0f));
				}
			}
		}
		else if (gage_ < 0) {
			if ((gage_) < 4) {
				gage.SetScale(gage.GetScale() - Vector2(8.0f, 0.0f));
			}
			else if ((gage_) < 2) {
				gage.SetScale(gage.GetScale() - Vector2(4.0f, 0.0f));
			}
			else if ((gage_) < 1) {
				gage.SetScale(gage.GetScale() - Vector2(2.0f, 0.0f));
			}
		}
	}
	gage.SetAlpha(gage, frameAlpha);
	gageBack.SetAlpha(gageBack, barAlpha);
	gage.SpriteTransferVertexBuffer(gage, 7);
	gage.SpriteUpdate(gage, spriteCommon_);
	gageBack.SpriteUpdate(gageBack, spriteCommon_);

	//UI表示
	if (Input::GetInstance()->TriggerMouseLeft()) {
		attackUI.SetColor(attackUI, { 0.9f,1.0f,0.2f,1.0f });
		attackIcon.SetColor(attackIcon, { 0.9f,1.0f,0.2f,1.0f });
	}
	else if (Input::GetInstance()->LeftMouseLeft()) {
		attackUI.SetColor(attackUI, { 1.0f,1.0f,1.0f,0.6f });
		attackIcon.SetColor(attackIcon, { 1.0f,1.0f,1.0f,0.6f });
	}//lock
	if (Input::GetInstance()->TriggerMouseRight()) {
		lockUI.SetColor(lockUI, { 0.9f,1.0f,0.2f,1.0f });
		lockIcon.SetColor(lockIcon, { 0.9f,1.0f,0.2f,1.0f });
	}
	else if (Input::GetInstance()->LeftMouseRight()) {
		lockUI.SetColor(lockUI, { 1.0f,1.0f,1.0f,0.6f });
		lockIcon.SetColor(lockIcon, { 1.0f,1.0f,1.0f,0.6f });
	}
}

void GameSceneUI::Draw(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	// スプライト描画前処理
	Sprite::PreDraw(cmdList, spriteCommon_);

	///=== スプライト描画 ===///

	hpFrame.SpriteDraw(cmdList, spriteCommon_, device);
	//UI
	attackUI.SpriteDraw(cmdList, spriteCommon_, device);
	attackIcon.SpriteDraw(cmdList, spriteCommon_, device);
	lockUI.SpriteDraw(cmdList, spriteCommon_, device);
	lockIcon.SpriteDraw(cmdList, spriteCommon_, device);
	if (isPlayable == true) {
		hpBack.SpriteDraw(cmdList, spriteCommon_, device);
		gageBack.SpriteDraw(cmdList, spriteCommon_, device);
		hp.SpriteDraw(cmdList, spriteCommon_, device);
		gage.SpriteDraw(cmdList, spriteCommon_, device);
	}


	// スプライト描画後処理
	Sprite::PostDraw();
}

void GameSceneUI::SetHPAlpha(bool isCollision)
{
	if (isCollision == true) {
		if (frameAlpha > 0.6f) {
			frameAlpha -= 0.025f;
		}
		if (barAlpha > 0.1f) {
			barAlpha -= 0.025f;
		}
	}
	else {
		if (frameAlpha < 1.0f) {
			frameAlpha += 0.025f;
		}
		if (barAlpha < 0.4f) {
			barAlpha += 0.025f;
		}
	}
}

void GameSceneUI::ResetUIPos()
{
	//hpフレーム
	hpFrame.SetPosition(Vector3(226, 851, 0));
	hpFrame.SpriteUpdate(hpFrame, spriteCommon_);
	//hp
	hp.SetScale(Vector2(4 * 1, 48 * 1));
	hp.SetPosition(Vector3(28, 650, 0));
	hp.SpriteUpdate(hp, spriteCommon_);
	hpBack.SetPosition(Vector3(28, 650, 0));
	hpBack.SetScale(Vector2(396, 48 * 1));
	hpBack.SpriteUpdate(hpBack, spriteCommon_);
	//gage
	gage.SetPosition(Vector3(28, 618, 0));
	gage.SetScale(Vector2(2 * 1, 18 * 1));
	gage.SpriteUpdate(gage, spriteCommon_);
	gageBack.SetPosition(Vector3(28, 618, 0));
	gageBack.SetScale(Vector2(358, 18 * 1));
	gageBack.SpriteUpdate(gageBack, spriteCommon_);
	//攻撃UI
	attackUI.SetPosition(Vector3(1020, 800, 0));
	attackUI.SpriteUpdate(attackUI, spriteCommon_);
	//攻撃Icon
	attackIcon.SetPosition(Vector3(1020, 808, 0));
	attackIcon.SpriteUpdate(attackIcon, spriteCommon_);
	//ロックUI
	lockUI.SetPosition(Vector3(1160, 740, 0));
	lockUI.SpriteUpdate(lockUI, spriteCommon_);
	//ロックIcon
	lockIcon.SetPosition(Vector3(1156, 742, 0));
	lockIcon.SpriteUpdate(lockIcon, spriteCommon_);

	//continueTextbox
	continueTextbox.SetScale(Vector2(64, 32));
	continueTextbox.SetPosition(Vector3(640, 360, 0));
	continueTextbox.SpriteTransferVertexBuffer(continueTextbox, 16);
	continueTextbox.SpriteUpdate(continueTextbox, spriteCommon_);
	//continueYes
	continueYes.SetColor(continueYes, Vector4(0.7f, 0.9f, 0.0f, 1.0f));
	continueYes.SpriteTransferVertexBuffer(continueYes, 17);
	continueYes.SpriteUpdate(continueYes, spriteCommon_);
	//continueNo
	continueNo.SetColor(continueNo, Vector4(0.8f, 0.8f, 0.8f, 1.0f));
	continueNo.SpriteTransferVertexBuffer(continueNo, 18);
	continueNo.SpriteUpdate(continueNo, spriteCommon_);

	isShowContinue = false;
	cursorPos = { 640,360,0 };
	cursorPosBak = { 0,0,0 };
	isGameOver = false;
	isGameSceneReset = false;

}

void GameSceneUI::SkipUIPos()
{
	//hpフレーム
	hpFrame.SetPosition(Vector3(226, 655, 0));
	hpFrame.SpriteUpdate(hpFrame, spriteCommon_);
	//攻撃UI
	attackUI.SetPosition(Vector3(1020, 604, 0));
	attackUI.SpriteUpdate(attackUI, spriteCommon_);
	//攻撃Icon
	attackIcon.SetPosition(Vector3(1020, 612, 0));
	attackIcon.SpriteUpdate(attackIcon, spriteCommon_);
	//ロックUI
	lockUI.SetPosition(Vector3(1160, 544, 0));
	lockUI.SpriteUpdate(lockUI, spriteCommon_);
	//ロックIcon
	lockIcon.SetPosition(Vector3(1156, 546, 0));
	lockIcon.SpriteUpdate(lockIcon, spriteCommon_);
}

void GameSceneUI::DeadUIPos()
{
	hpFrame.SetPosition(hpFrame.GetPosition() + Vector3(-1.0f, +4.0f, 0.0f));
	hpFrame.SpriteUpdate(hpFrame, spriteCommon_);
	hp.SetPosition(hp.GetPosition() + Vector3(-1.0f, +4.0f, 0.0f));
	hp.SpriteUpdate(hp, spriteCommon_);
	hpBack.SetPosition(hpBack.GetPosition() + Vector3(-1.0f, +4.0f, 0.0f));
	hpBack.SpriteUpdate(hpBack, spriteCommon_);
	gage.SetPosition(gage.GetPosition() + Vector3(-1.0f, +4.0f, 0.0f));
	gage.SpriteUpdate(gage, spriteCommon_);
	gageBack.SetPosition(gageBack.GetPosition() + Vector3(-1.0f, +4.0f, 0.0f));
	gageBack.SpriteUpdate(gageBack, spriteCommon_);


	attackIcon.SetPosition(attackIcon.GetPosition() + Vector3(1.0f, +4.0f, 0.0f));
	attackIcon.SpriteUpdate(attackIcon, spriteCommon_);
	attackUI.SetPosition(attackUI.GetPosition() + Vector3(1.0f, +4.0f, 0.0f));
	attackUI.SpriteUpdate(attackUI, spriteCommon_);

	lockIcon.SetPosition(lockIcon.GetPosition() + Vector3(1.0f, +4.0f, 0.0f));
	lockIcon.SpriteUpdate(lockIcon, spriteCommon_);
	lockUI.SetPosition(lockUI.GetPosition() + Vector3(1.0f, +4, 0));
	lockUI.SpriteUpdate(lockUI, spriteCommon_);
}

void GameSceneUI::ContinueText()
{
	Vector2 addScale = { 32, 12};
	if (continueTextbox.GetScale().x >= 768) {
		addScale.x = 0;
	}
	if (continueTextbox.GetScale().y >= 384) {
		addScale.y = 0;
	}
	if (addScale.x == 0) {
		isShowContinue = true;
	}
	if (isShowContinue == true) {
		CursorUpdate(true);

		bool onCursor = false;

		if (cursorPos.x > 362 && cursorPos.x < 558) {
			if (cursorPos.y > 378 && cursorPos.y < 442) {
				if (isContinue == false) {
					isContinue = true;
					continueYes.SetColor(continueYes, Vector4(0.7f, 0.9f, 0.0f, 1.0f));
					continueNo.SetColor(continueNo, Vector4(0.8f, 0.8f, 0.8f, 1.0f));
					contSelect.SetPosition({ 460, 410, 0 });
					contSelect.SpriteUpdate(contSelect, spriteCommon_);
				}
				if (Input::GetInstance()->TriggerMouseLeft()) {
					isGameSceneReset = true;
				}
				onCursor = true;
			}
		}

		if (cursorPos.x > 702 && cursorPos.x < 898) {
			if (cursorPos.y > 378 && cursorPos.y < 442) {
				if (isContinue == true) {
					isContinue = false;
					continueYes.SetColor(continueYes, Vector4(0.8f, 0.8f, 0.8f, 1.0f));
					continueNo.SetColor(continueNo, Vector4(0.7f, 0.9f, 0.0f, 1.0f));
					contSelect.SetPosition({ 800, 410, 0 });
					contSelect.SpriteUpdate(contSelect, spriteCommon_);
				}
				if (Input::GetInstance()->TriggerMouseLeft()) {
					isGameOver = true;
				}
				onCursor = true;
			}
		}

		if (onCursor == false) {
			if (Input::GetInstance()->TriggerKey(DIK_A)) {
				if (isContinue == false) {
					isContinue = true;
					continueYes.SetColor(continueYes, Vector4(0.7f, 0.9f, 0.0f, 1.0f));
					continueNo.SetColor(continueNo, Vector4(0.8f, 0.8f, 0.8f, 1.0f));
					contSelect.SetPosition({ 460, 410, 0 });
					contSelect.SpriteUpdate(contSelect, spriteCommon_);
				}
			}
			else if(Input::GetInstance()->TriggerKey(DIK_D)) {
				if (isContinue == true) {
					isContinue = false;
					continueYes.SetColor(continueYes, Vector4(0.8f, 0.8f, 0.8f, 1.0f));
					continueNo.SetColor(continueNo, Vector4(0.7f, 0.9f, 0.0f, 1.0f));
					contSelect.SetPosition({ 800, 410, 0 });
					contSelect.SpriteUpdate(contSelect, spriteCommon_);
				}
			}
			if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
				if (isContinue == false) {
					isGameOver = true;
				 }
				else {
					isGameSceneReset = true;
				}
			}
		}
		
		

		continueText.SpriteTransferVertexBuffer(continueText, 19);
		continueText.SpriteUpdate(continueText, spriteCommon_);
		continueYes.SpriteTransferVertexBuffer(continueYes, 17);
		continueYes.SpriteUpdate(continueYes, spriteCommon_);
		continueNo.SpriteTransferVertexBuffer(continueNo, 18);
		continueNo.SpriteUpdate(continueNo, spriteCommon_);
	}

	continueTextbox.SetScale(continueTextbox.GetScale() + addScale);
	continueTextbox.SpriteTransferVertexBuffer(continueTextbox, 16);
	continueTextbox.SpriteUpdate(continueTextbox, spriteCommon_);
}

void GameSceneUI::DrawContinue(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	// スプライト描画前処理
	Sprite::PreDraw(cmdList, spriteCommon_);

	continueTextbox.SpriteDraw(cmdList, spriteCommon_, device);
	if (isShowContinue == true) {
		continueText.SpriteDraw(cmdList, spriteCommon_, device);
		contSelect.SpriteDraw(cmdList, spriteCommon_, device);
		continueYes.SpriteDraw(cmdList, spriteCommon_, device);
		continueNo.SpriteDraw(cmdList, spriteCommon_, device);
		circle.SpriteDraw(cmdList, spriteCommon_, device);
		for (int i = 0; i < CURSOR_MAX; i++) {
			cursorGH[i].SpriteDraw(cmdList, spriteCommon_, device);
		}
	}

	// スプライト描画後処理
	Sprite::PostDraw();
}

void GameSceneUI::DrawClear(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	// スプライト描画前処理
	Sprite::PreDraw(cmdList, spriteCommon_);

	congratBack.SpriteDraw(cmdList, spriteCommon_, device);
	congrat.SpriteDraw(cmdList, spriteCommon_, device);
	clearNext.SpriteDraw(cmdList, spriteCommon_, device);
	for (int i = 0; i < CURSOR_MAX; i++) {
		cursorGH[i].SpriteDraw(cmdList, spriteCommon_, device);
	}

	// スプライト描画後処理
	Sprite::PostDraw();
}

void GameSceneUI::CursorUpdate(bool isCont) {
	Vector3 cur = Input::GetInstance()->GetMousePos();
	Vector3 move = cur - cursorPosBak;

	if (isCont == true) {
		if (cursorPos.x + move.x <= 256 || cursorPos.x + move.x >= 1024) {
			move.x = 0;
		}
		if (cursorPos.y + move.y <= 168 || cursorPos.y + move.y >= 552) {
			move.y = 0;
		}
	}
	cursorPos += move;

	cursorGH[8].SetPosition(cursorGH[7].GetPosition());
	cursorGH[7].SetPosition(cursorGH[6].GetPosition());
	cursorGH[6].SetPosition(cursorGH[5].GetPosition());
	cursorGH[5].SetPosition(cursorGH[4].GetPosition());
	cursorGH[4].SetPosition(cursorGH[3].GetPosition());
	cursorGH[3].SetPosition(cursorGH[2].GetPosition());
	cursorGH[2].SetPosition(cursorGH[1].GetPosition());
	cursorGH[1].SetPosition(cursorGH[0].GetPosition());
	cursorGH[0].SetPosition(cursorPos);
	circle.SetPosition(cursorPos);
	if (Input::GetInstance()->TriggerMouseLeft() == true) {
		circleSize = 1.0f;
		circleAlpha = 1.0f;
	}
	else if (circleSize < 6.0f) {
		circleSize += 0.1f;
		circleAlpha -= 0.025f;
	}
	else {
		circleSize = 1.0f;
		circleAlpha = 1.0f;
	}
	circle.SetScale(Vector2(16 * circleSize, 16 * circleSize));
	circle.SetRotation(circle.GetRotation() + 0.005f);
	circle.SetAlpha(circle, circleAlpha);
	circle.SpriteTransferVertexBuffer(circle, 7);
	circle.SpriteUpdate(circle, spriteCommon_);
	for (int i = 0; i < CURSOR_MAX; i++) {
		cursorGH[i].SpriteUpdate(cursorGH[i], spriteCommon_);
	}

	cursorPosBak = cursorPos;
}

void GameSceneUI::ClearUpdate()
{
	if (congratAlpha < 1.0f) {
		congratAlpha += 0.025f;
		congrat.SetAlpha(congrat, congratAlpha);
		congratBack.SetAlpha(congratBack, congratAlpha);
		clearNext.SetAlpha(clearNext, congratAlpha);
	}
}
