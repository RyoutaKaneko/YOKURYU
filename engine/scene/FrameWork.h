/**
 * @file SlFrameWork.cpp
 * @brief ゲーム基盤。メインループを行っている
 * @author カネコ_リョウタ
 */

#pragma once
#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include"Model.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
#include "AbstractSceneFactory.h"
#include "GameSceneManager.h"

class FrameWork
{
public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();


	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;
	
	/// <summary>
	/// 終了チェック
	/// </summary>
	/// <returns></returns>
	virtual bool IsEndRequest() { return endRequest; }

public:
	virtual ~FrameWork() = default;

public:
	/// <summary>
	/// 実行
	/// </summary>
	void Run();

protected:
	//WindowsAPIのポインタ
	WinApp* winApp = nullptr;
	//DirectXのポインタ
	DirectXCommon* dxCommon = nullptr;
	//入力のポインタ
	Input* input = nullptr;
	// シーンマネージャ
	GameSceneManager* sceneManager = nullptr;
	// シーンファクトリー
	AbstractSceneFactory* sceneFactory = nullptr;
private:
	bool endRequest = false;
};

