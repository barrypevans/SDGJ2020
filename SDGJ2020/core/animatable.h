#pragma once
#include "renderable.h"
#include <string>
#include "animation.h"
#include "asset-manager.h"

class Animatable : public Renderable
{
public:
	virtual void Init() override;
	virtual void Update() override;

	void AddAnimation(std::string animName, Animation* animation);
	void SetActiveAnimation(std::string animName);
	int GetCurrentFrame();
	Animation* GetActiveAnimation() { return m_activeAnimation; }
protected:
	Animation* m_activeAnimation;
	std::map<Hashcode, Animation*> m_anims;
	int m_curFrame;
	float m_tick;
	const float k15FpsBarrier = 1.0f / 15.0f;
};