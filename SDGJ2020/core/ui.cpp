#include "ui.h"

UI* UI::g_pUI;

void UI::Init()
{
	pHypebar = Game::g_pGame->CreateEntity();
	auto hypebarRenderable = pHypebar->AddComponent<Renderable>();
	hypebarRenderable->isUI = true;
	hypebarRenderable->SetTexture("art/HypeBar2.png");
	hypebarRenderable->m_layerOrder = 100;


	pHypebar->m_position = glm::vec2(0, 3);
	pHypebar->m_scale = glm::vec2(5,5);
	hypebarRenderable->m_layerOrder = 1;
	hypebarRenderable->OverrideShader("shaders/test.fs");
}

void UI::CleanUp()
{

}

void UI::Update()
{
	//pHypebar->m_scale += glm::vec2(0.1, 0);
}