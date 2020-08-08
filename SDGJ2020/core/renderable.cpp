#include "renderable.h"
#include <stdio.h>
#include "renderer.h"
#include "entity.h"
#include "asset-manager.h"

void Renderable::SetTexture(std::string texturePath)
{
	m_texture = AssetManager::g_pAssetManager->GetAsset<Texture>(texturePath.c_str());
	
	// scale the sprite to the proper aspect ratio
	if (m_texture)
	{
		Entity* entity = reinterpret_cast<Entity*>(m_entity);
		entity->m_scale = glm::vec2(1, m_texture->m_aspect);
	}
}
void Renderable::Update()
{
	Renderer::g_pRenderer->JoinRenderQueue(this);
}

void Renderable::Init()
{

}
