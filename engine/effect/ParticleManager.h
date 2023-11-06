/**
 * @file ParticleManager.cpp
 * @brief �p�[�e�B�N���Ǘ��N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Particle.h"
#include "XMViewProjection.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

/// 3D�I�u�W�F�N�g
class ParticleManager
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX matBillboard;	//�r���{�[�h�s��
	};
public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device_);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList_);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static ParticleManager* Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

private:// �ÓI�����o�֐�

	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C������
	/// </summary>
	static void InitializeGraphicsPipeline();

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	bool Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�[�e�B�N������
	/// </summary>
	/// <param name="particle">�p�[�e�B�N��</param>
	/// <param name="setpos">���ˈʒu</param>
	/// <param name="setvel">���ˑ��x</param>
	/// <param name="setacc">�c�ړ�</param>
	/// <param name="setnum">���ˌ�</param>
	/// <param name="setscale">�X�P�[��</param>
	void Fire(Particle* particle, XMFLOAT3 pos, const float& setpos, const float& setvel, const float& setacc, const int& setnum, const XMFLOAT2& setscale);

private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@
	//�X�P�[��
	XMFLOAT3 scale = { 1,1,1 };

	//DirectXMath���g����ViewProjection
	XMViewProjection* xmViewProjection = nullptr;
	//�p�[�e�B�N��
	Particle* particle = nullptr;

public://setter
	//�p�[�e�B�N�����f��
	void SetParticleModel(Particle* particlemodel) { this->particle = particlemodel; }
	//�J����
	void SetXMViewProjection(XMViewProjection* xmViewProjection_) { this->xmViewProjection = xmViewProjection_; }
};