/**
 * @file Object3d.cpp
 * @brief 3dオブジェクトを動かすためのクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "CollisionInfo.h"

class BaseCollider;

/// 3Dオブジェクト
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 静的メンバ関数
	/// <summary>
	///  静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	///  描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

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
	/// グラフィックパイプライン生成
	/// </summary>
	static void InitializeGraphicsPipeline();

public: // メンバ関数

	//コンストラクタ
	Object3d() = default;

	//デストラクタ
	virtual ~Object3d();

	/// <summary>
	/// /初期化
	/// </summary>
	/// <returns></returns>
	virtual bool Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">カメラ</param>
	void Draw(ViewProjection* viewProjection);

	/// <summary>
	/// 透過付き描画
	/// </summary>
	/// <param name="viewProjection">カメラ</param>
	/// <param name="alpha_">透過度</param>
	void Draw(ViewProjection* viewProjection, float alpha_);

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns></returns>
	const Matrix4& GetMatWorld() { return matWorld; }

	/// <summary>
	/// モデルの設定
	/// </summary>
	/// <param name="model_"></param>
	void SetModel(Model* model_) { this->model = model_; }

	/// <summary>
	/// コライダーのセット
	/// </summary>
	/// <param name="collider"></param>
	void SetCollider(BaseCollider* collider);

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	virtual void OnCollision([[maybe_unused]] const CollisionInfo& info) {}

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	virtual void OffCollision([[maybe_unused]] const CollisionInfo& info) {}

	/// <summary>
	/// ワールド行列のオブジェクトの座標
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPos();

	/// <summary>
	/// ローカル位置
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const { return worldTransform_.GetPosition(); }

	/// <summary>
	/// ロック情報を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsLocked() { return isLocked; }

	/// <summary>
	/// ロック情報を取得
	/// </summary>
	/// <param name="isLock"></param>
	void SetIsLocked(bool isLock) { isLocked = isLock; }

	/// <summary>
	/// z座標を取得
	/// </summary>
	/// <returns></returns>
	const float& GetPositionZ() const { return worldTransform_.GetPosition().z; }

	/// <summary>
	/// 位置をセット
	/// </summary>
	/// <param name="position">ローカル座標</param>
	void SetPosition(const Vector3& position) { this->worldTransform_.GetPosition() = position; }
	
	/// <summary>
	/// スケールをセット
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(const Vector3& scale) { this->worldTransform_.GetScale() = scale; }

	/// <summary>
	/// スケールを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale()  { return worldTransform_.GetScale(); }
	
	/// <summary>
	/// 回転をセット
	/// </summary>
	/// <param name="rotationZ">回転率</param>
	void SetRotation(const Vector3& rotation) { this->worldTransform_.GetRotation() = rotation; }

	/// <summary>
	/// 回転をセット
	/// </summary>
	/// <returns></returns>
	const Vector3& GetRotation()  { return worldTransform_.GetRotation(); }

	/// <summary>
	/// 名前を取得
	/// </summary>
	/// <returns></returns>
	const char* GetName() { return name; }

	/// <summary>
	/// 衝突相手の名前を取得
	/// </summary>
	/// <returns></returns>
	const char* GetToCollName() { return toCollisionName; }

	/// <summary>
	/// 衝突相手の名前を設定
	/// </summary>
	/// <returns></returns>
	void SetToCollName(const char* toCollName_) { toCollisionName = toCollName_; }

	/// <summary>
	/// ワールドトランスフォームを取得
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform() { return worldTransform_; }
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	const char* toCollisionName = nullptr;

protected: // メンバ変数
	//クラス名
	const char* name = nullptr;
	//コライダー
	BaseCollider* collider = nullptr;
	// モデル
	Model* model = nullptr;
	// ローカルワールド変換行列
	Matrix4 matWorld;
	//ロックされているかどうか
	bool isLocked;
};

