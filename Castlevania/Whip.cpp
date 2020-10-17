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
	//set position for whip level 1 
	if (nx > 0)
		SetPosition((Simon::GetInstance()->x - 20), Simon::GetInstance()->y);
	else if (nx < 0)
		SetPosition((Simon::GetInstance()->x - 80), Simon::GetInstance()->y);

	float l, t, r, b;
	float l1, t1, r1, b1;
	RECT rect1, rect2;
	GetBoundingBox(l, t, r, b);
	rect1.left = (int)l;
	rect1.top = (int)t;
	rect1.right = (int)r;
	rect1.bottom = (int)b;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CFirePot *>(coObjects->at(i)))
		{
			CFirePot *e = dynamic_cast<CFirePot *>(coObjects->at(i));
			e->GetBoundingBox(l1, t1, r1, b1);
			rect2.left = (int)l1;
			rect2.top = (int)t1;
			rect2.right = (int)r1;
			rect2.bottom = (int)b1;
			if (isCollision(rect1, rect2))
				e->SetState(FIREPOT_STATE_DIE);
		}
		  
	}


}
bool CWhip::isCollision(RECT r1, RECT r2)
{
	return !(r1.right < r2.left || r1.left > r2.right || r1.top > r2.bottom || r1.bottom < r2.top);
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
