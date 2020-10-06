#include "Whip.h"

/*CFirePot::CFirePot()
{
	SetState(FIREPOT_STATE_IDLE);
}*/

CWhip::CWhip()
{
	SetWeaponType(0);
	level = 1;
}

void CWhip::SetState(int state)
{
	CGameObject::SetState(state);
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (level == 1 || level == 2)
		if (animation_set->at(WHIP_ANI_LV1_LEFT)->GetCurrentFrame() == 2 || animation_set->at(WHIP_ANI_LV2_LEFT)->GetCurrentFrame() == 2 || animation_set->at(WHIP_ANI_LV1_RIGHT)->GetCurrentFrame() == 2 || animation_set->at(WHIP_ANI_LV2_RIGHT)->GetCurrentFrame() == 2)
		{
			right = x + WHIP_BBOX_SHORT_WIDTH;
			bottom = y + WHIP_BBOX_SHORT_HEIGHT;
		}
	else
		if (animation_set->at(WHIP_ANI_LV3_LEFT)->GetCurrentFrame() == 2 || animation_set->at(WHIP_ANI_LV3_RIGHT)->GetCurrentFrame() == 2)
		{
			right = x + WHIP_BBOX_LONG_WIDTH;
			bottom = y + WHIP_BBOX_LONG_HEIGHT;
		}
}

void CWhip::Render()
{
	int ani = WHIP_ANI_LV1_LEFT;
	if (state == WHIP_STATE_LV2_LEFT)
		ani = WHIP_ANI_LV2_LEFT;
	if (state == WHIP_STATE_LV3_LEFT)
		ani = WHIP_ANI_LV3_LEFT;
	if (state == WHIP_STATE_LV1_RIGHT)
		ani = WHIP_ANI_LV1_RIGHT;
	if (state == WHIP_STATE_LV2_RIGHT)
		ani = WHIP_ANI_LV2_RIGHT;
	if(state == WHIP_STATE_LV3_RIGHT)
		ani = WHIP_ANI_LV3_RIGHT;
	animation_set->at(ani)->Render(x, y);
}