#include "Whip.h"
#include"Simon.h"
CWhip* CWhip::__instance = NULL;

CWhip* CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}
CWhip::CWhip() :CWeapon()
{
	level = 1;
	animation_set = CAnimationSets::GetInstance()->Get(5);
	//available = true;
}
void CWhip::Update(DWORD dt, vector< LPGAMEOBJECT>*coObjects)
{
	if (nx > 0)
		SetPosition((Simon::GetInstance()->x - 20), Simon::GetInstance()->y);
	else if (nx < 0)
		SetPosition((Simon::GetInstance()->x - 80), Simon::GetInstance()->y);

}


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == 1 || level == 2) {
		if (animation_set->at(WHIP_ANI_LV1_RIGHT)->GetCurrentFrame() == 2 && Simon::GetInstance()->GetDirect() > 0)
		{
			left = Simon::GetInstance()->x + 60;
			top = Simon::GetInstance()->y + 20;
			right = left + 50;
			bottom = top + 15;
		}
		else if (animation_set->at(WHIP_ANI_LV1_LEFT)->GetCurrentFrame() == 2 && Simon::GetInstance()->GetDirect() < 0)
		{
			left = Simon::GetInstance()->x - 50;
			top = Simon::GetInstance()->y + 20;
			right = left + 50;
			bottom = top + 15;
		}
	}
}

void CWhip::Render()
{
	if (Simon::GetInstance()->GetDirect() < 0)
		animation_set->at(WHIP_ANI_LV1_LEFT)->Render(x, y, 255);
	else
		animation_set->at(WHIP_ANI_LV1_RIGHT)->Render(x, y, 255);
	RenderBoundingBox();
}
