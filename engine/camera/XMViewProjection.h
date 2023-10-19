/**
 * @file XMViewProjection.cpp
 * @brief ParticleManager.cpp�Ɏg���Ă���J�����N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include <DirectXMath.h>
#include <wrl.h>

class XMViewProjection
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	XMViewProjection();
	~XMViewProjection();
	//�X�V
	void Update();
	//�r���[�s��X�V
	void UpdateViewMatrix();
	//�v���W�F�N�V�����s��X�V
	void UpdateProjectionMatrix();
	//�J�����ړ�
	void CameraMoveVector(const XMFLOAT3& move);
	//�J�������_�ړ�
	void CameraMoveVectorEye(const XMFLOAT3& move);

protected:
	// �r���[�s��
	XMMATRIX matView = {};
	// �ˉe�s��
	XMMATRIX matProjection = {};

	XMMATRIX matViewProjection = {};

	// �r���{�[�h�s��
	XMMATRIX matBillboard = {};
	// Y�����r���{�[�h�s��
	XMMATRIX matBillboardY = {};
	// ���_���W
	XMFLOAT3 eye = { 0.0f, 0.0f, -100.0f };
	// �����_���W
	XMFLOAT3 target = { 0.0f,0.0f,0.0f };
	// ������x�N�g��
	XMFLOAT3 up = { 0.0f,1.0f,0.0f };

public://�A�N�Z�b�T
	/// <summary>
	/// �r���[�s��쐬
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatView() { return matView; }

	/// <summary>
	/// �v���W�F�N�V�����s��쐬
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatProjection() { return matProjection; }

	/// <summary>
	/// �r���[�v���W�F�N�V�����s��쐬
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatViewProjection() { return matViewProjection; }

	/// <summary>
	/// �r���{�[�h�s��擾
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatBillboard() { return matBillboard; }
	const XMMATRIX& GetMatBillboardY() { return matBillboardY; }

	/// <summary>
	/// ���_�擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetEye() { return eye; }
	/// <summary>
	/// ���_���Z�b�g
	/// </summary>
	/// <param name="eye"></param>
	void SetEye(const XMFLOAT3& eye_);

	/// <summary>
	/// �����_�擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// �����_���Z�b�g
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(const XMFLOAT3& target_);

	/// <summary>
	/// ������x�N�g���擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetUp() { return up; }

	/// <summary>
	/// ������x�N�g�����Z�b�g
	/// </summary>
	/// <returns></returns>
	void SetUp(const XMFLOAT3& up_);
};
