/**
 * @file Particle.cpp
 * @brief パーティクル管理クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <forward_list>

class Particle
{
private://エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス

	struct VertexPosScale
	{
		XMFLOAT3 pos; // xyz座標
		float scale;  //スケール
	};

	//パーティクル一粒
	struct OneParticle
	{
		//DirectX::を省略
		using XMFLOAT3 = DirectX::XMFLOAT3;

		//座標
		XMFLOAT3 position = {};
		//速度
		XMFLOAT3 velocity = {};
		//加速度
		XMFLOAT3 accel = {};
		//現在フレーム
		int frame = 0;
		//終了フレーム
		int num_frame = 0;

		//スケール
		float scale = 1.0f;
		//初期値
		float s_Scale = 1.0f;
		//最終値
		float e_Scale = 0.0f;
	};

private://定数
	static const int vertexCount = 1024;		// 頂点数

public://メンバ関数

	/// <summary>
	/// OBJファイルからパーティクルモデルを読み込む
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns></returns>
	static Particle* LoadParticleTexture(const std::string& fileName);
	
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	void InitializeDescriptorHeap();
	
	/// <summary>
	/// クスチャ読み込み
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	void LoadTexture(const std::string& fileName);

	/// <summary>
	/// 各種バッファ生成
	/// </summary>
	void CreateBuffers();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// パーティクルの追加
	/// </summary>
	/// <param name="life">存在時間</param>
	/// <param name="position">位置</param>
	/// <param name="velocity">速度</param>
	/// <param name="accel">縦移動</param>
	/// <param name="start_scale">開始スケール</param>
	/// <param name="end_scale">終了スケール</param>
	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel,
		float start_scale, float end_scale);

private://メンバ変数
	// デバイス
	static ID3D12Device* device_;
	//デフォルトテクスチャ格納ディレクトリ
	static std::string defaultTextureDirectoryPath_;

	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize_;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap_;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff_;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV_;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV_;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff_;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView_;
	//頂点データ配列
	VertexPosScale vertices_[vertexCount];

	std::forward_list<OneParticle> particles_;

public://setter
	/// <summary>
	/// デバイスをセット
	/// </summary>
	/// <param name="device"></param>
	static void SetDevice(ID3D12Device* device) { Particle::device_ = device; }

};

const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);