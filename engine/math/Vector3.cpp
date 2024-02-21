/**
 * @file Vector3.h
 * @brief 3���x�N�g���N���X
 * @author �J�l�R_�����E�^
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
	//���ς����߂�
	float dot = Vector3::dot(v1, v2);
	//1.0f�𒴂��Ȃ��悤�ɕ␳���|����
	dot = std::min(1.0f,t);
	//�A�[�N�R�T�C���Ń��̊p�x�����߂�
	float theta = std::acos(dot);
	//���̊p�x����sin���̊p�x�����߂�
	float sinTheta = std::sin(theta);
	//�T�C��(1-t)�����߂�						 
	float sinThetaFrom = std::sin((1 - t) * theta);
	//�T�C����t�����߂�
	float sinThetaTo = std::sin(t * theta);
	//���ʐ��`�⊮�����x�N�g��							  
	Vector3 normCompVec = sinThetaFrom / sinTheta * v1 + sinThetaTo / sinTheta * v2;
	//�[�����Z��h��
	if (sinTheta < 1.0e-5) {
		normCompVec = v1;
	}
	else {
		//���ʐ��`�⊮�����x�N�g��
		normCompVec = (sinThetaFrom * v1 + sinThetaTo * v2) / sinTheta;
	}
	//�⊮�x�N�g���̒��������߂�
	float length1 = v1.length();
	float length2 = v2.length();
	//lerp�ŕ⊮�x�N�g���̒��������߂�
	float length = length1 * (1.0f - t) + length2 * t;

	//�����𔽉f
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
// Vector3 �N���X�ɑ����Ȃ��֐��Q
// �񍀉��Z�q
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

