/**
 * @brief �v���W�F�N�g���C��cpp
 * @author �J�l�R_�����E�^
 */

#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SIFrameWork* game = new Game();

	game->Run();

	delete game;

	return 0;
}