#pragma once
#include "GameObject.h"
class OutroPoint :public CGameObject
{
public:
	OutroPoint() {};
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	~OutroPoint() {};
};