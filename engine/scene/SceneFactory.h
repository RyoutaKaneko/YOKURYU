/**
 * @file SceneFactory.cpp
 * @brief シーン切り替え時の次シーンを生成するクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "AbstractSceneFactory.h"
#include "GameTitleScene.h"
#include "GameScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"

/// <summary>
/// このゲーム用のシーン工場
/// </summary>
class SceneFactory : public AbstractSceneFactory
{
public:
	/// <summary>
	/// シーン生成
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	/// <returns></returns>
	GameBaseScene* CreateScene(const std::string& sceneName) override;
};

