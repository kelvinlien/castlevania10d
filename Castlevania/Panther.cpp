#include "Panther.h"
#include"Simon.h"
#include"Brick.h"
CPanther::CPanther(float x, float y, float xJumpLeft, float xJumpRight, int nx) :CEnemy()
{
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->xJumpRight = xJumpRight;
	this->xJumpLeft = xJumpLeft;
	type = 10;  // panther type

	isActive = false;
	isJump = false;
	isRun = false;
	isSit = true; 
}
void CPanther::Jump()
{
	if (isJump)
		return;
	vx = PANTHER_RUN_SPEED_WHEN_JUMP * this->nx;
	vy = -PANTHER_JUMP_SPEED_Y;
	isJump = true;
	isRun = false;
	startJumpTime = GetTickCount();
}
void CPanther::Run()
{
	vx = PANTHER_RUN_SPEED*this->nx;
	isRun = true;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{	
	CGameObject::Update(dt);
	vy += PANTHER_GRAVITY * dt;

	float distance;
	distance = PANTHER_DISTANCE;

	//float simonCenterX = (Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH) / 2;
	if (isActive == false && abs(Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH / 2 + 10 - (this->x + PANTHER_BBOX_WIDTH / 2)) <= distance)
	{
		
		isSit = false;
		isActive = true;
		jumpCount = 1;
		if (Simon::GetInstance()->x < this->x)
			this->nx = -1;
		else
			this->nx = 1;
		Run();
	}

	/**************************
	xet va cham voi nen gach
	***************************/
	vector<LPGAMEOBJECT> coObjectsPanther;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	for (int i = 0; i < coObjects->size(); i++)
	{
		if(dynamic_cast<CBrick *> (coObjects->at(i)))
		  coObjectsPanther.push_back(coObjects->at(i));
	}

	coEvents.clear();
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
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;

		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				vy = 0;
				if (isJump) {

					isJump = false;
					if (Simon::GetInstance()->x < this->x)// && this->nx > 0)
						this->nx = -1;
					else //if (Simon::GetInstance()->x >= this->x > 0)// && this->nx < 0)
						this->nx = 1;
					Run();
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (jumpCount == 1)
	{
		if (this->nx < 0 && x < xJumpLeft || this->nx > 0 && x + PANTHER_BBOX_WIDTH >= xJumpRight)
		{
			vx = 0;
			jumpCount = 0;
			Jump();
		}
	}
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
	if (isJump && y < 350) return;
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}