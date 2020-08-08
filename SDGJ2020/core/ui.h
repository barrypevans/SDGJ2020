#pragma once
#include "ISystem.h"
#include "entity.h"
#include "game.h"
#include "renderable.h"

class UI : public ISystem
{
public:
	static UI* g_pUI;

	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	Entity* pHypebar;
	float hypeBarPercent;

};