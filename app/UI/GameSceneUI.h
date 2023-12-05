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
	///  リセット時のUIの座標設定
	/// </summary>
	void ResetUIPos();

	/// <summary>
	/// 演出スキップ時のUIの座標設定
	/// </summary>
	void SkipUIPos();

	/// <summary>
	/// 死亡時UI座標
	/// </summary>
	void DeadUIPos();

	/// <summary>
	/// コンティニューテキスト更新
	/// </summary>
	void ContinueText();

	/// <summary>
	/// コンティニュー描画
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cmdList"></param>
	void DrawContinue(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// クリア画面描画
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cmdList"></param>
	void DrawClear(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// コンティニューフラグgetter
	/// </summary>
	/// <returns></returns>
	bool GetIsContinue() { return isContinue; }

	/// <summary>
	/// カーソルアップデート
	/// </summary>
	void CursorUpdate(bool isCont);
	
	/// <summary>
	/// ゲームシーンリセットgetter
	/// </summary>
	/// <returns></returns>
	bool GetIsGameSceneReset() { return isGameSceneReset; }

	/// <summary>
	// ゲームシーンオーバーgetter
	/// </summary>
	/// <returns></returns>
	bool GetIsGameOver() { return isGameOver; }

	/// <summary>
	/// クリアUI更新
	/// </summary>
	void ClearUpdate();

	/// <summary>
	/// ゲーム終了
	/// </summary>
	void EndText();

	/// <summary>
	/// ゲーム終了テキスト描画
	/// </summary>
	void DrawEnd(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	//ポーズ画面
	void PauseText();

	/// <summary>
    /// ポーズ画面テキスト描画
    /// </summary>
	void DrawPause(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// テキストとじる
	/// </summary>
	void CloseText();

	/// <summary>
	/// 
	/// </summary>
	bool GetIsClose() { return isClose; }

private:
	//定数
	static const int CURSOR_MAX = 9;
	static const int ALPHA_MAX = 1;
	static const Vector2 SELECT_CONTINUE_SCALE;
	static const Vector2 SELECT_PAUSE_SCALE;

	//スプライトのポインタ
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite hp;
	Sprite bossHP;
	Sprite hpBack;
	Sprite hpFrame;
	Sprite attackUI;
	Sprite attackIcon;
	Sprite lockUI;
	Sprite lockIcon;
	Sprite continueTextbox;
	Sprite continueYes;
	Sprite continueNo;
	Sprite continueText;
	Sprite cursorGH[CURSOR_MAX];
	Sprite circle;
	Sprite contSelect;
	Sprite congrat;
	Sprite clearNext;
	Sprite congratBack;
	Sprite end;
	Sprite goTitle;
	Sprite goReset;
	Sprite pause;
	Sprite pauseBack;
	Sprite esc;
	Sprite escClose;
	bool isPlayable;
	float frameAlpha;
	float barAlpha;
	bool isContinue;
	bool isShowContinue;
	float circleSize;
	float clickEffectAlpha;
	float circleAlpha;
	Vector3 cursorPos;
	Vector3 cursorPosBak;
	bool isGameSceneReset;
	bool isGameOver;
	float congratAlpha;
	bool isClose;
};

