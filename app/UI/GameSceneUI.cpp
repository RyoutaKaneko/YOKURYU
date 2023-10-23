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

	isPlayable = false;
	frameAlpha = 1.0f;
	barAlpha = 0.4f;
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
