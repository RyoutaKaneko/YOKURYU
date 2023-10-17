/**
 * @file FpsFixed.cpp
 * @brief ゲームのfps上限を管理するクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <chrono>
#include <thread>

class FPSFixed 
{
public: // メンバ関数
	/// <summary>
	///  FPS固定初期化
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS固定更新
	/// </summary>
	void UpdateFixFPS();

	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;
};