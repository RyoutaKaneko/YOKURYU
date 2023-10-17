/**
 * @file Vector4.cpp
 * @brief 4���x�N�g���N���X
 * @author �J�l�R_�����E�^
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
	//�R���X�g���N�^
	Vector4();								//��x�N�g���Ƃ���

	/// <summary>
	///  x����,y����,z���� ���w�肵�Đ���
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="w"></param>
	Vector4(float x, float y, float z, float w);

	/// <summary>
	/// �m����(����)�����߂� 
	/// </summary>
	/// <returns></returns>
	float length() const;

	/// <summary>
	/// ���K������
	/// </summary>
	/// <returns></returns>
	Vector4& normalize();

	/// <summary>
	///  ���ς����߂�
	/// </summary>
	/// <param name="v">�|���鑊��̃x�N�g��</param>
	/// <returns></returns>
	float dot(const Vector4& v) const;

	/// <summary>
	///  �O�ς����߂�
	/// </summary>
	/// <param name="v">�|���鑊��̃x�N�g��</param>
	/// <returns></returns>
	Vector4 cross(const Vector4& v) const;


	//�P�����Z�q�I�[�o�[���[�h
	Vector4 operator+() const;
	Vector4 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(float s);
	Vector4& operator/=(float s);

};


//�@2�����Z�q�I�[�o�[���[�h
//�@���낢��Ȉ����̃p�^�[���ɑΉ�(�����̏���)���邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector4 operator+(const Vector4& v1, const Vector4& v2);
const Vector4 operator-(const Vector4& v1, const Vector4& v2);
const Vector4 operator*(const Vector4& v, float s);
const Vector4 operator*(float s, const Vector4& v);
const Vector4 operator/(const Vector4& v, float s);