#include "Panther.h"
#include"Simon.h"
#include"Brick.h"
CPanther::CPanther(float x, float y, float xJumpRight, float xJumpLeft,int nx) :CEnemy()
{
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->xJumpRight = xJumpRight;
	this->xJumpLeft = xJumpLeft;
	type = 2;
	jumpCount = 1;
	isActive = true;
	isJump = false;
	isRun = false;
	isSit = true; 
}
void CPanther::Jump()
{
	if (isJump == true) 
		return;
	isJump = true;
	isRun = false;
	isSit = false;
	vy = -PANTHER_JUMP_SPEED_Y;
}
void CPanther::Run()
{
	if (isRun == true)
		return;
	isRun = true;
	isJump = false;
	isSit = false;
	vy = 0;
	vx = PANTHER_RUN_SPEED*this->nx;
}
void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += PANTHER_GRAVITY * dt;

	if (nx > 0)
		distance = PANTHER_RIGHT_DISTANCE;
	else distance = PANTHER_LEFT_DISTANCE;

	if (abs(Simon::GetInstance()->x - this->x) <= distance)
		Run();
	if(isRun == true && jumpCount == 1)
	{
		if ((nx > 0 && x >= xJumpRight) || (nx < 0 && x <= xJumpLeft))
		{
			Jump();
		}

	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isActive)
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
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) {}
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (isJump = true)
				{
					isJump = false;
					jumpCount--;
					if (Simon::GetInstance()->nx > 0)
						nx = -1;
					else if (Simon::GetInstance()->nx < 0)
						nx = 1;
					Run();
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CPanther::SetAnimation()
{
	 ani = PANTHER_ANI_SIT_LEFT;
	if (nx > 0)
	{
		if (isSit)
			ani = PANTHER_ANI_SIT_RIGHT;
		else if (isRun)
			ani = PANTHER_ANI_RUN_RIGHT;
		else if (isJump)
			ani = PANTHER_ANI_JUMP_RIGHT;
	}
	else {
		if (isRun)
			ani = PANTHER_ANI_RUN_RIGHT;
		else if (isJump)
			ani = PANTHER_ANI_JUMP_RIGHT;
	}
}
void CPanther::Render() {
	SetAnimation();

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y, color);

}

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
}