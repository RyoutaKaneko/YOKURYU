/**
 * @file RaikCamera.cpp
 * @brief �Q�[�����̃��[���J��������Ɏg���֐��Q���܂Ƃ߂Ă���
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "ViewProjection.h"
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Player.h"

class RailCamera {
public:
	//�C���X�^���X
	RailCamera();
	~RailCamera();

	/// <summary>
	///  ������
	/// </summary>
	/// <param name="player_">�v���C���[</param>
	void Initialize();
	
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="player_">�v���C���[</param>
	/// <param name="point">���[���J�����ʉߓ_</param>
	void Update(Player* player_, std::vector<Vector3>& point);

	/// <summary>
	/// �J�����̂ݍX�V
	/// </summary>
	void ViewUpdate();

	/// <summary>
	/// ��ʃV�F�C�N
	/// </summary>
	/// <param name="x">x�̗���</param>
	/// <param name="y">y�̗���</param>
	void ShakeCamera(float x, float y);

	/// <summary>
	/// 
	/// </summary>
	void TitleR();

	/// <summary>
	/// �J�������Z�b�g
	/// </summary>
	void RailReset();

	/// <summary>
	/// �v���C���[�����[���ɃZ�b�g
	/// </summary>
	/// <param name="player_">�v���C���[</param>
	void SetPlayer(Player* player_);
	/// <summary>
	/// ���_���Z�b�g
	/// </summary>
	/// <param name="view">�J����</param>
	void SetEye(Vector3 view);

	/// <summary>
	/// �����_���Z�b�g
	/// </summary>
	/// <param name="target">�����_</param>
	void SetTarget(Vector3 target);

	/// <summary>
	///  ���[���ォ�ǂ���
	/// </summary>
	/// <param name="onrail">���[����t���O</param>
	void SetOnRail(bool onrail) { OnRail = onrail; }

	/// <summary>
	/// Y������0�ɂ������ʃx�N�g�����擾
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	void GetVec(Vector3 a, Vector3 b);

	/// <summary>
	/// viewProjection�擾
	/// </summary>
	/// <returns></returns>
	ViewProjection* GetView() { return viewProjection; }

	/// <summary>
	///  ���[���̍Ō�܂ōs�������ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetIsEnd() { return isEnd; }

	/// <summary>
	/// ���[���ォ�ǂ������擾
	/// </summary>
	/// <returns></returns>
	bool GetOnRail() { return OnRail; }

	/// <summary>
	/// ���ʃx�N�g�����擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetFrontVec() { return frontVec; }

	/// <summary>
	/// ���[���J�����I�u�W�F�N�g���擾
	/// </summary>
	/// <returns></returns>
	Object3d* GetCamera() { return camera; }

	/// <summary>
	/// ���[���J�����I�u�W�F�N�g�̍��W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetCameraPos() { return camera->GetWorldTransform().GetPosition(); }

	/// <summary>
	/// �ʉߓ_���擾
	/// </summary>
	/// <returns></returns>
	float GetPasPoint() { return splineCam.GetT(); }
private:
	static const float PI;
	static const float DEGREES;
	static const float DELAY;
	static const float ADD_DELAY;

private:
	Input* input_ = nullptr;
	ViewProjection* viewProjection = nullptr;
	Object3d* camera = nullptr;
	Input* input = nullptr;

	//�X�v���C��
	Spline spline_;
	Spline splineCam;

	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0,0,0 };
	Vector3 oldCamera = { 0,0,0 };

	//�J�����f�B���C
	Vector3 playerMoveVel;
	Vector3 cameraDelay;

	//tmp
	Vector3 eyeTmp{};
	Vector3 targetTmp{};
	Vector3 up;

	bool isEnd;
	bool OnRail;
	float targetVel;
	float cameraVel;
};

