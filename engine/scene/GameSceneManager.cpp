#include "GameSceneManager.h"

GameSceneManager::~GameSceneManager()
{
	// �Ō�̃V�[���̏I���Ɖ��
	if (scene_ != nullptr) {
		scene_->Finalize();
		delete scene_;
		scene_ = nullptr;
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
	if (nextScene_) {
		// ���V�[���̏I��
		if (scene_) {
			scene_->Finalize();

			delete scene_;
		}

		// �V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;

		// �V�[���}�l�[�W�����Z�b�g
		scene_->SetSceneManager(this);

		// ���V�[��������������
		scene_->Initialize();
	}

	// ���s���V�[�����X�V����
	scene_->Update();
}

void GameSceneManager::Draw()
{
	// �V�[���̕`��
	scene_->Draw();
}

void GameSceneManager::Destroy()
{
	if (scene_ != nullptr) {
		scene_->Finalize();
		delete scene_;
		scene_ = nullptr;
	}
}

void GameSceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);

	// ���V�[������
	nextScene_ = sceneFactory_->CreateScene(sceneName);
}
