#include "Panther.h"
#include"Simon.h"
#include"Brick.h"
CPanther::CPanther(float x, float y, float xJumpRight, float xJumpLeft, int nx) :CEnemy()
{
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->xJumpRight = xJumpRight;
	this->xJumpLeft = xJumpLeft;
	type = 5;  // panther type
	jumpCount = 1;
	isActive = true;
	isJump = false;
	isRun = false;
	isSit = true; 
}
void CPanther::Jump()
{
	if (isJump || isRun) 
		return;
	isJump = true;
	isRun = false;
	isSit = false;
	vy = -PANTHER_JUMP_SPEED_Y;
}
void CPanther::Run()
{
	if (isRun || isJump)
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

	if (this->nx > 0)
		distance = PANTHER_RIGHT_DISTANCE;
	else distance = PANTHER_LEFT_DISTANCE;

	if (abs(Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH - 10 - this->x) <= distance || abs(Simon::GetInstance()->GetPostionX() + 12 - (this->x + PANTHER_BBOX_WIDTH)) <= distance)
		Run();
	if(isRun && jumpCount == 1)
	{
		if ((this->nx > 0 && x >= xJumpRight) || (this->nx < 0 && x <= xJumpLeft))
		{
			Jump();
		}

	}
	vector<LPGAMEOBJECT> coObjectsPanther;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	for (int i = 0; i < coObjects->size(); i++)
	{
		if(!dynamic_cast<Simon *> (coObjects->at(i)))
		coObjectsPanther.push_back(coObjects->at(i));
	}

	coEvents.clear();
	if (isActive)
		CalcPotentialCollisions(&coObjectsPanther, coEvents);
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

		if (nx != 0);
		if (ny != 0) {
			if (isJump)
			jumpCount--;
			vy = 0;
		}


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				if
				if (Simon::GetInstance()->x - this->x < 0 && this->nx > 0)
					this->nx = -1;
				else if (Simon::GetInstance()->x - this->x > 0 && this->nx < 0)
					this->nx = 1;
				Run();
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
			ani = PANTHER_ANI_RUN_LEFT;
		else if (isJump)
			ani = PANTHER_ANI_JUMP_LEFT;
	}
}
void CPanther::Render() {
	SetAnimation();

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y, color);

	RenderBoundingBox();
}

void CPanther::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}