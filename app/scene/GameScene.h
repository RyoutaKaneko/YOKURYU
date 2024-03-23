/**
 * @file GameScene.cpp
 * @brief �Q�[���̃��C��������ԏd�v
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Sprite.h"
#include "Object3d.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "time.h"
#include <random>
#include "Model.h"
#include "ViewProjection.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "FbxObject3d.h"
#include "FbxModel.h"
#include "Player.h"
#include "RailCamera.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "Boss.h"
#include "JsonLoader.h"	
#include "energy.h"
#include "GameBaseScene.h"
#include "GameSceneUI.h"
#include "GameSceneConst.h"
#include "BombEnemy.h"


class GameScene : public GameBaseScene {
public:
	//�����o�֐�
	GameScene();

	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// �X�e�[�W�ǂݍ���
	/// </summary>
	void LoadStage();

	/// <summary>
	/// �G�ǂݍ���
	/// </summary>
	void LoadEnemy();

	/// <summary>
	/// ���G
	/// </summary>
	void SerchEnemy();

	/// <summary>
	/// ���b�N�I�����N���A
	/// </summary>
	void LockedClear();

	/// <summary>
	/// �N���X�w�A���擾
	/// </summary>
	void GetCrosshair();

	/// <summary>
	/// �X�N���[�����W���烏�[���h���W��
	/// </summary>
	/// <param name="sprite_">�X�v���C�g</param>
	/// <param name="rail">���[���J����</param>
	/// <returns></returns>
	Vector3 GetScreenToWorldPos(const Sprite& sprite_, MyEngine::RailCamera* rail);

	/// <summary>
	/// ���[���h���W����X�N���[�����W��
	/// </summary>
	/// <param name="pos_">���W</param>
	/// <param name="rail">���[���J����</param>
	/// <returns></returns>
	Vector3 GetWorldToScreenPos(const Vector3& pos_, MyEngine::RailCamera* rail);

	/// <summary>
	/// ���[���h���W�̃I�u�W�F�N�g�ɍ��킹�ăX�N���[�����W�̃X�v���C�g�̃X�P�[�����擾
	/// </summary>
	/// <param name="obj">�I�u�W�F�N�g</param>
	/// <param name="rail">���[���J����</param>
	/// <returns></returns>
	Vector2 GetWorldToScreenScale(Object3d* obj, MyEngine::RailCamera* rail);

	/// <summary>
	///  �N���A�X�V
	/// </summary>
	void ClearUpdate();

	/// <summary>
	///  �|�[�Y�X�V
	/// </summary>
	void PauseUpdate();

	/// <summary>
	/// �{�X�폈��
	/// </summary>
	void BossUpdate();

	/// <summary>
	/// ���C���Q�[������
	/// </summary>
	void MainUpdate();

private:
	//base
	DirectXCommon* dxCommon_ = nullptr;
	WinApp* winApp = nullptr;
	//���͂̃|�C���^
	Input* input = nullptr;

	//�萔
	static const int CROSSHAIR_MAX = 4;
	static const int LOCK_MAX = 10;
	static const int INFOS_MAX = 10;

	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	std::array <Sprite, CROSSHAIR_MAX> crosshair;
	std::array <Sprite, LOCK_MAX> lock;
	Sprite fade;
	float fadeAlpha;
	Sprite bossHP;
	Sprite fadeout;
	Sprite thanks;
	Sprite loading;
	Sprite tips;
	float thanksAlpha;
	Sprite dmg;
	float dmgAlpha;
	//UI
	MyEngine::GameSceneUI* UIs = nullptr;
	//�I�u�W�F�N�g�̃|�C���^
	//3D�I�u�W�F�N�g����
	MyEngine::Player* player = nullptr;
	Model* skyModel = nullptr;
	Model* seaModel = nullptr;
	Model* block01Model = nullptr;
	Model* block02Model = nullptr;
	Model* stoneModel = nullptr;
	MyEngine::Boss* boss = nullptr;
	//�J����
	ViewProjection* viewProjection = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	MyEngine::RailCamera* railCamera = nullptr;
	Vector3 cameraTmpPos;
	Vector3 cameraTmpRot;
	//�p�[�e�B�N��
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* clearParticle_01 = nullptr;
	ParticleManager* clearPM_01 = nullptr;
	Particle* clearParticle_02 = nullptr;
	ParticleManager* clearPM_02 = nullptr;
	Particle* clearParticle_03 = nullptr;
	ParticleManager* clearPM_03 = nullptr;

	//enemy
	std::list<std::unique_ptr<MyEngine::Enemy>> enemys_;
	std::list<std::unique_ptr<MyEngine::BombEnemy>> bombEnemys_;
	//�����蔻��
	CollisionManager* collisionManager = nullptr;
	//�J�����ړ��p���[��
	std::vector<Vector3> points{};
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;
	std::vector<Vector3> bossPoint{};
	std::vector < std::vector<Vector3> > lockPoints{};
	//�X�e�[�W
	bool isCheckPoint = false;
	bool isPlayable = false;
	//���b�N�I�����
	std::vector<LockInfo> infos;
	int gameTime;
	float cursorRotate;
	//�Q�[���X�e�[�^�X
	enum GameState {
		MAIN,
		BOSS,
		ULT,
		CONTINUE,
		CLEAR,
		PAUSE
	};
	GameState gameState;
	GameState gameState_bak;
	int bossPass;
	int clearTimer;
	bool isShowUI;
	int particleTimer;
	bool isNext;
	bool isSceneEnd;
	bool isPause;
	bool isbossStart;
	int bossStartTime;
	bool isBoss;
};