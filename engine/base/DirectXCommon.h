#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <chrono>
#include <thread>

#include <DirectXTex.h>

#include "WinApp.h"

using namespace Microsoft::WRL;

// DirectX���
class DirectXCommon final
{
public: // �����o�֐�
	// ������
	void Initialize(WinApp* winApp);
	// �f�o�C�X�̏�����
	void InitializeDevice();
	// �R�}���h�֘A�̏�����
	void InitializeCommand();
	// �X���b�v�`�F�[���̏�����
	void InitializeSwapchain();
	// �����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRenderTargetView();
	// �[�x�o�b�t�@�̏�����
	void InitializeDepthBuffer();
	// �t�F���X�̏�����
	void InitializeFence();
	// �`��O����
	void PreDraw();
	// �`��㏈��
	void PostDraw();

private: // �����o�֐�
	template <class T>
	inline void safe_delete(T*& p) {
		delete p;
		p = nullptr;
	}

public:
	static DirectXCommon* GetInstance();

private:
	DirectXCommon() = default;
	~DirectXCommon() = default;
	DirectXCommon(const DirectXCommon&) = delete;
	DirectXCommon& operator=(const DirectXCommon&) = delete;
	

public: // Getter
	// �f�o�C�X�̎擾
	ID3D12Device* GetDevice() const { return device.Get(); }
	// �R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
	// �o�b�N�o�b�t�@�̐����擾
	size_t GetBackBufferCount() const { return backBuffers.size(); }

private: 
	// WindowsAPI
	WinApp* winApp = nullptr;

	HRESULT result;
	// DirectX12�f�o�C�X
	ComPtr<ID3D12Device> device;
	// DXGI�t�@�N�g��
	ComPtr<IDXGIFactory7> dxgiFactory;
	// �X���b�v�`�F�C��
	ComPtr<IDXGISwapChain4> swapChain;
	// �R�}���h�A���P�[�^
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	// �R�}���h���X�g
	ComPtr<ID3D12GraphicsCommandList> commandList;
	// �R�}���h�L���[
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;


	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// �t�F���X�̐���
	ComPtr<ID3D12Fence> fence;

	UINT rtvHD;
	UINT64 fenceVal = 0;
};