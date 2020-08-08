#pragma once
#include "component.h"

class PlayerController : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override;
};