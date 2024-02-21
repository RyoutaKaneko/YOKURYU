/**
 * @file Vector3.h
 * @brief 3軸ベクトルクラス
 * @author カネコ_リョウタ
 */

#include "Vector3.h"

Vector3::Vector3()
	:x(0), y(0), z(0)
{
}
Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}
float Vector3::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return*this /= len;
	}
	return*this;
}
float Vector3::dot(const Vector3& v, const Vector3& v2)
{
	return v.x * v2.x + v.y * v2.y + v.z * v2.z;
}
Vector3 Vector3::cross(const Vector3& v)const
{
	Vector3 temp;
	temp.x = this->y * v.z - this->z * v.y;
	temp.y = this->z * v.x - this->x * v.z;
	temp.z = this->x * v.y - this->y * v.x;
	return temp;
}

const Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t) + end * t;
}

Vector3 Vector3::Slerp(const Vector3& v1, const Vector3& v2, float t)
{
	//内積を求める
	float dot = Vector3::dot(v1, v2);
	//1.0fを超えないように補正を掛ける
	dot = std::min(1.0f,t);
	//アークコサインでΘの角度を求める
	float theta = std::acos(dot);
	//Θの角度からsinΘの角度を求める
	float sinTheta = std::sin(theta);
	//サイン(1-t)を求める						 
	float sinThetaFrom = std::sin((1 - t) * theta);
	//サインΘtを求める
	float sinThetaTo = std::sin(t * theta);
	//球面線形補完したベクトル							  
	Vector3 normCompVec = sinThetaFrom / sinTheta * v1 + sinThetaTo / sinTheta * v2;
	//ゼロ除算を防ぐ
	if (sinTheta < 1.0e-5) {
		normCompVec = v1;
	}
	else {
		//球面線形補完したベクトル
		normCompVec = (sinThetaFrom * v1 + sinThetaTo * v2) / sinTheta;
	}
	//補完ベクトルの長さを求める
	float length1 = v1.length();
	float length2 = v2.length();
	//lerpで補完ベクトルの長さを求める
	float length = length1 * (1.0f - t) + length2 * t;

	//長さを反映
	return length * normCompVec;
}

Vector3 Vector3::operator+()const
{
	return *this;
}
Vector3 Vector3::operator-()const
{
	return Vector3(-x, -y, -z);
}
Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}
// Vector3 クラスに属さない関数群
// 二項演算子
const Vector3 operator+ (const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}
const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}
const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}
const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}
const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

