/**
 * @file Boss.cpp
 * @brief �{�X�S��(�X�e�[�^�X�A�s���A�`��)���܂Ƃ߂�����
 * @author �J�l�R_�����E�^
 */

#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include "BossBullet.h"

//GameScene�̑O���錾
class GameScene;

class Boss : public Object3d
{
public:
	//�f�X�g���N�^
	~Boss();
	
	/// <summary>
	/// ������
	/// </summary>
	void BossInitialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="velo">�e�x�N�g��</param>
	void Update(Vector3 velo);

	/// <summary>
	/// �{�X�o��
	/// </summary>
	void Pop();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// ��ԕω�
	/// </summary>
	void ChangeState();
	
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection_">�J����</param>
	void BossDraw(ViewProjection* viewProjection_);

	/// <summary>
	/// ���S�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead_; }
	
	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(const CollisionInfo& info) override;
	
	/// <summary>
	/// �{�X�o����Ԃ��擾
	/// </summary>
	/// <returns></returns>
	bool GetIsInvisible() { return isInvisible; }

	/// <summary>
	/// ���ߓx���擾
	/// </summary>
	/// <returns></returns>
	float GetAlpha() { return bossAlpha; }

	/// <summary>
	/// �^�C�}�[���擾
	/// </summary>
	/// <returns></returns>
	int GetTimer() { return appearTimer; }

	/// <summary>
	/// HP���擾
	/// </summary>
	/// <returns></returns>
	float GetHP() { return hp; }

	/// <summary>
	/// �p�[�c�����擾
	/// </summary>
	/// <returns></returns>
	int GetPartsNum() { return PARTS_NUM; }

	/// <summary>
	/// �p�[�c���擾
	/// </summary>
	/// <param name="i">�p�[�c�ԍ�</param>
	/// <returns></returns>
	Object3d* GetParts(int i) { return parts[i]; }

	/// <summary>
	/// �{�X�o�ꉉ�o���X�L�b�v
	/// </summary>
	void SkipMovie();

	/// <summary>
	/// �|���ꂽ���o
	/// </summary>
	void SlainUpdate();

	/// <summary>
	/// �|���ꂽ�t���O�擾
	/// </summary>
	/// <returns></returns>
	bool GetISlained() { return isSlained; }

	

private:

	static const int STATE_TIME = 125;
	static const int HIT_TIME_MAX = 10;
	static const int DAMAGE_NUM = 5;
	static const int SLAIN_TIME = 30;
	static const int POP_TIME_ONE = 35;
	static const int POP_TIME_TWO = 70;
	static const int POP_TIME_MAX = 150;
	static const int APPEAR_TIME = 75;
	static const float MAX_ALPHA;
	static const float ADD_ALPHA;
	static const float SHADOW_Y;
	static const float SHADOW_SCALE_AD;

private:
	//�f�X�t���O
	bool isDead_ = false;
	bool isInvisible = true;
	//�^�C�}�[
	int appearTimer = 0;
	float bossAlpha = 0.0f;
	float hp;
	bool isHit;
	int hitTimer;
	int timeCount;
	int timer;
	
	//�{�X�s�����
	enum State {
		WAIT,
		SHOT
	};
	State state;

	// ���f��
	Model* bossModel = nullptr;
	Model* shadowModel = nullptr;
	//�e
	std::list<std::unique_ptr<BossBullet>> bullets_;
	static const int PARTS_NUM = 5;
	Object3d* parts[PARTS_NUM];
	Object3d* shadow = nullptr;
	Vector3 movePower = {0.5f,0.5f,0.5f};
	Vector3 postmp;
	Vector3 bossSkipPos;
	Vector3 addVec;
	int slainTimer;
	bool isSlained;
};
