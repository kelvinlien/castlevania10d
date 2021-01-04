#include "Axe.h"
#include "Candle.h"
#include "Ghost.h"
#include "Panther.h"

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