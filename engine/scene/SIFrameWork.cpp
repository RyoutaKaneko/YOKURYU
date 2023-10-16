/**
 * @file SlFrameWork.h
 * @brief �Q�[����ՁB���C�����[�v���s���Ă���
 * @author �J�l�R_�����E�^
 */

#include "SIFrameWork.h"

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
	sceneManager_ = GameSceneManager::GetInstance();
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice());
	//fbx�ėp������
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//
	FbxObject3d::StaticInitialize(dxCommon->GetDevice());

	/*postEffect.Initialize(dxCommon->GetDevice());*/
	
}

void SIFrameWork::Finalize()
{
	sceneManager_->Destroy();
	//�V�[���t�@�N�g���̉��
	delete sceneFactory_;

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

	if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
		endRequest = true;
	}

	// �V�[���}�l�[�W���̍X�V
	sceneManager_->Update();
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
