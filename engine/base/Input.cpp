#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//using namespace Microsoft::WRL;

Input* Input::GetInstance()
{
	static Input instance;

	return &instance;
}

void Input::Initialize(WinApp* winApp)
{
	// �؂�Ă���WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;

	HRESULT result;

	// DirectInput�̃C���X�^���X����
	/*ComPtr<IDirectInput8> directInput = nullptr;*/
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// �L�[�{�[�h�f�o�C�X�̐���
	//ComPtr<IDirectInputDevice8> keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

	//�}�E�X�f�o�C�X�̃Z�b�g
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = mouse->SetDataFormat(&c_dfDIMouse); // �W���`��
	assert(SUCCEEDED(result));
	
	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	assert(SUCCEEDED(result));

	//�f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	result = mouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	assert(SUCCEEDED(result));
	//�}�E�X�J�[�\�����B��
	ShowCursor(FALSE);
}

void Input::Update()
{
	HRESULT result;

	// �O��̃L�[���͂�ێ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�{�[�h���̎擾�J�n
	result = keyboard->Acquire();

	// �S�L�[�̓��͏�Ԃ��擾����
	/*BYTE key[256] = {};*/
	result = keyboard->GetDeviceState(sizeof(key), key);

	//�}�E�X����J�n
	memcpy(&mouseState_bak, &mouseState, sizeof(mouseState_bak));
	mouse->Acquire();

	result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);
}

//�}�E�X��
bool Input::PushMouseLeft()
{
	if (mouseState.rgbButtons[0] != 0) {
		return true;
	}
	return false;
}

bool Input::TriggerMouseLeft()
{
	if (mouseState.rgbButtons[0] > 0 && mouseState_bak.rgbButtons[0] == 0) {
		return true;
	}
	return false;
}

bool Input::PushMouseRight()
{
	if (mouseState.rgbButtons[1] > 0) {
		return true;
	}
	return false;
}

bool Input::TriggerMouseRight()
{
	if (mouseState.rgbButtons[1] > 0 && mouseState_bak.rgbButtons[1] == 0) {
		return true;
	}
	return false;
}

Vector3 Input::GetMousePos()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(winApp->GetHwnd(), &p);

	//z������0�ŕԂ�
	return Vector3((float)p.x,(float)p.y,0.0f);
}

Vector3 Input::GetMouseVelo()
{
	return Vector3((float)mouseState.lX - mouseState_bak.lX,(float)mouseState.lY - mouseState_bak.lY,0);
}

void Input::SetMousePos(Vector2 pos)
{
	POINT p{ (long)pos.x,(long)pos.y };
	SetCursorPos(p.x,p.y);
}

bool Input::PushKey(BYTE keyNumber) 
{
	// �w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	// �����ł͂Ȃ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber] && keyPre[keyNumber] == false) {
		return true;
	}
	
	return false;
}

bool Input::AnyKey()
{
	for (int i = 0; i < sizeof(key); i++) {
		if (key[i] && keyPre[i] == false) {
			return true;
		}
	}

	return false;
}
