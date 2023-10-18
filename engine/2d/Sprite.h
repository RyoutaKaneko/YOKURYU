/**
 * @file Sprite.cpp
 * @brief 画像描画関係クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <Windows.h>
#include <D3dx12.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <cassert>
#pragma warning(push)
#pragma	warning(disable:26813)
#include <DirectXTex.h>
#pragma warning(pop)
#include <wrl.h>
#include <array>
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"
#include "DirectXCommon.h"
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;



// パイプラインセット
struct PipelineSet {
	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
};

// スプライトの共通データ
struct SpriteCommon {
	// パイプラインセット
	PipelineSet pipelineSet;
	// 射影行列
	Matrix4 matProjection{};
	// テクスチャ用デスクリプタヒープの生成
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// SRVの最大枚数
	static const size_t kMaxSRVCount = 512;
	// テクスチャソース(テクスチャバッファ)の配列
	ComPtr<ID3D12Resource> texBuff[kMaxSRVCount];
	// テクスチャバッファ取得
	ID3D12Resource* GetTexBuffer(uint32_t index) const { return texBuff[index].Get(); }
};

// スプライト
class Sprite
{
public://サブクラス
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		Vector4 color;
		Matrix4 mat;	// ３Ｄ変換行列
	};

	// 頂点データ
	struct VertexPosUv {
		Vector3 pos;
		Vector2 uv;
	};
public:
	Sprite();
	~Sprite();

	/// <summary>
	/// スプライト共通データ生成
	/// </summary>
	/// <param name="dev">デバイス</param>
	/// <returns></returns>
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev);

	/// <summary>
	/// 3Dオブジェクト用パイプライン生成
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <returns></returns>
	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* device);

	/// <summary>
	/// スプライト共通テクスチャ読み込み
	/// </summary>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="texnumber">テクスチャ番号</param>
	/// <param name="filename">ファイル名</param>
	/// <param name="dev">デバイス</param>
	void LoadTexture(SpriteCommon& spriteCommon, UINT texnumber, 
		const wchar_t* filename, ID3D12Device* dev);

	/// <summary>
	/// スプライト生成
	/// </summary>
	/// <param name="dev">デバイス</param>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="anchorpoint">アンカーポイント</param>
	/// <param name="isFlipX">X反転</param>
	/// <param name="FlipY">Y反転</param>
	void SpriteCreate(ID3D12Device* dev, UINT texNumber, Vector2 anchorpoint, bool isFlipX, bool FlipY);

	/// <summary>
	///  スプライト単体頂点バッファの転送
	/// </summary>
	/// <param name="sprite">スプライト</param>
	/// <param name="texIndex_">テクスチャ番号</param>
	void SpriteTransferVertexBuffer(const Sprite& sprite, uint32_t texIndex_ = UINT32_MAX);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="sprite">スプライト</param>
	/// <param name="spriteCommon">スプライトコモン</param>
	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	/// <param name="spriteCommon">スプライトコモン</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList_">コマンドリスト</param>
	/// <param name="spriteCommon">スプライトコモン</param>
	/// <param name="dev">デバイス</param>
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, 
		ID3D12Device* dev);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

public: // セッター
	/// <summary>
	/// 座標設定
	/// </summary>
	/// <param name="position_">座標</param>
	void SetPosition(Vector3 position_) { this->position = position_; }
	
	/// <summary>
	/// スケール設定
	/// </summary>
	/// <param name="scale_">スケール</param>
	void SetScale(Vector2 scale_) { this->scale = scale_; }
	
	/// <summary>
	/// 回転設定
	/// </summary>
	/// <param name="_rotation">回転率</param>
	void SetRotation(float _rotation) { this->rotation = _rotation; }
	
	/// <summary>
	/// テクスチャ番号を設定
	/// </summary>
	/// <param name="texNumber_">テクスチャ番号</param>
	void SetTexNumber(UINT texNumber_) { this->texNumber = texNumber_; }
	
	/// <summary>
	/// 色設定
	/// </summary>
	/// <param name="color">色</param>
	void SetColor(Sprite sprite,const Vector4& color);

	/// <summary>
	/// 透過度を設定
	/// </summary>
	/// <param name="sprite">スプライト</param>
	/// <param name="alpha_">透過度</param>
	void SetAlpha(Sprite sprite, float alpha_);
	
	/// <summary>
	/// X反転フラグを設定
	/// </summary>
	/// <param name="isFlipX">X反転フラグ</param>
	void SetIsFlipX(bool isFlipX) { this->isFlipX_ = isFlipX; }

	/// <summary>
	/// Y反転フラグを設定
	/// </summary>
	/// <param name="isFlipY">Y反転フラグ</param>
	void SetIsFlipY(bool isFlipY) { this->isFlipY_ = isFlipY; }
	
	/// <summary>
	/// テクスチャ左上座標を設定
	/// </summary>
	/// <param name="texLeftTop">テクスチャ左上座標</param>
	void SetTexLeftTop(const Vector2& texLeftTop) { this->texLeftTop_ = texLeftTop; }


	/// <summary>
	/// テクスチャ切り出しサイズを設定
	/// </summary>
	/// <param name="texSize">テクスチャサイズ</param>
	void SetTexSize(const Vector2& texSize) { this->texSize_ = texSize; }

public: // ゲッター
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const { return position; }
	
	/// <summary>
	/// スケールを取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetScale() const { return scale; }
	
	/// <summary>
	/// ワールド行列を取得
	/// </summary>
	/// <returns></returns>
	Matrix4 GetMat() { return constMap->mat; }
	
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns></returns>
	float GetRotation() const { return rotation; }
	
	/// <summary>
	/// テクスチャ番号を取得
	/// </summary>
	/// <returns></returns>
	UINT GetTexNumber() const { return texNumber; }
	
	/// <summary>
	/// 色取得
	/// </summary>
	/// <returns></returns>
	Vector4 GetColor() const { return color_; }
	
	/// <summary>
	/// X反転を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFlipX() const { return isFlipX_; }

	/// <summary>
	/// Y反転を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsFlipY() const { return isFlipY_; }
	
	/// <summary>
	/// テクスチャ左上を取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetTexLeftTop() const { return texLeftTop_; }
	
	/// <summary>
	/// テクスチャ切り出しサイズを取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetTexSize() const { return texSize_; }

public:
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC();

private:
	// DirectXCommonのインスタンス
	DirectXCommon* dXCommon = nullptr;
	SpriteCommon spriteCommon_;

	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffB0 = nullptr;
	// マッピング済みアドレス
	ConstBufferDataB0* constMap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	static const size_t kMaxSRVCount = 2056;
	// テクスチャバッファ
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount> texBuffers_;

	// テクスチャ番号
	UINT texNumber = 0;
	uint32_t texIndex_ = 0;
	// 座標
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	// サイズ
	Vector2 scale = { 1.0f, 1.0f };
	// 回転
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	// ワールド行列
	Matrix4 matWorld;
	// アンカーポイント
	Vector2 anchorpoint = { 0.0f,0.0f };
	// テクスチャ左上座標設定
	Vector2 texLeftTop_ = { 50.0f, 50.0f };
	// テクスチャ切り出しサイズ
	Vector2 texSize_ = { 100.0f, 100.0f };
	// 色
	Vector4 color_ = { 1,1,1,1 };

	// Z軸回りの回転
	float rotation = 0.0f;
	// 左右反転
	bool isFlipX_ = false;
	// 上下反転
	bool isFlipY_ = false;
	// 非表示
	bool isInvisible = false;
};

