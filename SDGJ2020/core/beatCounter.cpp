#include "beatCounter.h"
#include "Input.h"
#include "entity.h"
#include "metronome.h"
#include "time.h"

void beatCounter::Init()
{
	beatCount = 0;
}
void beatCounter::Update()
{
	Entity* entity = (Entity*)m_entity;
	// put movement code here
	//get input

	if (Metronome::g_pMetronome->Beat) {
		beatCount++;
		if (beatCount > 3) {
			entity->m_position.x = 2.73;
			beatCount = 0;
		}
		else {
			entity->m_position.x += .725; 
		}
	}
}
void beatCounter::CleanUp()
{
	beatCount = 0;
}
