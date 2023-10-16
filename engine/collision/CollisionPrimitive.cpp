/**
 * @file CollisionPrimitive.h
 * @brief �����蔻��̃v���~�e�B�u���܂Ƃ߂��N���X
 * @author �J�l�R_�����E�^
 */

#include "CollisionPrimitive.h"

void Triangle::ComputeNormal()
{
	Vector3 p0_p1 = p1 - p0;
	Vector3 p0_p2 = p2 - p0;
	Vector3 V;

	// �O�ςɂ��A�Q�ӂɐ����ȃx�N�g�����Z�o����
	normal = p0_p1.cross(p0_p2);
	normal.normalize();
}