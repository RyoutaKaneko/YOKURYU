/**
 * @file SceneManeger.h
 * @brief �V�[���؂�ւ����s���N���X
 * @author �J�l�R_�����E�^
 */

#include "GameSceneManager.h"

GameSceneManager::~GameSceneManager()
{
	// �Ō�̃V�[���̏I���Ɖ��
	if (scene != nullptr) {
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
}

GameSceneManager* GameSceneManager::GetInstance() 
{
	static GameSceneManager instance;

	return &instance;
}

void GameSceneManager::Update()
{
	// �\��V�[���̗\�񂪂���Ȃ�
	if (nextScene) {
		// ���V�[���̏I��
		if (scene) {
			scene->Finalize();

			delete scene;
		}

		// �V�[���؂�ւ�
		scene = nextScene;
		nextScene = nullptr;

		// �V�[���}�l�[�W�����Z�b�g
		scene->SetSceneManager(this);

		// ���V�[��������������
		scene->Initialize();
	}

	// ���s���V�[�����X�V����
	scene->Update();
}

void GameSceneManager::Draw()
{
	// �V�[���̕`��
	scene->Draw();
}

void GameSceneManager::Destroy()
{
	if (scene != nullptr) {
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
}

void GameSceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory);
	assert(nextScene == nullptr);

	// ���V�[������
	nextScene = sceneFactory->CreateScene(sceneName);
}
