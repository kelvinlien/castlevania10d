#include "Entity.h"

Entity::Entity()
{
	triggerZone.left = 0;
	triggerZone.top = 0;
	triggerZone.right = 0;
	triggerZone.bottom = 0;
	width = 0;
	height = 0;
	start_x = 0;
	start_y = 0;
	gameObj = NULL;
}

Entity::Entity(CGameObject * _gameObj, float xTriggerDistance)
{
	gameObj = _gameObj;
	start_x = gameObj->start_x;
	start_y = gameObj->start_y;
	float l, t, r, b;
	gameObj->GetBoundingBox(l, t, r, b);
	width = r - l;
	height = b  - t;
	if (xTriggerDistance < width / 2)
	{
		xTriggerDistance = width / 2;
	}
	float xCentralPoint = l + width / 2;
	float yCentralPoint = t + height / 2;
	triggerZone.top = yCentralPoint - VERTICAL_TRIGGER_DISTANCE;
	triggerZone.bottom = yCentralPoint + VERTICAL_TRIGGER_DISTANCE;
	triggerZone.left = xCentralPoint - xTriggerDistance;
	triggerZone.right = xCentralPoint + xTriggerDistance;
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

void Entity::GetTriggerZone(float & l, float & t, float & r, float & b)
{
	l = triggerZone.left;
	t = triggerZone.top;
	r = triggerZone.right;
	b = triggerZone.bottom;
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

void Entity::SetGameObject(CGameObject * _gameObj)
{
	gameObj = _gameObj;
}

CGameObject * Entity::GetGameObject()
{
	return gameObj;
}

