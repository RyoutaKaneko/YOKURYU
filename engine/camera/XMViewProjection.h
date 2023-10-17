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
	XMMATRIX matView_ = {};
	// �ˉe�s��
	XMMATRIX matProjection_ = {};

	XMMATRIX matViewProjection_ = {};

	// �r���{�[�h�s��
	XMMATRIX matBillboard_ = {};
	// Y�����r���{�[�h�s��
	XMMATRIX matBillboardY_ = {};
	// ���_���W
	XMFLOAT3 eye_ = { 0.0f, 0.0f, -100.0f };
	// �����_���W
	XMFLOAT3 target_ = { 0.0f,0.0f,0.0f };
	// ������x�N�g��
	XMFLOAT3 up_ = { 0.0f,1.0f,0.0f };

public://�A�N�Z�b�T
	/// <summary>
	/// �r���[�s��쐬
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatView() { return matView_; }

	/// <summary>
	/// �v���W�F�N�V�����s��쐬
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatProjection() { return matProjection_; }

	/// <summary>
	/// �r���[�v���W�F�N�V�����s��쐬
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatViewProjection() { return matViewProjection_; }

	/// <summary>
	/// �r���{�[�h�s��擾
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatBillboard() { return matBillboard_; }
	const XMMATRIX& GetMatBillboardY() { return matBillboardY_; }

	/// <summary>
	/// ���_�擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetEye() { return eye_; }
	/// <summary>
	/// ���_���Z�b�g
	/// </summary>
	/// <param name="eye"></param>
	void SetEye(const XMFLOAT3& eye);

	/// <summary>
	/// �����_�擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetTarget() { return target_; }

	/// <summary>
	/// �����_���Z�b�g
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(const XMFLOAT3& target);

	/// <summary>
	/// ������x�N�g���擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetUp() { return up_; }

	/// <summary>
	/// ������x�N�g�����Z�b�g
	/// </summary>
	/// <returns></returns>
	void SetUp(const XMFLOAT3& up);
};
