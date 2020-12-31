#include "Brick.h"
#include "Simon.h"

void CBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//if (!Simon::GetInstance()->IsOnStair())
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}