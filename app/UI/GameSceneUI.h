#include "Sprite.h"
#include "Player.h"


#pragma once
class GameSceneUI
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// UI�\���J�n
	/// </summary>
	/// <param name="device"></param>
	/// <param name="time">�Q�[���^�C��</param>
	void ShowUI();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="device"></param>
	void Update(bool isPlayable_, Player* player);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="device"></param>
	void Draw(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

private:
	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite hp;
	Sprite bossHP;
	Sprite gage;
	Sprite gageBack;
	Sprite hpBack;
	Sprite hpFrame;
	Sprite attackUI;
	Sprite attackIcon;
	Sprite lockUI;
	Sprite lockIcon;
	bool isPlayable;
};

