/**
 * @file Vector2.cpp
 * @brief 2���x�N�g���N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
class Vector2
{
public:
	float x; // x����
	float y; // y����

public:
	// �R���X�g���N�^
	Vector2(); // ��x�N�g���Ƃ��Đ���

	/// <summary>
	///  x���� , y�������w�肵�Ă̐���
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	Vector2(float x, float y); 

	/// <summary>
	/// ���������߂�
	/// </summary>
	/// <returns></returns>
	float length() const;

	/// <summary>
	/// ���K������
	/// </summary>
	/// <returns></returns>
	Vector2& normalize();

	/// <summary>
	/// ���ς����߂�
	/// </summary>
	/// <param name="v">�|���鑊��̃x�N�g��</param>
	/// <returns></returns>
	float dot(const Vector2& v) const;

	/// <summary>
	/// �O�ς����߂�
	/// </summary>
	/// <param name="v">�|���鑊��̃x�N�g��</param>
	/// <returns></returns>
	float cross(const Vector2& v)const;

	// �P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);

};

// 2�����Z�q�I�[�o�[���[�h
// �������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă�
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

