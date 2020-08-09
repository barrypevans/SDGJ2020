#pragma once
#include "renderable.h"

class Animatable : public Renderable
{
public:
	virtual void Init() override;

	float GetAnimOffset();
};