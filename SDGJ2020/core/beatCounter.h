#pragma once
#include "component.h"
#include "entity.h"
class beatCounter : public Component
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void CleanUp() override;
	int beatCount;
public:
	int getBeatCount() {
		return this->beatCount;
	}
};

