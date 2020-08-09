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
	((Entity*)m_entity)->GetComponent<Animatable>()->SetActiveAnimation("pose");
	m_poseCoolDown = 1.0f;
	m_posing = true;
}
