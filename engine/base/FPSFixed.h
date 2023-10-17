/**
 * @file FpsFixed.cpp
 * @brief �Q�[����fps������Ǘ�����N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include <chrono>
#include <thread>

class FPSFixed 
{
public: // �����o�֐�
	/// <summary>
	///  FPS�Œ菉����
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS�Œ�X�V
	/// </summary>
	void UpdateFixFPS();

	// �L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference_;
};