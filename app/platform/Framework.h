#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Object3d.h"
#include "GameScene.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include"WinApp.h"
#include"DirectXCommon.h"

#include<windows.h>
#include<cassert>
#include<vector>
#include<string>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<dinput.h>
#pragma warning(push)
#pragma warning(disable:26813)
#include<DirectXTex.h>
#pragma warning(pop)
#include "PostEffect.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

class Framework
{

public:
	// ���s
	void Run();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// �X�V
	void Draw();

	// �I��
	void Finalize();

public:
	//�@�I���`�F�b�N
	bool IsEndRequest() { return endRequest_; }

protected:
	WinApp* winApp = nullptr;
	DirectXCommon* dXCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon spriteCommon;
	GameScene* gameScene = nullptr;
	PostEffect postEffect;
	ParticleManager* particleManager = nullptr;

private:
	// �Q�[���I���t���O
	bool endRequest_ = false;
};
