#include "renderable.h"
#include <stdio.h>
#include "renderer.h"
#include "entity.h"
#include "asset-manager.h"

void Renderable::SetTexture(std::string texturePath)
{
	m_texture = AssetManager::g_pAssetManager->GetAsset<Texture>(texturePath.c_str());
}
void Renderable::Update()
{
	Renderer::g_pRenderer->JoinRenderQueue(this);
}

void Renderable::Init()
{
	m_layerOrder = 0;
}
