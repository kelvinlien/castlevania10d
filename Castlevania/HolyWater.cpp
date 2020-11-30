#include "HolyWater.h"


HolyWater::HolyWater()
{
	isVanish = true;
	isBreak = false;
	SetState(STATE_HOLY_WATER_THROW);
	//this->vy = -HOLY_WATER_VY;
}

void HolyWater::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + HOLY_WATER_BBOX_WIDTH;
	bottom = y + HOLY_WATER_BBOX_HEIGHT;
	if (isBreak)
	{
		right = x + HOLY_WATER_BBOX_WIDTH * 2;
	}
}

void HolyWater::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case STATE_HOLY_WATER_THROW:
		/*CWeapon::animation_set->at(ANI_HOLY_WATER_USING)->ResetFrame();*/
		break;
	case STATE_HOLY_WATER_BREAK:
		if (isBreak) return;
		isBreak = true;
		startBurnTime = GetTickCount();
		break;
	}		
}

void HolyWater::SetAnimation() {
	if (this->nx > 0)
		ani = CWeapon::animation_set->at(ANI_HOLY_WATER_RIGHT);
	else
		ani = CWeapon::animation_set->at(ANI_HOLY_WATER_LEFT);
	if (isBreak)
		ani = CWeapon::animation_set->at(ANI_HOLY_WATER_USING);
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
		//SetState(STATE_HOLY_WATER_THROW);
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
				x += dx;
				y += dy;
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				SetState(STATE_HOLY_WATER_BREAK);
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

