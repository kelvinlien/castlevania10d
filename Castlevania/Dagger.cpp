#include "Dagger.h"


Dagger::Dagger() : CWeapon()
{
	ani = CWeapon::animation_set->at(7);
	vx = DAGGER_VX;

	//Replace simon_x, simon_y
	x = 200;
	y = 230;
}
void Dagger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}
void Dagger::Render() {
	ani->Render(x, y);
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CFirePot*>(e->obj))
			{
				this->isVanish = true;
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				x += dx;
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

