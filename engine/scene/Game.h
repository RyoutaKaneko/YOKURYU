#pragma once

#include "SIFrameWork.h"

// �Q�[���S��
class Game : public SIFrameWork
{
public: // �����o�֐�
	// ������
	void Initialize() override;

	// �I��
	void Finalize() override;

	// ���t���[���X�V
	void Update() override;

	// �`��
	void Draw() override;
};
