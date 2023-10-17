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
	/// ���Z�b�g
	/// </summary>
	void Reset();

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
	/// �G�l���M�[�o��
	/// </summary>
	/// <param name="pos_">���W</param>
	static void PopEnergy(Vector3 pos_);

	/// <summary>
	/// �X�N���[�����W���烏�[���h���W��
	/// </summary>
	/// <param name="sprite_">�X�v���C�g</param>
	/// <param name="rail">���[���J����</param>
	/// <returns></returns>
	Vector3 GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail);

	/// <summary>
	/// ���[���h���W����X�N���[�����W��
	/// </summary>
	/// <param name="pos_">���W</param>
	/// <param name="rail">���[���J����</param>
	/// <returns></returns>
	Vector3 GetWorldToScreenPos(Vector3 pos_, RailCamera* rail);

	/// <summary>
	/// ���[���h���W�̃I�u�W�F�N�g�ɍ��킹�ăX�N���[�����W�̃X�v���C�g�̃X�P�[�����擾
	/// </summary>
	/// <param name="obj">�I�u�W�F�N�g</param>
	/// <param name="rail">���[���J����</param>
	/// <returns></returns>
	Vector2 GetWorldToScreenScale(Object3d* obj, RailCamera* rail);

private:
	//base
	DirectXCommon* dxCommon_ = nullptr;
	WinApp* winApp = nullptr;
	//���͂̃|�C���^
	Input* input = nullptr;
	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite titleGH;
	Sprite crosshair[4];
	Sprite hp;
	Sprite clearGH;
	Sprite overGH;
	Sprite lock[10];
	Sprite fade;
	float fadeAlpha;
	Sprite bossHP;
	Sprite gage;
	Sprite gageBack;
	Sprite hpBack;
	Sprite fadeout;
	//�I�u�W�F�N�g�̃|�C���^
	//3D�I�u�W�F�N�g����
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Model* skyModel = nullptr;
	Model* seaModel = nullptr;
	Model* block01Model = nullptr;
	Model* block02Model = nullptr;
	Model* stoneModel = nullptr;
	Boss* boss = nullptr;
	//�J����
	ViewProjection* viewProjection = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	Vector3 cameraTmpPos;
	Vector3 cameraTmpRot;
	//�p�[�e�B�N��
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* particle_ = nullptr;
	ParticleManager* pm_ = nullptr;
	//enemy
	std::list<std::unique_ptr<Enemy>> enemys_;
	//energy
	static std::list<std::unique_ptr<Energy>> energys_;
	static int popEnergyCount;
	//�����蔻��
	CollisionManager* collisionManager = nullptr;
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* obj = nullptr;
	//�J�����ړ��p���[��
	std::vector<Vector3> points{};
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;
	std::vector<Vector3> bossPoint{};
	//�X�e�[�W
	int stageNum = 0;
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
		ULT
	};
	GameState gameState;
	GameState gameState_bak;
	int bossPass;
	bool isStart;
};