/**
 * @file Vector4.cpp
 * @brief 4軸ベクトルクラス
 * @author カネコ_リョウタ
 */

#pragma once

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	//コンストラクタ
	Vector4();								//零ベクトルとする

	/// <summary>
	///  x成分,y成分,z成分 を指定して生成
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="w"></param>
	Vector4(float x, float y, float z, float w);

	/// <summary>
	/// ノルム(長さ)を求める 
	/// </summary>
	/// <returns></returns>
	float length() const;

	/// <summary>
	/// 正規化する
	/// </summary>
	/// <returns></returns>
	Vector4& normalize();

	/// <summary>
	///  内積を求める
	/// </summary>
	/// <param name="v">掛ける相手のベクトル</param>
	/// <returns></returns>
	float dot(const Vector4& v) const;

	/// <summary>
	///  外積を求める
	/// </summary>
	/// <param name="v">掛ける相手のベクトル</param>
	/// <returns></returns>
	Vector4 cross(const Vector4& v) const;


	//単項演算子オーバーロード
	Vector4 operator+() const;
	Vector4 operator-() const;

	//代入演算子オーバーロード
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(float s);
	Vector4& operator/=(float s);

};


//　2項演算子オーバーロード
//　いろいろな引数のパターンに対応(引数の序列)するため、以下のように準備している
const Vector4 operator+(const Vector4& v1, const Vector4& v2);
const Vector4 operator-(const Vector4& v1, const Vector4& v2);
const Vector4 operator*(const Vector4& v, float s);
const Vector4 operator*(float s, const Vector4& v);
const Vector4 operator/(const Vector4& v, float s);