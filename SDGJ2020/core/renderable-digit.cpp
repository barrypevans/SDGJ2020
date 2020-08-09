#include "renderable-digit.h"
#include "animation.h"
#include "entity.h"
void RenderableDigit::Update()
{
	Renderable::Update();
}

void RenderableDigit::Init()
{
	Animatable::Init();
	AddAnimation("default", new Animation("art/numbers.png", 10));
	SetActiveAnimation("default");
	isUI = true;
	m_layerOrder = 10000;
	Entity* entity = (Entity*)m_entity;
}

void RenderableDigit::SetDigit(int i)
{
	if (i > 9)
		i = 9;
	if (i < -1)
		i = -1;

	m_curFrame = i;
}
