/**
 * @file SceneFactory.h
 * @brief シーン切り替え時の次シーンを生成するクラス
 * @author カネコ_リョウタ
 */

#include "SceneFactory.h"

GameBaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
    // 次のシーン生成
    GameBaseScene* newScene = nullptr;

    if (sceneName == "TITLE") {
        newScene = new GameTitleScene();
    }
    else if (sceneName == "GAMEPLAY") {
        newScene = new GameScene();
    }
    else if (sceneName == "OVER") {
        newScene = new GameOverScene();
    }

    return newScene;
}
