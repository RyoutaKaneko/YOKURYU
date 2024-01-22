/**
 * @file SceneFactory.h
 * @brief �V�[���؂�ւ����̎��V�[���𐶐�����N���X
 * @author �J�l�R_�����E�^
 */

#include "SceneFactory.h"

GameBaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
    // ���̃V�[������
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
