﻿/**
 * @file Input.cpp
 * @brief 入力デバイス管理クラス(キーボード、マウス)
 * @author カネコ_リョウタ
 */

#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <windows.h>
#include <wrl.h>
#include "WinApp.h"
#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>
#include <xinput.h>
#include "Vector3.h"
#include "Vector2.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment (lib, "xinput.lib")
#define MaxCountrollers 4  
#define MaxVibration 65535

// 入力
class Input final
{
public:
	static Input* GetInstance();

public:
	struct CountrolerState
	{
		XINPUT_STATE state; // コントローラーの状態の取得
		XINPUT_VIBRATION vibration;  // バイブレーション
		//bool Connected;
	};
	/*CountrolerState GamePad;*/

public:
	// namespace
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="winApp"></param>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// マウス左クリック長押し
	/// </summary>
	/// <returns></returns>
	bool PushMouseLeft();

	/// <summary>
	///  マウス左クリックしたとき
	/// </summary>
	/// <returns></returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// マウス右クリック長押し
	/// </summary>
	/// <returns></returns>
	bool PushMouseRight();

	/// <summary>
	/// マウス右クリックしたとき
	/// </summary>
	/// <returns></returns>
	bool TriggerMouseRight();

	/// <summary>
	/// マウス位置取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetMousePos();

	/// <summary>
	/// マウス移動量取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetMouseVelo();

	/// <summary>
	/// マウス位置設定
	/// </summary>
	/// <param name="pos"></param>
	void SetMousePos(Vector2 pos);

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name = "keyNumber">キー番号(DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// </param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <reutrns>トリガーか</params>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// 全てのキー入力をチェック
	/// </summary>
	/// <returns></returns>
	bool AnyKey();

private:
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

private: // メンバ変数
	// キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	//マウスのデバイス
	ComPtr<IDirectInputDevice8> mouse;
	// DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
	// 全キーの状態
	BYTE key[256] = {};
	// 前回の全キーの状態
	BYTE keyPre[256] = {};
	//マウスの状態
	DIMOUSESTATE mouseState = {};
	DIMOUSESTATE mouseState_bak = {};	// マウス情報(変化検知用)
	// WindowsAPI
	WinApp* winApp = nullptr;
};