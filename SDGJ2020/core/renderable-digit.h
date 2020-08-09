#pragma once
#include "animatable.h"

class RenderableDigit : public Animatable
{
public:
	virtual void Update() override;
	virtual void Init() override;

	void SetDigit(int i);
};