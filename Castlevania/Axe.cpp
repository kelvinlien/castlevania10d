#include "Axe.h"
#include "Candle.h"
#include "Ghost.h"
#include "Panther.h"
#include "BrokenBrick.h"
#include "Bat.h"
#include "Fishman.h"

Axe::Axe()
{
	SetState(STATE_AXE_IDLE);
}

void Axe::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + AXE_BBOX_WIDTH;
	bottom = y + AXE_BBOX_HEIGHT;
}

void Axe::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case STATE_AXE_IDLE:
		this->isVanish = true;
		SetIsThrown(false);
		this->vy = -AXE_VY;
		break;
	}
}

void Axe::SetAnimation() {
	if (this->nx > 0)
		ani = CWeapon::animation_set->at(ANI_AXE_RIGHT);
	else
		ani = CWeapon::animation_set->at(ANI_AXE_LEFT);
}

void Axe::Render() {
	if (!isVanish && GetIsThrown())
	{
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (!GetIsThrown()) return;

	this->vx = this->nx * AXE_VX;
	this->vy += AXE_GRAVITY;

	if (this->y >= SCREEN_HEIGHT)
	{
		SetState(STATE_AXE_IDLE);
	}

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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
		x += dx;
		y += dy;
		
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
				SetIsThrown(false);
			}
			if (dynamic_cast<CCandle*>(e->obj))
			{
				e->obj->SetState(CANDLE_STATE_BREAK);
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}