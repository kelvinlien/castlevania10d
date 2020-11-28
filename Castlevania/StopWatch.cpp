#include "StopWatch.h"
#include"Ghost.h"

StopWatch::StopWatch()
{
	isVanish = true;
}


void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	
	if (stopTime == 0)
	{
		stopTime = GetTickCount();
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy *e = NULL;
				switch (dynamic_cast<CEnemy *>(coObjects->at(i))->GetType())
				{
				case 1:
					e = dynamic_cast<CGhost *>(coObjects->at(i));
					break;
				default:
					break;
				}
				e->SetState(ENEMY_STATE_STOP);
			}
		}
	}
	if (GetTickCount() - stopTime > 10000)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy *e = dynamic_cast<CGhost*>(coObjects->at(i));
				e->SetState(ENEMY_STATE_MOVE);
			}
		}
		stopTime = 0;
		this->isVanish = true;
	}


	//***********************************//
	//CGameObject::Update(dt, coObjects);
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;
	//coEvents.clear();

	//CalcPotentialCollisions(coObjects, coEvents);

	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;

	//	float rdx = 0;
	//	float rdy = 0;
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		if (dynamic_cast<CFirePot*>(e->obj))
	//		{
	//			this->isVanish = true;
	//			e->obj->isVanish = true;
	//		}
	//		if (dynamic_cast<CBrick*>(e->obj))
	//		{
	//			x += dx;
	//		}
	//	}

	//	// clean up collision events
	//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//}
}

