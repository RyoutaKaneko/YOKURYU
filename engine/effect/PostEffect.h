/**
 * @file PostEffect.cpp
 * @brief ポストエフェクトを行うクラス(基盤)
 * @author カネコ_リョウタ
 */

#pragma once
#include <Windows.h>
#include <D3dx12.h>
#include <d3dcompiler.h>
#include <cassert>
#include <DirectXTex.h>
#include <wrl.h>
#include <array>
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"
#include "DirectXCommon.h"
#pragma comment(lib, "d3dcompiler.lib")

struct VertexPosUv {
	Vector3 pos;
	Vector2 uv;
};
class PostEffect
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dev">デバイス</param>
	void Initialize(ID3D12Device* dev);
	
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList_">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList_);
	
	/// <summary>
	/// 描画前準備
	/// </summary>
	/// <param name="cmdList_">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList_);

	/// <summary>
	/// 描画後処理
	/// </summary>
	/// <param name="cmdList_">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList_);

	/// <summary>
	/// パイプライン生成
	/// </summary>
	void CreateGraphicsPipelineState();


private:
	static const float clearColor[4];

private:
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	//パイプライン
	ComPtr<ID3D12PipelineState> pipelinestate;
	//cmdList
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	//Device
	ComPtr<ID3D12Device> device;
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//定数バッファ用データ構造体
	struct ConstBufferData {
		Vector4 color; // 色 (RGBA)
		Matrix4 mat; //座標
	};
	Vector4 color = { 1,1,1,1 }; // 色 (RGBA)
	Matrix4 mat; //座標
};

