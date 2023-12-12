///**
// * @file FbxObject3d.cpp
// * @brief fbxモデルを3dオブジェクトとして扱うためのクラス
// * @author カネコ_リョウタ
// */
//
//#pragma once
//#include "FbxModel.h"
//#include "ViewProjection.h"
//#include "WorldTransform.h"
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vector4.h"
//#include "Matrix4.h"
//#include <Windows.h>
//#include <wrl.h>
//#include <d3d12.h>
//#include <d3dx12.h>
//#include <string>
//
//class FbxObject3d {
//protected://エイリアス
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//public:
//	/// <summary>
//	/// 静的初期化
//	/// </summary>
//	/// <param name="device">デバイス</param>
//	static void StaticInitialize(ID3D12Device* device);
//
//	/// <summary>
//	/// カメラをセット
//	/// </summary>
//	/// <param name="view_">カメラ</param>
//	static void SetCamera(ViewProjection* view_) { FbxObject3d::view = view_; }
//
//	/// <summary>
//	/// 描画前処理
//	/// </summary>
//	/// <param name="cmdList">コマンドリスト</param>
//	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
//	
//	/// <summary>
//	/// 描画後処理
//	/// </summary>
//	static void PostDraw();
//
//	/// <summary>
//	/// グラフィックスパイプライン生成
//	/// </summary>
//	static void CreateGraphicsPipeline();
//private://静的メンバ変数
//	static ID3D12Device* device;
//	static ViewProjection* view;
//public://サブクラス
//	struct ConstBufferDataTransform {
//		Matrix4 viewproj;
//		Matrix4 world;
//		Vector3 cameraPos;
//	};
//public://メンバ関数
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	void Initialize();
//
//	/// <summary>
//	/// 更新
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// モデルをセット
//	/// </summary>
//	/// <param name="model_">モデル</param>
//	void SetModel(FbxModel* model_) { this->model = model_; }
//
//	/// <summary>
//	/// 描画
//	/// </summary>
//	/// <param name="viewProjection">カメラ</param>
//	void Draw(ViewProjection* viewProjection);
//
//	/// <summary>
//	/// 座標を取得
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetPosition() const { return worldTransform.GetPosition(); }
//
//	/// <summary>
//	/// 座標をセット
//	/// </summary>
//	/// <param name="position">座標</param>
//	void SetPosition(const Vector3& position) { this->worldTransform.GetPosition() = position; }
//	
//	/// <summary>
//	/// スケールを取得
//	/// </summary>
//	/// <param name="scale">スケール</param>
//	void SetScale(const Vector3& scale) { this->worldTransform.GetScale() = scale; }
//
//	/// <summary>
//	/// スケールを取得
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetScale()  { return worldTransform.GetScale(); }
//	
//	/// <summary>
//	/// オブジェクトの回転をセット
//	/// </summary>
//	/// <param name="rotationZ">回転率</param>
//	void SetRotation(const Vector3& rotation) { this->worldTransform.GetRotation() = rotation; }
//
//	/// <summary>
//	/// オブジェクトの回転を取得
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetRotation()  { return worldTransform.GetRotation(); }
//
//protected://メンバ変数
//	ComPtr<ID3D12Resource> constBuffTransform;
//private:
//	static ComPtr<ID3D12RootSignature> rootsignature;
//	static ComPtr<ID3D12PipelineState> pipelinestate;
//	// コマンドリスト
//	static ID3D12GraphicsCommandList* cmdList;
//
//	WorldTransform worldTransform;
//	FbxModel* model = nullptr;
//};