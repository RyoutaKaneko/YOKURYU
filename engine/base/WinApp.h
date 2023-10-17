/**
 * @file WinApp.cpp
 * @brief Window�����N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp final
{
public: // �ÓI�����o�֐�
	/// <summary>
	/// window����
	/// </summary>
	/// <param name="hwnd"></param>
	/// <param name="msg"></param>
	/// <param name="wparam"></param>
	/// <param name="lparam"></param>
	/// <returns></returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	/// <summary>
	/// WindowsAPI�̏�����
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// hwnd�擾
	/// </summary>
	/// <returns></returns>
	HWND GetHwnd() const { return hwnd; }

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns></returns>
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	/// <summary>
	/// ���b�Z�[�W�̏���
	/// </summary>
	/// <returns></returns>
	bool ProcessMessage();

public:
	static WinApp* GetInstance();

private:
	WinApp() = default;
	~WinApp() = default;
	WinApp(const WinApp&) = delete;
	WinApp& operator=(const WinApp&) = delete;

public: // �萔
	// �E�B���h�E����
	static const int window_width = 1280;
	// �E�B���h�E�c��
	static const int window_height = 720;

private:
	// �E�B���h�E�n���h��
	HWND hwnd = nullptr;
	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wc{};
};