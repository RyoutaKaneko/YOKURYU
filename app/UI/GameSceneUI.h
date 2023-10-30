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

	/// <summary>
	/// HP�t���[���̍��W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetHPFramePos() { return hpFrame.GetPosition(); }

	/// <summary>
	/// ���ߗ��Z�b�g
	/// </summary>
	/// <param name="isCollision"></param>
	void SetHPAlpha(bool isCollision);

	/// <summary>
	///  ���Z�b�g����UI�̍��W�ݒ�
	/// </summary>
	void ResetUIPos();

	/// <summary>
	/// ���o�X�L�b�v����UI�̍��W�ݒ�
	/// </summary>
	void SkipUIPos();

	/// <summary>
	/// ���S��UI���W
	/// </summary>
	void DeadUIPos();

	/// <summary>
	/// �R���e�B�j���[�e�L�X�g�X�V
	/// </summary>
	void ContinueText();

	/// <summary>
	/// �R���e�B�j���[�`��
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cmdList"></param>
	void DrawContinue(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �R���e�B�j���[�t���Ogetter
	/// </summary>
	/// <returns></returns>
	bool GetIsContinue() { return isContinue; }

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
	Sprite continueTextbox;
	Sprite continueYes;
	Sprite continueNo;
	Sprite continueText;
	bool isPlayable;
	float frameAlpha;
	float barAlpha;
	bool isContinue;
	bool isShowContinue;
};

