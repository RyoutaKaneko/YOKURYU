/**
 * @file Vector3.cpp
 * @brief 3���x�N�g���N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include <cmath>

class Vector3 {
public:
	float x;//x����
	float y;//y����
	float z;//z����

public:
	//�R���X�g���N�g
	Vector3();                            //�[���x�N�g���Ƃ��Đ���

	/// <summary>
	/// x����,y�������w�肵�Ă̐���
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector3(float x, float y, float z);   

	/// <summary>
	/// �m����(����)�����߂�
	/// </summary>
	/// <returns></returns>
	float length() const;

	/// <summary>
	/// ���K������
	/// </summary>
	/// <returns></returns>
	Vector3& normalize();

	/// <summary>
	/// ���ς����߂�
	/// </summary>
	/// <param name="v">�|����x�N�g��1</param>
	/// <param name="v2">�|����x�N�g��2</param> 
	/// <returns></returns>
	static float dot(const Vector3& v, const Vector3& v2);

	/// <summary>
	/// �O�ς����߂�
	/// </summary> 
	/// <param name="v">�|���鑊��̃x�N�g��</param>
	/// <returns></returns>
	Vector3 cross(const Vector3& v)const;

	/// <summary>
	/// ���`���(1���֐����)
	/// </summary>
	/// <param name="start">�J�n�n�_</param>
	/// <param name="end">�I���n�_</param> 
	/// <param name="t">���ݒn�_</param>
	/// <returns></returns>
	static const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	/// <summary>
	/// ���ʐ��`�⊮
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

	//�b�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};
//2�����Z�q�I�[�o�[���[�h
//�������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector3  operator+(const Vector3& v1, const Vector3& v2);
const Vector3  operator-(const Vector3& v1, const Vector3& v2);
const Vector3  operator*(const Vector3& v, float s);
const Vector3  operator*(float s, const Vector3& v);
const Vector3  operator/(const Vector3& v, float s);


