#pragma once

#include "Vector3.h"
#include <Vector>

class Spline 
{
public:
	//������
	void Initialize();

	//�X�V
	Vector3 Update(std::vector<Vector3>& points,float val);

	Vector3 EnemyPosition(std::vector<Vector3>& points, float val);

	//�X�V
	Vector3 pointCal(std::vector<Vector3>& points);

	void Reset();

	//����_�̏W��(vector�R���e�i)�A��Ԃ����Ԃ̓Y���A���Ԍo�ߗ�
	Vector3 SplinePosition(const std::vector<Vector3>& point, size_t startIndex, float t);

	bool GetIsEnd() { return isEnd; }
	float GetT() { return t + integer; }

private:
	//P1����X�^�[�g����
	size_t startIndex = 1;
	bool isEnd = false;
	float t = 0;
	float integer = 0;


	//���̈ʒu
	Vector3 position;
};