#include "SmallBrick.h"

void CSmallBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CSmallBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + SMALL_BRICK_BBOX_WIDTH;
	b = y + SMALL_BRICK_BBOX_HEIGHT;
}