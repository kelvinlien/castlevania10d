#include "Brick.h"
#include"Game.h"
void CBrick::Render()
{
	if (CGame::GetInstance()->GetCurrentSceneID() != 5)
		animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (CGame::GetInstance()->GetCurrentSceneID() == 5) {
		l = x;
		t = y;
		r = x + BRICK_INTRO_BBOX_WIDTH;
		b = y + BRICK_INTRO_BBOX_HEIGHT;
	}
	else {
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}