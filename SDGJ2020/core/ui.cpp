#include "ui.h"
#include "glm/glm.hpp"
#include "time.h"
#include "audio.h"
#include "game-logic-core.h"
#include "camera.h"
UI* UI::g_pUI;


void UI::Init()
{
	InitBar(&pHypebar, &hypebarRenderable, "HypeBar5isoB.png");

	pHypebarGlow = Game::g_pGame->CreateEntity();
	pHypebarGlow->m_dontDestroyOnReset = true;
	hypebarGlowRenderable = pHypebarGlow->AddComponent<Renderable>();
	hypebarGlowRenderable->OverrideShader("shaders/growableGlow.fs");
	hypebarGlowRenderable->isUI = true;
	hypebarGlowRenderable->SetTexture("art/HypeBarGlowIso.png");
	pHypebarGlow->m_position = hypeBarPosition;
	pHypebarGlow->m_scale = glm::vec2(hypeBarSize, hypeBarSize);
	hypebarGlowRenderable->m_layerOrder = 49;

	m_pScoreRendererEntity = Game::g_pGame->CreateEntity();
	m_pScoreRendererEntity->m_dontDestroyOnReset = true;
	m_pScoreRendererEntity->m_position = glm::vec2(-Camera::g_pCamera->GetWidth() + 1.0f, Camera::g_pCamera->GetHeight() - 1.0f) * 0.5f ;
	m_pScoreRenderer = m_pScoreRendererEntity->AddComponent<NumberRenderer>();
}


void UI::CleanUp()
{

}

float time;
float barMoveSpeed;
float hypeTime;
void UI::Update()
{
	time += Time::g_pTime->GetDeltaTime();

	//float t = abs(fmod(time, 3.0f)-1.5f) - 0.25f;
	//if (t > 1)
	//	t = 1;
	//else if (t < 0)
	//	t = 0;

	if (GameLogic::g_pGameLogic->m_maxHypeCount == GameLogic::g_pGameLogic->m_hypeCount)
	{
			hypeTime += Time::g_pTime->GetDeltaTime() * 3;
		if (hypeTime > 1)
			hypeTime = 1;
	}
	else
	{
			hypeTime -= Time::g_pTime->GetDeltaTime() * 3;
		if (hypeTime < 0)
			hypeTime = 0;
	}


	hypebarGlowRenderable->userData1 = hypeTime * ((sin(time * 4.0f * 3.15159f) + 1) / 2);

	barMoveSpeed = glm::mix(barMoveSpeed, (targetHypeBarPercent - hypeBarPercent) * 0.5f, 0.2f);
	hypeBarPercent += barMoveSpeed;

	hypebarRenderable->userData1 = hypeBarPercent;

	m_pScoreRenderer->SetNumber(GameLogic::g_pGameLogic->m_score);
}

void UI::InitBar(Entity** e, Renderable** r, std::string textureFilename)
{
	*e = Game::g_pGame->CreateEntity();
	*r = (*e)->AddComponent<Renderable>();
	(*r)->isUI = true;
	(*r)->SetTexture("art/" + textureFilename);

	(*e)->m_position = hypeBarPosition;
	(*e)->m_scale = glm::vec2(hypeBarSize, hypeBarSize);
	(*r)->m_layerOrder = 50;
	(*r)->OverrideShader("shaders/stepBarUI.fs");
}

void UI::CorrectMove()
{
	int hypeCount = GameLogic::g_pGameLogic->m_hypeCount;
	targetHypeBarPercent = (float)hypeCount / (float)GameLogic::g_pGameLogic->m_maxHypeCount;
	//printf("%g\n", targetHypeBarPercent);
}


