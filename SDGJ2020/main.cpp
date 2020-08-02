#pragma once
#include "core/game.h"

int main()
{
	Game* pGame = new Game();
	pGame->Init();

	while (pGame->IsRunning())
	{
		pGame->Update();
	}

	pGame->CleanUp();
	return 0;
}