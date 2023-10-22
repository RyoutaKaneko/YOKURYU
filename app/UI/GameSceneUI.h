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
};

