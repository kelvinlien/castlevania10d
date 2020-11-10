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
	width = 0;
	height = 0;
	start_x = 0;
	start_y = 0;
	gameObj = NULL;
}

Entity::Entity(CGameObject * _gameObj, RECT _triggerZone, RECT _activeZone)
{
	triggerZone = _triggerZone;
	activeZone = _activeZone;
	start_x = gameObj->start_x;
	start_y = gameObj->start_y;
	float l, t, r, b;
	_gameObj->GetBoundingBox(l, t, r, b);
	width = r - l;
	height = t - b;
	gameObj = _gameObj;
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

float Entity::GetStartX()
{
	return start_x;
}

float Entity::GetStartY()
{
	return start_y;
}

float Entity::GetObjectWidth()
{
	return width;
}

float Entity::GetObjectHeight()
{
	return height;
}

