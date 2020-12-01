#include "HolyWater.h"


HolyWater::HolyWater()
{
	isVanish = true;
}
void HolyWater::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + HOLY_WATER_BBOX_WIDTH;
	bottom = y + HOLY_WATER_BBOX_HEIGHT;
}

void HolyWater::SetAnimation() {
	if (nx > 0)
		ani = CWeapon::animation_set->at(ANI_HOLY_WATER_RIGHT);
	else
		ani = CWeapon::animation_set->at(ANI_HOLY_WATER_LEFT);
}

void HolyWater::Render() {
	if (!isVanish) {
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}



void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;



	vx = nx * HOLY_WATER_VX;
	vy = nx * HOLY_WATER_VY;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (x < Camera::GetInstance()->GetCamX() ||
			x > Camera::GetInstance()->GetCamX() + SCREEN_WIDTH) {
			isVanish = true;
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
			if (dynamic_cast<CFirePot*>(e->obj))
			{
				this->isVanish = true;
				e->obj->isVanish = true;
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

