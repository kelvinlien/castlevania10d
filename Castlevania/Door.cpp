#include "Door.h"
#include "Simon.h"
#include"Camera.h"
CDoor* CDoor::__instance = NULL;

CDoor* CDoor::GetInstance()
{
	if (__instance == NULL)
		__instance = new CDoor();
	return __instance;
}
CDoor::CDoor() : CGameObject()
{
	ani = DOOR_ANI_CLOSED;
	isClosed = true;
	turnOffBb = false;
	isActive = false;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (!isActive)
		return;
	if (isClosed && !Camera::GetInstance()->GetIsAuto())
	{
		turnOffBb = true;
		ani = DOOR_ANI_OPENING;
		isClosed = false;
		if(Time==0)
		 Time = GetTickCount();
	}
	else if (GetTickCount() - Time > 400 && ani == DOOR_ANI_OPENING)
	{
		ani = DOOR_ANI_OPENED;
		isOpened = true;
		turnOffBb = true;
		Time = 0;
	}
	else if (isOpened && !Simon::GetInstance()->IsAutoWalking())
	{
		ani = DOOR_ANI_CLOSING;
		isOpened = false;
		if (Time == 0)
			Time = GetTickCount();
		turnOffBb = true;
	}
	else if(GetTickCount() - Time > 400 && ani == DOOR_ANI_CLOSING)
	{
		ani = DOOR_ANI_CLOSED;
		isClosed = true;
		turnOffBb = false;
		Time = 0;
		isActive = false;
	}
}

void CDoor::Render()
{
	
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CDoor::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (turnOffBb)
		return;
	left = x;
	top = y;
	right = x + DOOR_BBOX_WIDTH;
	bottom = y + DOOR_BBOX_HEIGHT;
}