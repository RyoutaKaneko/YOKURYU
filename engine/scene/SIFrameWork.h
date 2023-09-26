#pragma once
#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include"Model.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
#include "AbstractSceneFactory.h"
#include "GameSceneManager.h"

class SIFrameWork
{
public://�����o�֐�
	//������
	virtual void Initialize();
	//�I��
	virtual void Finalize();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw() = 0;
	//�I���`�F�b�N
	virtual bool IsEndRequest() { return endRequest; }

public:
	virtual ~SIFrameWork() = default;

public:
	//���s
	void Run();

protected:
	//WindowsAPI�̃|�C���^
	WinApp* winApp = nullptr;
	//DirectX�̃|�C���^
	DirectXCommon* dxCommon = nullptr;
	//���͂̃|�C���^
	Input* input = nullptr;
	// �V�[���}�l�[�W��
	GameSceneManager* sceneManager_ = nullptr;
	// �V�[���t�@�N�g���[
	AbstractSceneFactory* sceneFactory_ = nullptr;
private:
	bool endRequest = false;
};

