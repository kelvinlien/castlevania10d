#include "HolyWater.h"
#include "Candle.h"
#include "Ghost.h"
#include "Panther.h"
#include "BrokenBrick.h"
#include "Bat.h"
#include "Fishman.h"

HolyWater::HolyWater()
{
	isVanish = true;
	isBreak = false;
	SetState(STATE_HOLY_WATER_THROW);
}

void HolyWater::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + HOLY_WATER_BBOX_WIDTH;
	bottom = y + HOLY_WATER_BBOX_HEIGHT;
	if (isBreak)
	{
		right = x + BROKEN_HOLY_WATER_BBOX_WIDTH;
		bottom = y + BROKEN_HOLY_WATER_BBOX_HEIGHT;
	}
}

void HolyWater::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case STATE_HOLY_WATER_THROW:
		/*CWeapon::animation_set->at(ANI_HOLY_WATER_USING)->ResetFrame();*/
		isBreak = false;
		this->vy = -HOLY_WATER_VY;

		break;
	case STATE_HOLY_WATER_BREAK:
		if (isBreak) return;
		y -= 6;
		isBreak = true;
		startBurnTime = GetTickCount();
		break;
	}		
}

void HolyWater::SetAnimation() {

	if (isBreak)
		ani = CWeapon::animation_set->at(ANI_HOLY_WATER_USING); 
	else {
		if (this->nx > 0)
			ani = CWeapon::animation_set->at(ANI_HOLY_WATER_RIGHT);
		else
			ani = CWeapon::animation_set->at(ANI_HOLY_WATER_LEFT);
	}
	/*else
		CWeapon::animation_set->at(ANI_HOLY_WATER_USING)->ResetFrame();*/
}

void HolyWater::Render() {
	
	if (!isVanish && GetIsThrown())
	{
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (!GetIsThrown()) return;

	/*if (Simon::GetInstance()->nx == 1)
		SetPosition(Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH - 10 - 4, Simon::GetInstance()->GetPostionY() + 20);
	else if (Simon::GetInstance()->nx == -1)
		SetPosition(Simon::GetInstance()->GetPostionX() + 12 - 16 + 4, Simon::GetInstance()->GetPostionY() + 20);*/

	//this->vy = -HOLY_WATER_VY;
	this->vx = this->nx * HOLY_WATER_VX;
	this->vy += HOLY_WATER_GRAVITY;
	

	if (isBreak && (GetTickCount() - startBurnTime >= BURN_TIME))
	{
		this->isBreak = false;
		this->isVanish = true;
		SetState(STATE_HOLY_WATER_THROW);
	}
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		if (!isBreak)
		{
			x += dx;
			y += dy;
		}
		float l1, t1, r1, b1;
		float l2, t2, r2, b2;
		GetBoundingBox(l1, t1, r1, b1);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CFirePot*>(coObjects->at(i)))
			{
				CFirePot* e = dynamic_cast<CFirePot*>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(FIREPOT_STATE_BREAK);
			}
			else if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy* e = NULL;

				switch (dynamic_cast<CEnemy*>(coObjects->at(i))->GetType())
				{
				case ENEMY_TYPE_GHOST:
					e = dynamic_cast<CGhost*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_PANTHER:
					e = dynamic_cast<CPanther*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_BAT:
					e = dynamic_cast<CBat*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_FISHMAN:
					e = dynamic_cast<CFishman*>(coObjects->at(i));
				default:
					break;
				}
				if (e != NULL) {
					e->GetBoundingBox(l2, t2, r2, b2);
					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
						e->SetState(ENEMY_STATE_DIE);
				}
				else if (dynamic_cast<CBrokenBrick*>(coObjects->at(i)))
				{
					CBrokenBrick* e = dynamic_cast<CBrokenBrick*>(coObjects->at(i));
					e->GetBoundingBox(l2, t2, r2, b2);
					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
						e->SetState(STATE_BRICK_BREAK);
				}
			}
			else if (dynamic_cast<CCandle*>(coObjects->at(i)))
			{
				CCandle* e = dynamic_cast<CCandle*>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(CANDLE_STATE_BREAK);
			}
			else if (dynamic_cast<CBrokenBrick*>(coObjects->at(i)))
			{
				CBrokenBrick* e = dynamic_cast<CBrokenBrick*>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(STATE_BRICK_BREAK);
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
			if (dynamic_cast<CEnemy*>(e->obj))
			{
				e->obj->isVanish = true;
				if (!isBreak)
				{
					x += dx;
					y += dy;
				}
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				SetState(STATE_HOLY_WATER_BREAK);
			}
			if (dynamic_cast<CCandle*>(e->obj))
			{
				e->obj->SetState(CANDLE_STATE_BREAK);
				x += dx;
				y += dy;
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

