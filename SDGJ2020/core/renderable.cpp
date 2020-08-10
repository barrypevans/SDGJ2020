#include "renderable.h"
#include <stdio.h>
#include "renderer.h"
#include "entity.h"
#include "asset-manager.h"

void Renderable::SetTexture(std::string texturePath)
{
	m_texture = AssetManager::g_pAssetManager->GetAsset<Texture>(texturePath.c_str());
}

void Renderable::SetUserTexture(std::string texturePath)
{
	m_userTexture = AssetManager::g_pAssetManager->GetAsset<Texture>(texturePath.c_str());
}
void Renderable::Update()
{
	//Renderer::g_pRenderer->JoinRenderQueue(this);
}

void Renderable::Init()
{
	m_layerOrder = 0;
	shouldOverrideShader = false;
}


void Renderable::OverrideShader(std::string f, std::string v)
{
	shouldOverrideShader = true;
	m_overrideShader = new Shader(f, v);
}

