/**
 * @file SlFrameWork.h
 * @brief �Q�[����ՁB���C�����[�v���s���Ă���
 * @author �J�l�R_�����E�^
 */

#include "SIFrameWork.h"
#include "GameTitleScene.h"

void SIFrameWork::Initialize()
{
	// WindowsAPI�̏�����
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectX�̏�����
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(winApp);

	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);
	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice());
	// �r���[�v���W�F�N�V�����̏�����
	ViewProjection::StaticInitialize(dxCommon->GetDevice());
	// �V�[���}�l�[�W���̐���
	sceneManager = GameSceneManager::GetInstance();
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice());	
}

void SIFrameWork::Finalize()
{
	sceneManager->Destroy();
	//�V�[���t�@�N�g���̉��
	delete sceneFactory;

	// WindowsAPI�̏I������
	winApp->Finalize();

	// DirectX���
	dxCommon->fpsFixedFinalize();
}

void SIFrameWork::Update()
{
	// Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		// �Q�[�����[�v�𔲂���
		endRequest = true;
	}

	// ���͂̍X�V
	input->Update();

	if (GameTitleScene::GetIsEnd() == true) {
		endRequest = true;
	}

	// �V�[���}�l�[�W���̍X�V
	sceneManager->Update();
}

void SIFrameWork::Run()
{
	// �Q�[���̏�����
	Initialize();

	while (true) // �Q�[�����[�v 
	{
		// ���t���[���X�V
		Update();

		// �I�����N�G�X�g�������烋�[�v�𔲂���
		if (IsEndRequest()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

		// �`��
		Draw();
	}

	// �Q�[���̏I��
	Finalize();
}
