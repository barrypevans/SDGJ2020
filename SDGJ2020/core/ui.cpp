#include "ui.h"

UI* UI::g_pUI;

void UI::Init()
{
	pHypebar = Game::g_pGame->CreateEntity();
	auto hyperbarRenderable = pHypebar->AddComponent<Renderable>();
	hyperbarRenderable->isUI = true;
	hyperbarRenderable->SetTexture("art/BerryBarry.png");

	pHypebar->m_position = glm::vec2(0, 3);
	pHypebar->m_scale = glm::vec2(6, 1);

}

void UI::CleanUp()
{

}

void UI::Update()
{
	pHypebar->m_scale += glm::vec2(0.1, 0);
}