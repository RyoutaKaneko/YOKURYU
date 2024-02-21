/**
 * @file Vector3.cpp
 * @brief 3軸ベクトルクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include <cmath>

class Vector3 {
public:
	float x;//x成分
	float y;//y成分
	float z;//z成分

public:
	//コンストラクト
	Vector3();                            //ゼロベクトルとして生成

	/// <summary>
	/// x成分,y成分を指定しての生成
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector3(float x, float y, float z);   

	/// <summary>
	/// ノルム(長さ)を求める
	/// </summary>
	/// <returns></returns>
	float length() const;

	/// <summary>
	/// 正規化する
	/// </summary>
	/// <returns></returns>
	Vector3& normalize();

	/// <summary>
	/// 内積を求める
	/// </summary>
	/// <param name="v">掛けるベクトル1</param>
	/// <param name="v2">掛けるベクトル2</param> 
	/// <returns></returns>
	static float dot(const Vector3& v, const Vector3& v2);

	/// <summary>
	/// 外積を求める
	/// </summary> 
	/// <param name="v">掛ける相手のベクトル</param>
	/// <returns></returns>
	Vector3 cross(const Vector3& v)const;

	/// <summary>
	/// 線形補間(1次関数補間)
	/// </summary>
	/// <param name="start">開始地点</param>
	/// <param name="end">終了地点</param> 
	/// <param name="t">現在地点</param>
	/// <returns></returns>
	static const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	/// <summary>
	/// 球面線形補完
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

	//甲項演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;

	//代入演算子オーバーロード
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};
//2項演算子オーバーロード
//※いろんな引数(引数の型と順序)のパターンに対応するため、以下のように準備している
const Vector3  operator+(const Vector3& v1, const Vector3& v2);
const Vector3  operator-(const Vector3& v1, const Vector3& v2);
const Vector3  operator*(const Vector3& v, float s);
const Vector3  operator*(float s, const Vector3& v);
const Vector3  operator/(const Vector3& v, float s);


