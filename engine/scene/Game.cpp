#include "Game.h"

#include "SceneFactory.h"

void Game::Initialize()
{	
	// ���N���X�̏���������
	SIFrameWork::Initialize();

	// �V�[���t�@�N�g���𐶐����A�}�l�[�W���ɃZ�b�g
	sceneFactory_ = new SceneFactory();
	sceneManager_->SetSceneFactory(sceneFactory_);
	// �V�[���}�l�[�W���ɍŏ��̃V�[�����Z�b�g
	sceneManager_->ChangeScene("TITLE");
}

void Game::Finalize()
{
	// ���N���X�̏I������
	SIFrameWork::Finalize();
}

void Game::Update()
{
	// ���N���X�̍X�V����
	SIFrameWork::Update();
}

void Game::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	//=== �V�[���}�l�[�W���̕`�� ===//
	sceneManager_->Draw();
}
