#pragma once
#include "ISystem.h"
#include "entity.h"
#include "game.h"
#include "renderable.h"
#include "time.h"

class UI : public ISystem
{
public:
	static UI* g_pUI;

	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	virtual bool IsHypeBarFull();
	float hypeBarPercent;
	float targetHypeBarPercent;

	int hypeCount = 0;
	int maxHypeCount = 10;
	void CorrectMove();
	void ClearMoveCount();

	void InitBar(Entity** e, Renderable** r, std::string textureFilename);

	Entity* pHypebar;
	Renderable* hypebarRenderable;

	Entity* pHypebarGlow;
	Renderable* hypebarGlowRenderable;

};