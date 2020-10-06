#include "FirePot.h"
CFirePot::CFirePot(float x, float y)
{
	SetState(FIREPOT_STATE_IDLE);

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

void CFirePot::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += FIREPOT_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

		if (ny != 0) {
			vy = 0;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
