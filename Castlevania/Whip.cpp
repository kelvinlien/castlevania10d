#include "Whip.h"
#include"Simon.h"
#include"Ghost.h"
#include "Candle.h"
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
void CWhip::LevelUp()
{
	if(level<3)
	  level++;
}
void CWhip::Update(DWORD dt, vector< LPGAMEOBJECT>*coObjects)
{
	//set position for whip all level 
	if (nx > 0)
		SetPosition((Simon::GetInstance()->x - 20), Simon::GetInstance()->y);
	else if (nx < 0)
		SetPosition((Simon::GetInstance()->x - 80), Simon::GetInstance()->y);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		float l1, t1, r1, b1;
		float l2, t2, r2, b2;
		GetBoundingBox(l1, t1, r1, b1);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CFirePot *>(coObjects->at(i)))
			{
				CFirePot *e = dynamic_cast<CFirePot *>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(FIREPOT_STATE_BREAK);
			}
			else if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy *e = NULL;
				switch (dynamic_cast<CEnemy *>(coObjects->at(i))->GetType())
				{
				case 1:
					e = dynamic_cast<CGhost *>(coObjects->at(i));
					break;
				default:
					break;
				}
				if (e != NULL) {
					e->GetBoundingBox(l2, t2, r2, b2);
					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
						e->SetState(GHOST_STATE_DIE);
				}
			}
			else if (dynamic_cast<CCandle *>(coObjects->at(i)))
			{
				CCandle *e = dynamic_cast<CCandle *>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(CANDLE_STATE_BREAK);
			}
		}
		  
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy *e=NULL;
				switch (dynamic_cast<CEnemy *>(coObjects->at(i))->GetType())
				{
				case 1:
					e = dynamic_cast<CGhost *>(coObjects->at(i));
					break;
				default:
					break;
				}
				if (e != NULL) {
					e->SetState(GHOST_STATE_DIE);
				}

			}
		}
	}
}
//bool CWhip::isCollision(RECT r1, RECT r2)   
//{
//	return !(r1.right < r2.left || r1.left > r2.right || r1.top > r2.bottom || r1.bottom < r2.top);
//}


void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == 1 || level == 2) {
		if (animation_set->at(level+2)->GetCurrentFrame() == 2 && Simon::GetInstance()->GetDirect() > 0)
		{
			left = Simon::GetInstance()->x + 60;
			top = Simon::GetInstance()->y + 20;
			right = left + 50;
			bottom = top + 15;
		}
		else if (animation_set->at(level-1)->GetCurrentFrame() == 2 && Simon::GetInstance()->GetDirect() < 0)
		{
			left = Simon::GetInstance()->x - 50;
			top = Simon::GetInstance()->y + 20;
			right = left + 50;
			bottom = top + 15;
		}
	}
	else if(level==3) {
		if (animation_set->at(level + 2)->GetCurrentFrame() == 2 && Simon::GetInstance()->GetDirect() > 0)
		{
			left = Simon::GetInstance()->x + 60;
			top = Simon::GetInstance()->y + 20;
			right = left + 78;
			bottom = top + 15;
		}
		else if (animation_set->at(level - 1)->GetCurrentFrame() == 2 && Simon::GetInstance()->GetDirect() < 0)
		{
			left = Simon::GetInstance()->x - 77;
			top = Simon::GetInstance()->y + 20;
			right = left + 78;
			bottom = top + 15;
		}
	}
}

void CWhip::Render()
{
	if (Simon::GetInstance()->GetDirect() < 0)
		animation_set->at(level-1)->Render(x, y, 255);
	else
		animation_set->at(level+2)->Render(x, y, 255);
	RenderBoundingBox();
}
