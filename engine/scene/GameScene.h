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


class GameScene {
public:
	//�����o�֐�
	GameScene();

	~GameScene();

	void Initialize(SpriteCommon& spriteCommon);
	void LoadObjFromLevelEditor(const std::string& fileName);

	void Update();

	void Draw();
	void Reset();

	void LoadStage(int stageNum);
	void LoadEnemy(int stageNum);
	void SerchEnemy();
	void LockedClear();
	void GetCrosshair();

	Vector3 GetScreenToWorldPos(Sprite& sprite_, RailCamera* rail);
	Vector3 GetWorldToScreenPos(Vector3 pos_, RailCamera* rail);
	Vector2 GetWorldToScreenScale(Object3d* obj, RailCamera* rail);

private:
	//base
	DirectXCommon* dxCommon = nullptr;
	WinApp* winApp = nullptr;
	//���͂̃|�C���^
	Input* input = nullptr;
	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite titleGH;
	Sprite crosshair[4];
	Sprite hp[5];
	Sprite clearGH;
	Sprite overGH;
	Sprite lock[10];
	Sprite fade;
	float fadeAlpha;
	Sprite bossHP;
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
	//�p�[�e�B�N��
	Particle* particle = nullptr;
	ParticleManager* pm = nullptr;
	Particle* particle_ = nullptr;
	ParticleManager* pm_ = nullptr;
	//enemy
	std::list<std::unique_ptr<Enemy>> enemys_;
	//�����蔻��
	CollisionManager* collisionManager = nullptr;
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* obj = nullptr;
	//�J�����ړ��p���[��
	std::vector<Vector3> points{};
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;
	//�X�e�[�W
	int stageNum = 0;
	bool isCheckPoint = false;
	bool isPlayable = false;

	std::vector<LockInfo> infos;

	enum Scene {
		TITLE,
		GAME,
		CLEAR,
		OVER
	};
	Scene sceneNum;
	int gameTime;
	float cursorRotate;
	//leveleditor
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};