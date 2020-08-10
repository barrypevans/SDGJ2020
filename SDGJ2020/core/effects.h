#pragma once
#include "ISystem.h"
#include "entity.h"
#include "game.h"
#include "renderable.h"
#include "time.h"
#include "glm/glm.hpp"
#include "game-logic-core.h"

class Effects : public ISystem
{
public:
	static Effects* g_pEffects;

	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	std::vector<Entity*> glowTiles;

	void GlowTilesAt(int x, int y);

};