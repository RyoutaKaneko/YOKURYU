/**
 * @file Matrix4.cpp
 * @brief 4x4行列クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Vector3.h"
#include "Vector2.h"

class Matrix4
{
public:

	// Matrix4 構造体
	float m[4][4];


	// コンストラクタ
	Matrix4();
	// 成分を指定しての生成
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// <summary>
	/// 単位行列を求める
	/// </summary>
	/// <returns></returns>
	static Matrix4 identity();

	/// <summary>
	/// 逆行列を求める
	/// </summary>
	/// <returns></returns>
	Matrix4 MakeInverse();

	/// <summary>
	/// 拡大縮小行列の設定
	/// </summary>
	/// <param name="s">スケール</param>
	/// <returns></returns>
	Matrix4 scale(const Vector3& s);

	/// <summary>
	/// // 回転行列の設定
	/// </summary>
	/// <param name="angle">ラジアンで回転率</param>
	/// <returns></returns>
	Matrix4 rotateX(float angle);
	Matrix4 rotateY(float angle);
	Matrix4 rotateZ(float angle);

	/// <summary>
	/// 平行移動行列の作成
	/// </summary>
	/// <param name="t">移動量</param>
	/// <returns></returns>
	Matrix4 translate(const Vector3& t);

	/// <summary>
	/// 座標変換（ベクトルと行列の掛け算をする）
	/// </summary>
	/// <param name="v">position</param>
	/// <param name="m">ワールド行列</param>
	/// <returns></returns>
	Vector3 transform(const Vector3& v, const Matrix4& m);

	/// <summary>
	/// ビュー行列作成
	/// </summary>
	/// <param name="eye">視点</param>
	/// <param name="target">注視点</param>
	/// <param name="up">自身を中心にした上方向</param>
	/// <returns></returns>
	Matrix4 ViewMat(Vector3 eye, Vector3 target, Vector3 up);

	/// <summary>
	/// 射影行列作成
	/// </summary>
	/// <param name="fovAngleY">視野角</param>
	/// <param name="aspectRatio">アスペクト比</param>
	/// <param name="nearZ"></param> 近距離限界 
	/// <param name="farZ">遠距離限界</param>
	/// <returns></returns>
	Matrix4 ProjectionMat(float fovAngleY, float aspectRatio, float nearZ, float farZ);

	/// <summary>
	/// ビューポート行列作成
	/// </summary>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="offset">画面範囲オフセット</param>
	/// <returns></returns>
	Matrix4 ViewPortMat(float width, float height, Vector2 offset);

	// 代入演算子オーバーロード
	Matrix4& operator*=(const Matrix4& m1);
	Matrix4 operator*(const Matrix4& m1);

	/// <summary>
	///ラジアンから弧度法への変換
	/// </summary>
	/// <param name="rad">ラジアン</param>
	/// <returns></returns>
	static float ConvertToRadian(float rad);

};

	// 2項演算子オーバーロード
	Vector3 operator*(const Vector3& v, const Matrix4& m);

