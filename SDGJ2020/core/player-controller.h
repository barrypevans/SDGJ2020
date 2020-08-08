#pragma once
#include "component.h"

class PlayerController : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override;

	int playerPosX;
	int playerPosY;

	double coordX[10][10];
	double coordY[10][10];

};