#include "animatable.h"
#include "time.h"
void Animatable::Init()
{
	Renderable::Init();
	OverrideShader("shaders/animated.fs");
	m_tick = 0;
}

void Animatable::Update()
{
	Renderable::Update();
	m_tick += Time::g_pTime->GetDeltaTime();
	if (m_tick > k15FpsBarrier)
	{
		m_tick = 0;
		m_curFrame++;
		if (m_curFrame > m_activeAnimation->m_numFrames-1)
		{
			m_curFrame = 0;
		}
	}
}

void Animatable::AddAnimation(std::string animName, Animation* animation)
{
	Hashcode hash = AssetManager::FnvHash(animName.c_str());
	m_anims.insert(std::pair<Hashcode, Animation*>(hash, animation));
}

void Animatable::SetActiveAnimation(std::string animName)
{
	Hashcode hash = AssetManager::FnvHash(animName.c_str());
	auto it = m_anims.find(hash);
	if (it == m_anims.end())
		return;
	m_activeAnimation = m_anims[hash];
	m_texture = m_activeAnimation->m_texture;
}

int Animatable::GetCurrentFrame()
{
	return m_curFrame;
}
/*
float Animatable::GetAnimOffset()
{
	static float t = 0;
	t += Time::g_pTime->GetDeltaTime();
	return fmod(t,1.0f);
}*/
