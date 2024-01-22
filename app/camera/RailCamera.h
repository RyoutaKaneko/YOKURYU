/**
 * @file RaikCamera.cpp
 * @brief ゲーム内のレールカメラ制御に使う関数群をまとめてある
 * @author カネコ_リョウタ
 */

#pragma once
#include "ViewProjection.h"
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Player.h"

class RailCamera {
public:
	//インスタンス
	RailCamera();
	~RailCamera();

	/// <summary>
	///  初期化
	/// </summary>
	/// <param name="player_">プレイヤー</param>
	void Initialize();
	
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="player_">プレイヤー</param>
	/// <param name="point">レールカメラ通過点</param>
	void Update(Player* player_, std::vector<Vector3>& point);

	/// <summary>
	/// カメラのみ更新
	/// </summary>
	void ViewUpdate();

	/// <summary>
	/// 画面シェイク
	/// </summary>
	/// <param name="x">xの乱数</param>
	/// <param name="y">yの乱数</param>
	void ShakeCamera(float x, float y);

	/// <summary>
	/// 
	/// </summary>
	void TitleR();

	/// <summary>
	/// カメラリセット
	/// </summary>
	void RailReset();

	/// <summary>
	/// プレイヤーをレールにセット
	/// </summary>
	/// <param name="player_">プレイヤー</param>
	void SetPlayer(Player* player_);
	/// <summary>
	/// 視点をセット
	/// </summary>
	/// <param name="view">カメラ</param>
	void SetEye(Vector3 view);

	/// <summary>
	/// 注視点をセット
	/// </summary>
	/// <param name="target">注視点</param>
	void SetTarget(Vector3 target);

	/// <summary>
	///  レール上かどうか
	/// </summary>
	/// <param name="onrail">レール上フラグ</param>
	void SetOnRail(bool onrail) { OnRail = onrail; }

	/// <summary>
	/// Y成分を0にした正面ベクトルを取得
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	void GetVec(Vector3 a, Vector3 b);

	/// <summary>
	/// viewProjection取得
	/// </summary>
	/// <returns></returns>
	ViewProjection* GetView() { return viewProjection; }

	/// <summary>
	///  レールの最後まで行ったかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsEnd() { return isEnd; }

	/// <summary>
	/// レール上かどうかを取得
	/// </summary>
	/// <returns></returns>
	bool GetOnRail() { return OnRail; }

	/// <summary>
	/// 正面ベクトルを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetFrontVec() { return frontVec; }

	/// <summary>
	/// レールカメラオブジェクトを取得
	/// </summary>
	/// <returns></returns>
	Object3d* GetCamera() { return camera; }

	/// <summary>
	/// レールカメラオブジェクトの座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetCameraPos() { return camera->GetWorldTransform().GetPosition(); }

	/// <summary>
	/// 通過点を取得
	/// </summary>
	/// <returns></returns>
	float GetPasPoint() { return splineCam.GetT(); }
private:
	static const float PI;
	static const float DEGREES;
	static const float DELAY;
	static const float ADD_DELAY;

private:
	Input* input_ = nullptr;
	ViewProjection* viewProjection = nullptr;
	Object3d* camera = nullptr;
	Input* input = nullptr;

	//スプライン
	Spline spline_;
	Spline splineCam;

	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0,0,0 };
	Vector3 oldCamera = { 0,0,0 };

	//カメラディレイ
	Vector3 playerMoveVel;
	Vector3 cameraDelay;

	//tmp
	Vector3 eyeTmp{};
	Vector3 targetTmp{};
	Vector3 up;

	bool isEnd;
	bool OnRail;
	float targetVel;
	float cameraVel;
};

