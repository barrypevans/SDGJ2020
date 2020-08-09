#include "number-renderer.h"
#include "game.h"

void NumberRenderer::Init()
{
	for (int i = 0; i < 10; i++)
	{
		Entity* digitEntity = Game::g_pGame->CreateEntity();
		auto renderableDigit = digitEntity->AddComponent<RenderableDigit>();
		renderableDigit->SetDigit(-1);
		m_digits.push_back(renderableDigit);
		digitEntity->m_scale = glm::vec2(kDigitSize, kDigitSize);
		digitEntity->m_position = ((Entity*)m_entity)->m_position + glm::vec2((float)i * kDigitSize,0);
	}
}

void NumberRenderer::SetNumber(int value)
{
	for (int i = 0; i < 10; i++)
		m_digits[i]->SetDigit(-1);

	char valString[10];
	memset(valString, 0, 10);
	sprintf_s(valString, "%d", value);

	char* character = valString;
	int index = 0;
	while (index < 10)
	{
		m_digits[index]->SetDigit(*character - 48);
		character++;
		index++;
	}
}
