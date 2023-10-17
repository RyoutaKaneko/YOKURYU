/**
 * @file Matrix4.cpp
 * @brief 4x4�s��N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Vector3.h"
#include "Vector2.h"

class Matrix4
{
public:

	// Matrix4 �\����
	float m[4][4];


	// �R���X�g���N�^
	Matrix4();
	// �������w�肵�Ă̐���
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// <summary>
	/// �P�ʍs������߂�
	/// </summary>
	/// <returns></returns>
	static Matrix4 identity();

	/// <summary>
	/// �t�s������߂�
	/// </summary>
	/// <returns></returns>
	Matrix4 MakeInverse();

	/// <summary>
	/// �g��k���s��̐ݒ�
	/// </summary>
	/// <param name="s">�X�P�[��</param>
	/// <returns></returns>
	Matrix4 scale(const Vector3& s);

	/// <summary>
	/// // ��]�s��̐ݒ�
	/// </summary>
	/// <param name="angle">���W�A���ŉ�]��</param>
	/// <returns></returns>
	Matrix4 rotateX(float angle);
	Matrix4 rotateY(float angle);
	Matrix4 rotateZ(float angle);

	/// <summary>
	/// ���s�ړ��s��̍쐬
	/// </summary>
	/// <param name="t">�ړ���</param>
	/// <returns></returns>
	Matrix4 translate(const Vector3& t);

	/// <summary>
	/// ���W�ϊ��i�x�N�g���ƍs��̊|���Z������j
	/// </summary>
	/// <param name="v">position</param>
	/// <param name="m">���[���h�s��</param>
	/// <returns></returns>
	Vector3 transform(const Vector3& v, const Matrix4& m);

	/// <summary>
	/// �r���[�s��쐬
	/// </summary>
	/// <param name="eye">���_</param>
	/// <param name="target">�����_</param>
	/// <param name="up">���g�𒆐S�ɂ��������</param>
	/// <returns></returns>
	Matrix4 ViewMat(Vector3 eye, Vector3 target, Vector3 up);

	/// <summary>
	/// �ˉe�s��쐬
	/// </summary>
	/// <param name="fovAngleY">����p</param>
	/// <param name="aspectRatio">�A�X�y�N�g��</param>
	/// <param name="nearZ"></param> �ߋ������E 
	/// <param name="farZ">���������E</param>
	/// <returns></returns>
	Matrix4 ProjectionMat(float fovAngleY, float aspectRatio, float nearZ, float farZ);

	/// <summary>
	/// �r���[�|�[�g�s��쐬
	/// </summary>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	/// <param name="offset">��ʔ͈̓I�t�Z�b�g</param>
	/// <returns></returns>
	Matrix4 ViewPortMat(float width, float height, Vector2 offset);

	// ������Z�q�I�[�o�[���[�h
	Matrix4& operator*=(const Matrix4& m1);
	Matrix4 operator*(const Matrix4& m1);

	/// <summary>
	///���W�A������ʓx�@�ւ̕ϊ�
	/// </summary>
	/// <param name="rad">���W�A��</param>
	/// <returns></returns>
	static float ConvertToRadian(float rad);

};

	// 2�����Z�q�I�[�o�[���[�h
	Vector3 operator*(const Vector3& v, const Matrix4& m);

