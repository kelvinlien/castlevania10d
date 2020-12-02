#pragma once
#include "GameObject.h"
#define VERTICAL_TRIGGER_DISTANCE 500
class Entity
{
	RECT triggerZone;
	float start_x;
	float start_y;
	float width;
	float height;
	CGameObject* gameObj;
public:
	Entity();
	Entity(CGameObject * _gameObj, float triggerDistance);
	~Entity();
	RECT GetTriggerZone();
	void SetTriggerZone(RECT zone);
	void GetTriggerZone(float &l, float &t, float &r, float &b);
	float GetStartX();
	float GetStartY();
	float GetObjectWidth();
	float GetObjectHeight();
	void SetGameObject(CGameObject* _gameObj);
	CGameObject* GetGameObject();
};

