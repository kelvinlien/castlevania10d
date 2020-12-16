#pragma once
#include "GameObject.h"

class CWaterSurface :public CGameObject
{
	int width, height;
public:
	CWaterSurface(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

