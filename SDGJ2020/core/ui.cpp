#include "ui.h"
#include "glm/glm.hpp"
#include "time.h"
#include "audio.h"

UI* UI::g_pUI;


void UI::Init()
{
	InitBar(&pHypebar, &hypebarRenderable, "HypeBar5.png");

	pHypebarGlow = Game::g_pGame->CreateEntity();
	hypebarGlowRenderable = pHypebarGlow->AddComponent<Renderable>();
	hypebarGlowRenderable->OverrideShader("shaders/growableGlow.fs");
	hypebarGlowRenderable->isUI = true;
	hypebarGlowRenderable->SetTexture("art/HypeBarGlow.png");
	pHypebarGlow->m_position = glm::vec2(-4.5, -2.9);
	pHypebarGlow->m_scale = glm::vec2(3.5, 3.5);
	hypebarGlowRenderable->m_layerOrder = 9;

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

	if (maxHypeCount == hypeCount)
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
}

bool UI::IsHypeBarFull()
{
	if (hypeCount == maxHypeCount)
		return true;
	else
		return false;
}

void UI::InitBar(Entity** e, Renderable** r, std::string textureFilename)
{
	*e = Game::g_pGame->CreateEntity();
	*r = (*e)->AddComponent<Renderable>();
	(*r)->isUI = true;
	(*r)->SetTexture("art/" + textureFilename);

	(*e)->m_position = glm::vec2(-4.5, -2.9);
	(*e)->m_scale = glm::vec2(2.5, 2.5);
	(*r)->m_layerOrder = 10;
	(*r)->OverrideShader("shaders/stepBarUI.fs");
}

void UI::CorrectMove()
{
	if (hypeCount >= maxHypeCount) 
	{
		Audio::g_pAudio->Play((Audio::GameClip)(rand()%15 + 4), .1f);
		hypeCount = 0;
		return;
	}

	hypeCount++;
	targetHypeBarPercent = (float)hypeCount / (float)maxHypeCount;
	printf("%g\n", targetHypeBarPercent);
}

void UI::ClearMoveCount()
{
	hypeCount = 0;
	targetHypeBarPercent = 0;
}
