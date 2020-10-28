#pragma once
#include "GameObject.h"
class Entity
{
	RECT triggerZone;
	RECT activeZone;
	CGameObject* gameObj;
public:
	Entity();
	~Entity();
	RECT GetTriggerZone();
	void SetTriggerZone(RECT zone);
	RECT GetActiveZone();
	void SetActiveZone(RECT zone);
};

