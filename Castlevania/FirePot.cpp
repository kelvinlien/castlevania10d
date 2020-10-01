#include "FirePot.h"
CFirePot::CFirePot(float x, float y)
{
	//SetState(FIREPOT_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CFirePot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIREPOT_BBOX_WIDTH;

	if (state == FIREPOT_STATE_IDLE)
		bottom = y + FIREPOT_BBOX_HEIGHT;
}

void CFirePot::Render()
{
	int ani = FIREPOT_ANI_IDLE;
	/*if (state == FIREPOT_STATE_DIE) {
		ani = FIREPOT_ANI_DIE;
	}*/

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}