#pragma once
#include "GameObject.h"

#define SMALL_BRICK_BBOX_WIDTH  16
#define SMALL_BRICK_BBOX_HEIGHT 16

class CSmallBrick :public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

