#include "animation.h"
#include "asset-manager.h"

Animation::Animation(std::string texturePath, unsigned int numFrames) : m_numFrames(numFrames)
{
	m_texture = AssetManager::g_pAssetManager->GetAsset<Texture>(texturePath.c_str());
}
