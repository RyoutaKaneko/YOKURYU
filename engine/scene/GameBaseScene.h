#pragma once

#include "Sprite.h"
#include "JsonLoader.h"	
#include "Model.h"
#include "Object3d.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <map>
#include <list>

// �O���錾
class GameSceneManager;

// �V�[�����N���X
class GameBaseScene
{
public: // �����o�֐�
	GameBaseScene() = default;
	virtual ~GameBaseScene() = default;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ���
	/// </summary>
	virtual void Finalize() = 0;

	void LoadObjFromLevelEditor(const std::string& fileName);

public: // �����o�֐�
	virtual void SetSceneManager(GameSceneManager* gSceneManager) { gSceneManager_ = gSceneManager; }

protected: // �����o�ϐ�
	// �V�[���}�l�[�W���i�؂�Ă���j
	GameSceneManager* gSceneManager_ = nullptr;
	//leveleditor
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

