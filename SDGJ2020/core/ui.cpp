#include "ui.h"

UI* UI::g_pUI;


void UI::Init()
{
	InitBar(&pHypebar, &hypebarRenderable, "HypeBar6.png");
	InitBar(&pHypebar2, &hypebarRenderable2, "HypeBar3.png");
	InitBar(&pHypebar3, &hypebarRenderable3, "HypeBar7.png");
	InitBar(&pHypebar4, &hypebarRenderable4, "HypeBar5.png");
	InitBar(&pHypebar5, &hypebarRenderable5, "HypeBar9.png");

	pHypebar2->m_position += glm::vec2(0, 1.5);
	pHypebar3->m_position += glm::vec2(0, 3);
	pHypebar4->m_position += glm::vec2(0, 4.5);
	pHypebar5->m_position += glm::vec2(0, 6);
}


void UI::CleanUp()
{

}

float time;
void UI::Update()
{
	time += Time::g_pTime->GetDeltaTime() * 0.2;

	float t = abs(fmod(time, 3.0f)-1.5f) - 0.25f;
	if (t > 1)
		t = 1;
	else if (t < 0)
		t = 0;

	hypebarRenderable->userData1 = t;
	hypebarRenderable2->userData1 = t;
	hypebarRenderable3->userData1 = t;
	hypebarRenderable4->userData1 = t;
	hypebarRenderable5->userData1 = t;

}

void UI::InitBar(Entity** e, Renderable** r, std::string textureFilename)
{
	*e = Game::g_pGame->CreateEntity();
	*r = (*e)->AddComponent<Renderable>();
	(*r)->isUI = true;
	(*r)->SetTexture("art/" + textureFilename);

	(*e)->m_position = glm::vec2(-4.5, -3.5);
	(*e)->m_scale = glm::vec2(5, 5);
	(*r)->m_layerOrder = 1;
	(*r)->OverrideShader("shaders/stepBarUI.fs");
}
