#include "Whip.h"

/*CFirePot::CFirePot()
{
	SetState(FIREPOT_STATE_IDLE);
}*/

CWhip::CWhip(float x, float y) : CGameObject()
{
	//SetState(FIREPOT_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	switch (state)
	{
	case WHIP_STATE_LV1:
		if()
	default:
		break;
	}
}

void CWhip::Render()
{
	int ani = WHIP_ANI_IDLE;
	/*if (state == FIREPOT_STATE_DIE) {
		ani = FIREPOT_ANI_DIE;
	}*/

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();