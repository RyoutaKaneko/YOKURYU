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
	/// �N���A��ʕ`��
	/// </summary>
	/// <param name="device"></param>
	/// <param name="cmdList"></param>
	void DrawClear(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �R���e�B�j���[�t���Ogetter
	/// </summary>
	/// <returns></returns>
	bool GetIsContinue() { return isContinue; }

	/// <summary>
	/// �J�[�\���A�b�v�f�[�g
	/// </summary>
	void CursorUpdate(bool isCont);
	
	/// <summary>
	/// �Q�[���V�[�����Z�b�ggetter
	/// </summary>
	/// <returns></returns>
	bool GetIsGameSceneReset() { return isGameSceneReset; }

	/// <summary>
	// �Q�[���V�[���I�[�o�[getter
	/// </summary>
	/// <returns></returns>
	bool GetIsGameOver() { return isGameOver; }

	/// <summary>
	/// �N���AUI�X�V
	/// </summary>
	void ClearUpdate();

	/// <summary>
	/// �Q�[���I��
	/// </summary>
	void EndText();

	/// <summary>
	/// �Q�[���I���e�L�X�g�`��
	/// </summary>
	void DrawEnd(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	//�|�[�Y���
	void PauseText();

	/// <summary>
    /// �|�[�Y��ʃe�L�X�g�`��
    /// </summary>
	void DrawPause(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �e�L�X�g�Ƃ���
	/// </summary>
	void CloseText();

	/// <summary>
	/// 
	/// </summary>
	bool GetIsClose() { return isClose; }

private:
	//�萔
	static const int CURSOR_MAX = 9;
	static const int ALPHA_MAX = 1;
	static const Vector2 SELECT_CONTINUE_SCALE;
	static const Vector2 SELECT_PAUSE_SCALE;

	//�X�v���C�g�̃|�C���^
	Sprite* sprite = new Sprite;
	SpriteCommon spriteCommon_;
	Sprite hp;
	Sprite bossHP;
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
	Sprite cursorGH[CURSOR_MAX];
	Sprite circle;
	Sprite contSelect;
	Sprite congrat;
	Sprite clearNext;
	Sprite congratBack;
	Sprite end;
	Sprite goTitle;
	Sprite goReset;
	Sprite pause;
	Sprite pauseBack;
	Sprite esc;
	Sprite escClose;
	bool isPlayable;
	float frameAlpha;
	float barAlpha;
	bool isContinue;
	bool isShowContinue;
	float circleSize;
	float clickEffectAlpha;
	float circleAlpha;
	Vector3 cursorPos;
	Vector3 cursorPosBak;
	bool isGameSceneReset;
	bool isGameOver;
	float congratAlpha;
	bool isClose;
};

