#include "Whip.h"

/*CFirePot::CFirePot()
{
	SetState(FIREPOT_STATE_IDLE);
}*/

CWhip::CWhip()
{
	SetWeaponType(0);
	level = WHIP_STATE_LV1;
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	
	if (level == WHIP_STATE_LV1)
	{
	
	}
}

void CWhip::Render()
{
	int ani = WHIP_ANI_LV1;
	if (state == WHIP_STATE_LV2)
		ani = WHIP_ANI_LV2;
	if(state == WHIP_STATE_LV3)
		ani = WHIP_ANI_LV3;

	animation_set->at(ani)->Render(x, y);
}