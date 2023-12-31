/**
 * @file XMViewProjection.cpp
 * @brief ParticleManager.cppに使っているカメラクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <DirectXMath.h>
#include <wrl.h>

class XMViewProjection
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	XMViewProjection();
	~XMViewProjection();
	//更新
	void Update();
	//ビュー行列更新
	void UpdateViewMatrix();
	//プロジェクション行列更新
	void UpdateProjectionMatrix();
	//カメラ移動
	void CameraMoveVector(const XMFLOAT3& move);
	//カメラ視点移動
	void CameraMoveVectorEye(const XMFLOAT3& move);

protected:
	// ビュー行列
	XMMATRIX matView = {};
	// 射影行列
	XMMATRIX matProjection = {};

	XMMATRIX matViewProjection = {};

	// ビルボード行列
	XMMATRIX matBillboard = {};
	// Y軸回りビルボード行列
	XMMATRIX matBillboardY = {};
	// 視点座標
	XMFLOAT3 eye = { 0.0f, 0.0f, -100.0f };
	// 注視点座標
	XMFLOAT3 target = { 0.0f,0.0f,0.0f };
	// 上方向ベクトル
	XMFLOAT3 up = { 0.0f,1.0f,0.0f };

public://アクセッサ
	/// <summary>
	/// ビュー行列作成
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatView() { return matView; }

	/// <summary>
	/// プロジェクション行列作成
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatProjection() { return matProjection; }

	/// <summary>
	/// ビュープロジェクション行列作成
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatViewProjection() { return matViewProjection; }

	/// <summary>
	/// ビルボード行列取得
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatBillboard() { return matBillboard; }
	const XMMATRIX& GetMatBillboardY() { return matBillboardY; }

	/// <summary>
	/// 視点取得
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetEye() { return eye; }
	/// <summary>
	/// 視点をセット
	/// </summary>
	/// <param name="eye"></param>
	void SetEye(const XMFLOAT3& eye_);

	/// <summary>
	/// 注視点取得
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点をセット
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(const XMFLOAT3& target_);

	/// <summary>
	/// 上方向ベクトル取得
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetUp() { return up; }

	/// <summary>
	/// 上方向ベクトルをセット
	/// </summary>
	/// <returns></returns>
	void SetUp(const XMFLOAT3& up_);
};
