#include "renderable.h"
#include <stdio.h>
#include "renderer.h"

void Renderable::Update()
{
	Renderer::g_pRenderer->JoinRenderQueue(this);
}
