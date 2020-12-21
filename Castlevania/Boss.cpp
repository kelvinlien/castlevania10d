#include "Boss.h"
#include "Simon.h"

CBoss::CBoss()
{
	type = 15;
	isActive = false;
	isFly = false;
}

void CBoss::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (ani == BOSS_ANI_IDLE)
	{
		left = x + 32;
		top = y + 4;
		right = left + BOSS_IDLE_BBOX_WIDTH;
		bottom = top + BOSS_IDLE_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + BOSS_FLY_BBOX_WIDTH;
		bottom = y + BOSS_FLY_BBOX_HEIGHT;
	}
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (isFly)
	{
		vy += BOSS_GRAVITY * dt;
	}

	if (Simon::GetInstance()->x >= this->x)
	{
		isActive = true;
	}

	if (isActive)
	{
		if (Simon::GetInstance()->x >= this->x)
			this->nx = 1;
		else
			this->nx = -1;
		Fly();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

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
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoss::Render()
{
	SetAnimation();
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBoss::SetAnimation()
{
	ani = BOSS_ANI_IDLE;
	if (isFly)
		ani = BOSS_ANI_FLY;
}

void CBoss::Fly()
{
	vx = BOSS_FLY_SPEED * this->nx;
	isFly = true;
}