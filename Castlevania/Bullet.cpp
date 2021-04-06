#include "Bullet.h"


Bullet::Bullet()
{
	isVanish = true;
}
void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + Bullet_BBOX_WIDTH;
	bottom = y + Bullet_BBOX_HEIGHT;
}

void Bullet::SetAnimation() {
	if (nx > 0)
		ani = CAnimationSets::GetInstance()->Get(62)->at(7);
	else
		ani = CAnimationSets::GetInstance()->Get(62)->at(7);
}

void Bullet::Render() {
	if (!isVanish && GetIsThrown()) {
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}



void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (!GetIsThrown()) return;
	vx = nx * Bullet_VX;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (x < Camera::GetInstance()->GetCamX() ||
			x > Camera::GetInstance()->GetCamX() + SCREEN_WIDTH) {
			isVanish = true;
			SetIsThrown(false);
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += dx;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				this->isVanish = true;
			}
			if (dynamic_cast<Simon*>(e->obj))
			{
				Simon* simon = Simon::GetInstance();
				simon->SetHealth(simon->GetHealth() - 2);
				simon->SetState(SIMON_STATE_HURT);
			}

		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

