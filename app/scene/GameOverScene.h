#pragma once
#include "Input.h"
#include "DirectXCommon.h"
#include "GameBaseScene.h"
#include "Sprite.h"
#include "GameSceneManager.h"
#include "GameTitleScene.h"
#include "Object3d.h"

#include <DirectXMath.h>

enum Health {
	FINE,
	WEEKNESS,
	DYING,
	DIE
};

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
	Sprite overGH;
	Sprite fade;
	Sprite textGH;
	Object3d* sky = nullptr;
	Model* skyModel = nullptr;
	Player* player = nullptr;
	Object3d* stage = nullptr;
	Model* stageModel = nullptr;
	int gameTimer;
	float fadeAlpha;
	float textAlpha;

};

