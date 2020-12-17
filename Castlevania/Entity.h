#pragma once
#include "GameObject.h"
class Entity
{
	RECT triggerZone;
	RECT activeZone;
	float start_x;
	float start_y;
	float width;
	float height;
	CGameObject* gameObj;
public:
	Entity();
	Entity(CGameObject* _gameObj, RECT _triggerZone, RECT _activeZone);
	~Entity();
	RECT GetTriggerZone();
	void SetTriggerZone(RECT zone);
	RECT GetActiveZone();
	void SetActiveZone(RECT zone);
	float GetStartX();
	float GetStartY();
	float GetObjectWidth();
	float GetObjectHeight();
};

