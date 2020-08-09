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

	float hypeBarPercent;


	void InitBar(Entity** e, Renderable** r, std::string textureFilename);

	Entity* pHypebar;
	Renderable* hypebarRenderable;

	Entity* pHypebar2;
	Renderable* hypebarRenderable2;

	Entity* pHypebar3;
	Renderable* hypebarRenderable3;

	Entity* pHypebar4;
	Renderable* hypebarRenderable4;

};