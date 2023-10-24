/**
 * @file SceneManeger.h
 * @brief シーン切り替えを行うクラス
 * @author カネコ_リョウタ
 */

#include "GameSceneManager.h"

GameSceneManager::~GameSceneManager()
{
	// 最後のシーンの終了と解放
	if (scene != nullptr) {
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
}

GameSceneManager* GameSceneManager::GetInstance() 
{
	static GameSceneManager instance;

	return &instance;
}

void GameSceneManager::Update()
{
	// 予約シーンの予約があるなら
	if (nextScene) {
		// 旧シーンの終了
		if (scene) {
			scene->Finalize();

			delete scene;
		}

		// シーン切り替え
		scene = nextScene;
		nextScene = nullptr;

		// シーンマネージャをセット
		scene->SetSceneManager(this);

		// 次シーンを初期化する
		scene->Initialize();
	}

	// 実行中シーンを更新する
	scene->Update();
}

void GameSceneManager::Draw()
{
	// シーンの描画
	scene->Draw();
}

void GameSceneManager::Destroy()
{
	if (scene != nullptr) {
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
}

void GameSceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory);
	assert(nextScene == nullptr);

	// 次シーン生成
	nextScene = sceneFactory->CreateScene(sceneName);
}
