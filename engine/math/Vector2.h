/**
 * @file Vector2.cpp
 * @brief 2軸ベクトルクラス
 * @author カネコ_リョウタ
 */

#pragma once
class Vector2
{
public:
	float x; // x成分
	float y; // y成分

public:
	// コンストラクタ
	Vector2(); // 零ベクトルとして生成

	/// <summary>
	///  x成分 , y成分を指定しての生成
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	Vector2(float x, float y); 

	/// <summary>
	/// 距離を求める
	/// </summary>
	/// <returns></returns>
	float length() const;

	/// <summary>
	/// 正規化する
	/// </summary>
	/// <returns></returns>
	Vector2& normalize();

	/// <summary>
	/// 内積を求める
	/// </summary>
	/// <param name="v">掛ける相手のベクトル</param>
	/// <returns></returns>
	float dot(const Vector2& v) const;

	/// <summary>
	/// 外積を求める
	/// </summary>
	/// <param name="v">掛ける相手のベクトル</param>
	/// <returns></returns>
	float cross(const Vector2& v)const;

	// 単項演算子オーバーロード
	Vector2 operator+() const;
	Vector2 operator-() const;

	// 代入演算子オーバーロード
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);

};

// 2項演算子オーバーロード
// ※いろんな引数(引数の型と順序)のパターンに対応するため、以下のように準備してる
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

