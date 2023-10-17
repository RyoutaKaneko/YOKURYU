/**
 * @file ViewProjection.cpp
 * @brief �ʏ�̃J�����Ǘ��N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include"Vector3.h"
#include "Vector4.h"
#include"Matrix4.h"
#include "WinApp.h"
#include<d3d12.h>
#include<wrl.h>

class ViewProjection
{
public:// �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataViewProjection {
		Matrix4 view;       // ���[���h �� �r���[�ϊ��s��
		Matrix4 projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
		Vector3 cameraPos;  // �J�������W�i���[���h���W�j
	};
public:// �����o�֐�
	/// <summary>
	///  �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���_���Z�b�g
	/// </summary>
	/// <param name="eye_">���_</param>
	void SetEye(Vector3 eye_);

	/// <summary>
	/// ���_���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetEye() { return eye; }

	/// <summary>
	///�@�����_���Z�b�g
	/// </summary>
	/// <param name="terget_">�����_</param>
	void SetTarget(Vector3 terget_);

	/// <summary>
	/// �����_���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetTarget() { return target; }

	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	/// <returns></returns>
	Matrix4 GetMatView() { return matView; }

	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	/// <returns></returns>
	Matrix4 GetMatProjection() { return matProjection; }

	/// <summary>
	/// �s����X�V
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// �o�b�t�@�̃Q�b�^�[���擾
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetBuff() { return constBuff.Get(); }


private:// �v���C�x�[�g�֐�
	// �~����
	const float PI = 3.141592f;

	/// <summary>
	/// �萔�o�b�t�@����
	/// </summary>
	void CreateConstBuffer();

	/// <summary>
	/// �}�b�s���O����
	/// </summary>
	void Map();

	/// <summary>
	/// �x�����烉�W�A���ɕϊ�
	/// </summary>
	/// <param name="angle">�x��</param>
	/// <returns></returns>
	float ToRadian(float angle) { return angle * (PI / 180); }


public:// �p�u���b�N�ϐ�
#pragma region �r���[�s��̐ݒ�
	// ���_���W
	Vector3 eye = { 0, 5, -10.0f };
	// �����_���W
	Vector3 target = { 0, 0, 0 };
	// ������x�N�g��
	Vector3 up = { 0, 1, 0 };
#pragma endregion

#pragma region �ˉe�s��̐ݒ�
	// ������������p
	float fovAngleY = ToRadian(45.0f);
	// �r���[�|�[�g�̃A�X�y�N�g��
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	// �[�x���E�i��O���j
	float nearZ = 0.1f;
	// �[�x���E�i�����j
	float farZ = 1000.0f;
#pragma endregion

	// �r���[�s��
	Matrix4 matView;
	// �ˉe�s��
	Matrix4 matProjection;

private:// �����o�ϐ�

	// �f�o�C�X�i�؂�Ă���j
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;

	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataViewProjection* constMap = nullptr;

};

