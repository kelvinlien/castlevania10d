#include "Entity.h"

Entity::Entity()
{
	triggerZone.left = 0;
	triggerZone.top = 0;
	triggerZone.right = 0;
	triggerZone.bottom = 0;
	activeZone.left = 0;
	activeZone.top = 0;
	activeZone.right = 0;
	activeZone.bottom = 0;
	gameObj = NULL;
}

Entity::~Entity()
{
	delete gameObj;
}

RECT Entity::GetTriggerZone()
{
	return triggerZone;
}

void Entity::SetTriggerZone(RECT zone)
{
	triggerZone = zone;
}

RECT Entity::GetActiveZone()
{
	return activeZone;
}

void Entity::SetActiveZone(RECT zone)
{
	activeZone = zone;
}
