#include "Framework.h"

void Framework::Run()
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
		if (input->TriggerKey(DIK_ESCAPE)) {
			// �Q�[�����[�v�𔲂���
			break;
		}

		// �`��
		Draw();
	}

	// �Q�[���̏I��
	Finalize();
}

void Framework::Initialize()
{
	// WindowsAPI�̏�����
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectX�̏�����
	dXCommon = DirectXCommon::GetInstance();
	dXCommon->Initialize(winApp);

	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);
	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// �r���[�v���W�F�N�V�����̏�����
	ViewProjection::StaticInitialize(dXCommon->GetDevice());
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dXCommon->GetDevice());
	//fbx�ėp������
	FbxLoader::GetInstance()->Initialize(dXCommon->GetDevice());
	//
	FbxObject3d::StaticInitialize(dXCommon->GetDevice());

	postEffect.Initialize(dXCommon->GetDevice());
#pragma endregion ��ՃV�X�e���̏�����

	//�Q�[���V�[��
	gameScene = new GameScene();
	gameScene->Initialize(spriteCommon);
}

void Framework::Update()
{
	// Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		// �Q�[�����[�v�𔲂���
		endRequest_ = true;
	}
	gameScene->Update();
	// ���͂̍X�V
	/*input->Update();*/
}

void Framework::Draw()
{
#pragma region �Q�[���V�[���`��


#pragma endregion

#pragma region �`��
	postEffect.PreDrawScene(dXCommon->GetCommandList());
	gameScene->Draw();
	postEffect.PostDrawScene(dXCommon->GetCommandList());
	// �`��O����
	dXCommon->PreDraw();
	//=== �Q�[���V�[���`�� ===//
	postEffect.Draw(dXCommon->GetCommandList());
	// �`��㏈��
	dXCommon->PostDraw();
#pragma endregion
}

void Framework::Finalize()
{
	delete gameScene;
	FbxLoader::GetInstance()->Finalize();
	// WindowsAPI�̏I������
	winApp->Finalize();

	// DirectX���
	dXCommon->fpsFixedFinalize();
	
}
