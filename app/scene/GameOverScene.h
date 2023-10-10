#pragma once

#include "Input.h"
#include "DirectXCommon.h"
#include "GameBaseScene.h"
#include "Sprite.h"
#include "GameSceneManager.h"
#include "GameTitleScene.h"
#include "Object3d.h"

#include <DirectXMath.h>

class GameOverScene : public GameBaseScene
{
public: // �����o�֐�
	// �R���X�g���N�^
	GameOverScene();
	// �f�X�g���N�^
	~GameOverScene();

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="dXCommon"></param>
	void Draw() override;

	/// <summary>
	/// ���
	/// </summary>
	void Finalize() override;

private: // �����o�ϐ�
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Sprite* cross = nullptr;
	//�J����
	ViewProjection* viewProjection = nullptr;
	//score
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite clearGH;
	int scores[6];
	float numPosX;
	int showTime;
	//title
	Sprite* title01 = nullptr;
	Sprite* title02 = nullptr;
	//retry
	Sprite* retry01 = nullptr;
	Sprite* retry02 = nullptr;
	bool isNext;
	bool curHit01;
	bool curHit02;
};

