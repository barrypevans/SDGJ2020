#include "dance-floor-visual-controller.h"
#include "../core/entity.h"
#include "../core/renderable.h"
#include "../core/time.h"
void DanceFloorVisualController::Update()
{
	Entity* entity = (Entity*)m_entity;
	entity->GetComponent<Renderable>()->userData1 += Time::g_pTime->GetDeltaTime();
}
