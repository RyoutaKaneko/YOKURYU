/**
 * @file WorldTransform.cpp
 * @brief 3dオブジェクトの座標管理、アフィン変換を行うクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include"Vector3.h"
#include "Vector4.h"
#include"Matrix4.h"
#include<d3d12.h>
#include<wrl.h>

class WorldTransform
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


public:// サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferDataB0 {
		Matrix4 matWorld;// 行列
	};
public:// メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 行列を更新する
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	///  定数バッファのゲッター
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetBuff() { return constBuffB0.Get(); }

	/// <summary>
	/// 定数バッファ生成
	/// </summary>
	void CreateConstBuffer();

	/// <summary>
	/// マッピングする
	/// </summary>
	void Map();

	/// <summary>
	/// 現在位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const { return position; }

	/// <summary>
	/// 度数からラジアンに変換
	/// </summary>
	/// <param name="angle">度数</param>
	/// <returns></returns>
	float ToRadian(float angle) { return angle * (PI / 180); }

	/// <summary>
	/// 親子関係をセット
	/// </summary>
	/// <param name="parent"></param>
	void SetParent3d(WorldTransform* parent_) { this->parent = parent_; }

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3& GetPosition() { return position; }

	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns></returns>
	Vector3& GetRotation() { return rotation; }

	/// <summary>
	/// スケールを取得
	/// </summary>
	/// <returns></returns>
	Vector3& GetScale() { return scale; }

	/// <summary>
	/// ワールド行列を取得
	/// </summary>
	/// <returns></returns>
	Matrix4 GetMatWorld() { return matWorld; }

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="position_">座標</param>
	void SetPosition(Vector3 position_) { position = position_; }

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation_">回転率</param>
	void SetRotation(Vector3 rotation_) { rotation = rotation_; }

	/// <summary>
	/// スケールを設定
	/// </summary>
	/// <param name="scale_">スケール</param>
	void SetScale(Vector3 scale_) { scale = scale_; }

private:// パブリック変数
	// ローカルスケール
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation = { 0, 0, 0 };

	// ローカル座標
	Vector3 position = { 0, 0, 0 };

	// 色
	Vector4 color = { 1,1,1,1 };

	// ローカル → ワールド変換行列
	Matrix4 matWorld;

	// 親となるワールド変換へのポインタ
	const WorldTransform* parent = nullptr;

	// 円周率
	const float PI = 3.141592f;

private:// メンバ変数
	// デバイス
	static ComPtr<ID3D12Device> device;

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffB0;

	// マッピング済みアドレス
	ConstBufferDataB0* constMap = nullptr;
};

