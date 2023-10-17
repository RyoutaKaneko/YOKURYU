/**
 * @file DirectXCommon.cpp
 * @brief DirectX基盤
 * @author カネコ_リョウタ
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

// DirectX基盤
class DirectXCommon final
{
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="winApp">winApp</param>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// デバイスの初期化
	/// </summary>
	void InitializeDevice();

	/// <summary>
	/// コマンド関連の初期化
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// スワップチェーンの初期化
	/// </summary>
	void InitializeSwapchain();
	
	/// <summary>
	/// レンダーターゲットビューの初期化
	/// </summary>
	void InitializeRenderTargetView();

	/// <summary>
	/// 度バッファの初期化
	/// </summary>
	void InitializeDepthBuffer();
	
	/// <summary>
	/// フェンスの初期化
	/// </summary>
	void InitializeFence();
	
	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();
	
	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();
	
	/// <summary>
	/// 終了処理
	/// </summary>
	void fpsFixedFinalize();

private: // メンバ関数
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
	/// デバイスの取得
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDevice() const { return device.Get(); }
	
	/// <summary>
	/// コマンドリスト取得
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
	
	/// <summary>
	/// バックバッファの数を取得
	/// </summary>
	/// <returns></returns>
	size_t GetBackBufferCount() const { return backBuffers.size(); }

private: 
	// WindowsAPI
	WinApp* winApp = nullptr;
	// FPS
	FPSFixed* fpsFixed = nullptr;

	HRESULT result = NULL;
	// DirectX12デバイス
	ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	ComPtr<IDXGIFactory7> dxgiFactory;
	// スワップチェイン
	ComPtr<IDXGISwapChain4> swapChain;
	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> commandList;
	// コマンドキュー
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;


	//バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// フェンスの生成
	ComPtr<ID3D12Fence> fence;

	UINT rtvHD = 0;
	UINT64 fenceVal = 0;
};