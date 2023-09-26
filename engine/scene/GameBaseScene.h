#pragma once

#include "Sprite.h"

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

	int GetScore() { return score_; }
	void SetScore(int score) { score_ = score; }

public: // �����o�֐�
	virtual void SetSceneManager(GameSceneManager* gSceneManager) { gSceneManager_ = gSceneManager; }

private: // �����o�ϐ�
	// �V�[���}�l�[�W���i�؂�Ă���j
	GameSceneManager* gSceneManager_ = nullptr;
	//�X�R�A
	int score_;
};

