/**
 * @file Game.cpp
 * @brief �V�[�������N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "SIFrameWork.h"

// �Q�[���S��
class Game : public SIFrameWork
{
public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;
};
