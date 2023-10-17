/**
 * @file DirectXCommon.cpp
 * @brief DirectX���
 * @author �J�l�R_�����E�^
 */

#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <chrono>
#include <thread>
#pragma warning(push)
#pragma warning(disable:26813)
#include<DirectXTex.h>
#pragma warning(pop)
#include "WinApp.h"
#include "FPSFixed.h"

using namespace Microsoft::WRL;

// DirectX���
class DirectXCommon final
{
public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="winApp">winApp</param>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �f�o�C�X�̏�����
	/// </summary>
	void InitializeDevice();

	/// <summary>
	/// �R�}���h�֘A�̏�����
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// �X���b�v�`�F�[���̏�����
	/// </summary>
	void InitializeSwapchain();
	
	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̏�����
	/// </summary>
	void InitializeRenderTargetView();

	/// <summary>
	/// �x�o�b�t�@�̏�����
	/// </summary>
	void InitializeDepthBuffer();
	
	/// <summary>
	/// �t�F���X�̏�����
	/// </summary>
	void InitializeFence();
	
	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();
	
	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();
	
	/// <summary>
	/// �I������
	/// </summary>
	void fpsFixedFinalize();

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
	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDevice() const { return device.Get(); }
	
	/// <summary>
	/// �R�}���h���X�g�擾
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
	
	/// <summary>
	/// �o�b�N�o�b�t�@�̐����擾
	/// </summary>
	/// <returns></returns>
	size_t GetBackBufferCount() const { return backBuffers.size(); }

private: 
	// WindowsAPI
	WinApp* winApp = nullptr;
	// FPS
	FPSFixed* fpsFixed = nullptr;

	HRESULT result = NULL;
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

	UINT rtvHD = 0;
	UINT64 fenceVal = 0;
};