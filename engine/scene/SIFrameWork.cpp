/**
 * @file SlFrameWork.h
 * @brief ゲーム基盤。メインループを行っている
 * @author カネコ_リョウタ
 */

#include "SIFrameWork.h"
#include "GameTitleScene.h"

void SIFrameWork::Initialize()
{
	// WindowsAPIの初期化
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectXの初期化
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize(winApp);
	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice());
	// ビュープロジェクションの初期化
	ViewProjection::StaticInitialize(dxCommon->GetDevice());
	// シーンマネージャの生成
	sceneManager = GameSceneManager::GetInstance();
	// パーティクル静的初期化
	ParticleManager::StaticInitialize(dxCommon->GetDevice());	
}

void SIFrameWork::Finalize()
{
	sceneManager->Destroy();
	//シーンファクトリの解放
	delete sceneFactory;

	// WindowsAPIの終了処理
	winApp->Finalize();

	// DirectX解放
	dxCommon->fpsFixedFinalize();
}

void SIFrameWork::Update()
{
	// Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		// ゲームループを抜ける
		endRequest = true;
	}

	// 入力の更新
	input->Update();

	if (GameTitleScene::GetIsEnd() == true) {
		endRequest = true;
	}

	// シーンマネージャの更新
	sceneManager->Update();
}

void SIFrameWork::Run()
{
	// ゲームの初期化
	Initialize();

	while (true) // ゲームループ 
	{
		// 毎フレーム更新
		Update();

		// 終了リクエストが来たらループを抜ける
		if (IsEndRequest()) {
			// ゲームループを抜ける
			break;
		}

		// 描画
		Draw();
	}

	// ゲームの終了
	Finalize();
}
