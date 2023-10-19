/**
 * @file Game.h
 * @brief �V�[�������N���X
 * @author �J�l�R_�����E�^
 */

#include "Game.h"
#include "SceneFactory.h"

void Game::Initialize()
{	
	// ���N���X�̏���������
	SIFrameWork::Initialize();

	// �V�[���t�@�N�g���𐶐����A�}�l�[�W���ɃZ�b�g
	sceneFactory = new SceneFactory();
	sceneManager->SetSceneFactory(sceneFactory);
	// �V�[���}�l�[�W���ɍŏ��̃V�[�����Z�b�g
	sceneManager->ChangeScene("TITLE");
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
	/*ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();*/

	//=== �V�[���}�l�[�W���̕`�� ===//
	sceneManager->Draw();
}
