#pragma once
#include "ISystem.h"
#include "entity.h"
#include "game.h"
#include "renderable.h"
#include "time.h"
#include "glm/glm.hpp"

class Effects : public ISystem
{
public:
	static Effects* g_pEffects;

	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	std::vector<Entity*> glowTiles;
	std::vector<Renderable*> glowTileRenderables;

	void GlowTilesAt(glm::vec2 position);

};