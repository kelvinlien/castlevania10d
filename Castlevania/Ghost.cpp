#include "Ghost.h"
#include "Simon.h"
CGhost::CGhost(float x, float y, int nx, int itemType):CEnemy()
{
	SetItem(itemType);
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->type = 1; // 1 là ghost nên thay bằng enum
	isActive=true;
	vx = GHOST_WALKING_SPEED * this->nx;

}
void CGhost::SetState(int state)
{
	this->state = state;
	if (state == GHOST_STATE_DIE) {
		die_time = GetTickCount();
		vx = 0;
	}
}
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == GHOST_STATE_DIE && ((GetTickCount() - die_time) > GHOST_DIE_TIME))
		isVanish = true;
	
	CGameObject::Update(dt);
	vy += GHOST_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if(isActive)
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

		if (nx != 0){}
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Simon *>(e->obj)) // if e->obj is simon 
			{
				
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CGhost::Render() {
	
	ani = GHOST_ANI_RIGHT;
	if (this->nx < 0 && state != GHOST_STATE_DIE)
		ani = GHOST_ANI_LEFT;
	else if (state == GHOST_STATE_DIE)
		ani = GHOST_ANI_DIE;

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y ,color);
	RenderBoundingBox();
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
}
