/**
 * @file SceneFactory.h
 * @brief SceneFactory基盤クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "GameBaseScene.h"
#include <string>

class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;

	virtual GameBaseScene* CreateScene(const std::string& sceneName) = 0;
};