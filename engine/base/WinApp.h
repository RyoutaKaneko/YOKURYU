/**
 * @file WinApp.cpp
 * @brief Window生成クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp final
{
public: // 静的メンバ関数
	/// <summary>
	/// window生成
	/// </summary>
	/// <param name="hwnd"></param>
	/// <param name="msg"></param>
	/// <param name="wparam"></param>
	/// <param name="lparam"></param>
	/// <returns></returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // メンバ関数
	/// <summary>
	/// WindowsAPIの初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// hwnd取得
	/// </summary>
	/// <returns></returns>
	HWND GetHwnd() const { return hwnd; }

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns></returns>
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns></returns>
	bool ProcessMessage();

public:
	static WinApp* GetInstance();

private:
	WinApp() = default;
	~WinApp() = default;
	WinApp(const WinApp&) = delete;
	WinApp& operator=(const WinApp&) = delete;

public: // 定数
	// ウィンドウ横幅
	static const int window_width = 1280;
	// ウィンドウ縦幅
	static const int window_height = 720;

private:
	// ウィンドウハンドル
	HWND hwnd = nullptr;
	// ウィンドウクラスの設定
	WNDCLASSEX wc{};
};