#include "player-anim-controller.h"
#include "../core/entity.h"
#include "../core/animatable.h"
#include "../core/time.h"
void PlayerAnimController::Init()
{
	m_poseCoolDown = 0;
}

void PlayerAnimController::Update()
{
	if (m_posing)
	{
		m_poseCoolDown -= Time::g_pTime->GetDeltaTime();
		if (m_poseCoolDown <= 0)
		{
			((Entity*)m_entity)->GetComponent<Animatable>()->SetActiveAnimation("idle");
			m_posing = false;
		}
	}
}

void PlayerAnimController::Pose()
{
	int poseIndex = rand() % 4;
	char posName[128];
	sprintf_s(posName, "pose_%d", poseIndex + 1);
	((Entity*)m_entity)->GetComponent<Animatable>()->SetActiveAnimation(posName);
	m_poseCoolDown = 1.0f;
	m_posing = true;
}
