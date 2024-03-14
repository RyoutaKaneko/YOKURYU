/**
 * @file SlFrameWork.cpp
 * @brief �Q�[����ՁB���C�����[�v���s���Ă���
 * @author �J�l�R_�����E�^
 */

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

class FrameWork
{
public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();


	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();
	
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	
	/// <summary>
	/// �I���`�F�b�N
	/// </summary>
	/// <returns></returns>
	virtual bool IsEndRequest() { return endRequest; }

public:
	virtual ~FrameWork() = default;

public:
	/// <summary>
	/// ���s
	/// </summary>
	void Run();

protected:
	//WindowsAPI�̃|�C���^
	WinApp* winApp = nullptr;
	//DirectX�̃|�C���^
	DirectXCommon* dxCommon = nullptr;
	//���͂̃|�C���^
	Input* input = nullptr;
	// �V�[���}�l�[�W��
	GameSceneManager* sceneManager = nullptr;
	// �V�[���t�@�N�g���[
	AbstractSceneFactory* sceneFactory = nullptr;
private:
	bool endRequest = false;
};

