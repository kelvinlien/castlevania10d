#include "Dagger.h"


Dagger::Dagger()
{
	isVanish = true;
}
void Dagger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}

void Dagger::SetAnimation() {
	if (nx > 0)
		ani = CWeapon::animation_set->at(ANI_DAGGER_RIGHT);
	else
		ani = CWeapon::animation_set->at(ANI_DAGGER_LEFT);
}

void Dagger::Render() {
	if (!isVanish) {
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}



void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	
	vx = nx * DAGGER_VX;
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

