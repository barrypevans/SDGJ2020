#include "ui.h"

UI* UI::g_pUI;


void UI::Init()
{
	pHypebar = Game::g_pGame->CreateEntity();
	hypebarRenderable = pHypebar->AddComponent<Renderable>();
	hypebarRenderable->isUI = true;
	hypebarRenderable->SetTexture("art/HypeBar2.png");


	pHypebar->m_position = glm::vec2(0, 3);
	pHypebar->m_scale = glm::vec2(5,5);
	hypebarRenderable->m_layerOrder = 1;
	hypebarRenderable->OverrideShader("shaders/stepBarUI.fs");
}

void UI::CleanUp()
{

}

float time;
void UI::Update()
{
	time += Time::g_pTime->GetDeltaTime();

	hypebarRenderable->userData1 = (sin(time)+1)/2;
	//pHypebar->m_scale += glm::vec2(0.1, 0);
}