/**
 * @file ParticleManager.cpp
 * @brief パーティクル管理クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Particle.h"
#include "XMViewProjection.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

/// 3Dオブジェクト
class ParticleManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX matBillboard;	//ビルボード行列
	};
public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device_);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList_);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static ParticleManager* Create();

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

private:// 静的メンバ関数

	/// <summary>
	/// グラフィックスパイプライン生成
	/// </summary>
	static void InitializeGraphicsPipeline();

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	bool Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル発射
	/// </summary>
	/// <param name="particle">パーティクル</param>
	/// <param name="setpos">発射位置</param>
	/// <param name="setvel">発射速度</param>
	/// <param name="setacc">縦移動</param>
	/// <param name="setnum">発射個数</param>
	/// <param name="setscale">スケール</param>
	void Fire(Particle* particle, XMFLOAT3 pos, const float& setpos, const float& setvel, const float& setacc, const int& setnum, const XMFLOAT2& setscale);

private: // メンバ変数
	ComPtr<ID3D12Resource> constBuff; // 定数バッファ
	//スケール
	XMFLOAT3 scale = { 1,1,1 };

	//DirectXMathを使ったViewProjection
	XMViewProjection* xmViewProjection = nullptr;
	//パーティクル
	Particle* particle = nullptr;

public://setter
	//パーティクルモデル
	void SetParticleModel(Particle* particlemodel) { this->particle = particlemodel; }
	//カメラ
	void SetXMViewProjection(XMViewProjection* xmViewProjection_) { this->xmViewProjection = xmViewProjection_; }
};