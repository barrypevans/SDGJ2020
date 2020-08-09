#include "animatable.h"
#include "time.h"
void Animatable::Init()
{
	OverrideShader("shaders/animated.fs");
}

float Animatable::GetAnimOffset()
{
	static float t = 0;
	t += Time::g_pTime->GetDeltaTime();
	return fmod(t,1.0f);
}
