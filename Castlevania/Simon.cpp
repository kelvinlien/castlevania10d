#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Goomba.h"
#include "Brick.h"
#include "Portal.h"
#include"Game.h"
Simon::Simon(float x, float y) :CGameObject()
{
	SetState(SIMON_STATE_IDLE);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}
void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	}
}
void Simon::Render()
{
	int ani = -1;
	if (state == SIMON_STATE_IDLE)
		ani = SIMON_ANI_IDLE;
	if (state == SIMON_STATE_DIE)
	{
		ani = NULL;
	}
	animation_set->at(ani)->Render(x, y, 255);

	RenderBoundingBox();
}
void Simon::Update(DWORD dt, vector< LPGAMEOBJECT>*coObjects)
{
	CGameObject::Update(dt);
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when simon die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
						SetState(SIMON_STATE_DIE);
				}
			} // if Goomba
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + 16;

	if (state == SIMON_STATE_DIE)
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	else
		bottom = y + 32;
}