/**
 * @file Game.cpp
 * @brief シーン生成クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "SIFrameWork.h"

// ゲーム全体
class Game : public SIFrameWork
{
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};
