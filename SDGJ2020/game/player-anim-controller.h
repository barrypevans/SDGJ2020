#pragma once
#include "../core/component.h"

class PlayerAnimController : public Component
{
public:
	virtual void Init() override;
	virtual void Update() override;
	void Pose();
	float m_poseCoolDown;

private:
	bool m_posing;
};