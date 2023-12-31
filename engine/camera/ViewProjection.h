/**
 * @file ViewProjection.cpp
 * @brief 通常のカメラ管理クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include"Vector3.h"
#include "Vector4.h"
#include"Matrix4.h"
#include "WinApp.h"
#include<d3d12.h>
#include<wrl.h>

class ViewProjection
{
private:// サブクラス
	// 定数バッファ用データ構造体
	struct ConstBufferDataViewProjection {
		Matrix4 view;       // ワールド → ビュー変換行列
		Matrix4 projection; // ビュー → プロジェクション変換行列
		Vector3 cameraPos;  // カメラ座標（ワールド座標）
	};
public:// メンバ関数
	/// <summary>
	///  静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device_);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 視点をセット
	/// </summary>
	/// <param name="eye">視点</param>
	void SetEye(Vector3 eye_);

	/// <summary>
	/// 視点を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetEye() { return eye; }

	/// <summary>
	///　注視点をセット
	/// </summary>
	/// <param name="terget_">注視点</param>
	void SetTarget(Vector3 terget_);

	/// <summary>
	/// 注視点を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetTarget() { return target; }

	/// <summary>
	/// ビュー行列を取得
	/// </summary>
	/// <returns></returns>
	Matrix4 GetMatView() { return matView; }

	/// <summary>
	/// プロジェクション行列を取得
	/// </summary>
	/// <returns></returns>
	Matrix4 GetMatProjection() { return matProjection; }

	/// <summary>
	/// 行列を更新
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// バッファのゲッターを取得
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetBuff() { return constBuff.Get(); }


private:// プライベート関数
	// 円周率
	const float PI = 3.141592f;

	/// <summary>
	/// 定数バッファ生成
	/// </summary>
	void CreateConstBuffer();

	/// <summary>
	/// マッピングする
	/// </summary>
	void Map();

	/// <summary>
	/// 度数からラジアンに変換
	/// </summary>
	/// <param name="angle">度数</param>
	/// <returns></returns>
	float ToRadian(float angle) { return angle * (PI / 180); }


private:
#pragma region ビュー行列の設定
	// 視点座標
	Vector3 eye = { 0, 5, -10.0f };
	// 注視点座標
	Vector3 target = { 0, 0, 0 };
	// 上方向ベクトル
	Vector3 up = { 0, 1, 0 };
#pragma endregion

#pragma region 射影行列の設定
	// 垂直方向視野角
	float fovAngleY = ToRadian(45.0f);
	// ビューポートのアスペクト比
	float aspectRatio = (float)WinApp::window_width / WinApp::window_height;
	// 深度限界（手前側）
	float nearZ = 0.1f;
	// 深度限界（奥側）
	float farZ = 1000.0f;
#pragma endregion

	// ビュー行列
	Matrix4 matView;
	// 射影行列
	Matrix4 matProjection;

private:// メンバ変数

	// デバイス（借りてくる）
	static Microsoft::WRL::ComPtr<ID3D12Device> device;

	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;

	// マッピング済みアドレス
	ConstBufferDataViewProjection* constMap = nullptr;

};

