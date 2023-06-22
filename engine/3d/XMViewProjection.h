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
	//�r���[�s��
	const XMMATRIX& GetMatView() { return matView_; }

	//�v���W�F�N�V�����s��
	const XMMATRIX& GetMatProjection() { return matProjection_; }

	const XMMATRIX& GetMatViewProjection() { return matViewProjection_; }

	//�r���{�[�h�s��
	const XMMATRIX& GetMatBillboard() { return matBillboard_; }
	const XMMATRIX& GetMatBillboardY() { return matBillboardY_; }

	//���_
	const XMFLOAT3& GetEye() { return eye_; }
	void SetEye(const XMFLOAT3& eye);

	//�����_
	const XMFLOAT3& GetTarget() { return target_; }
	void SetTarget(const XMFLOAT3& target);

	//������x�N�g��
	const XMFLOAT3& GetUp() { return up_; }
	void SetUp(const XMFLOAT3& up);
};