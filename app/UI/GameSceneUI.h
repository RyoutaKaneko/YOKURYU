#include "Sprite.h"
#include "Player.h"


#pragma once
class GameSceneUI
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// UI表示開始
	/// </summary>
	/// <param name="device"></param>
	/// <param name="time">ゲームタイム</param>
	void ShowUI();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="device"></param>
	void Update(bool isPlayable_, Player* player);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="device"></param>
	void Draw(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// HPフレームの座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetHPFramePos() { return hpFrame.GetPosition(); }

	/// <summary>
	/// 透過率セット
	/// </summary>
	/// <param name="isCollision"></param>
	void SetHPAlpha(bool isCollision);

	/// <summary>
	/// 
	/// </summary>
	void ResetUIPos();

	/// <summary>
	/// 
	/// </summary>
	void SkipUIPos();

private:
	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite hp;
	Sprite bossHP;
	Sprite gage;
	Sprite gageBack;
	Sprite hpBack;
	Sprite hpFrame;
	Sprite attackUI;
	Sprite attackIcon;
	Sprite lockUI;
	Sprite lockIcon;
	bool isPlayable;
	float frameAlpha;
	float barAlpha;
};

