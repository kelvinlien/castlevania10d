#pragma once
#include "GameObject.h"
class OutroBat :public CGameObject
{
public:
	OutroBat() {};
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	~OutroBat() {};
};