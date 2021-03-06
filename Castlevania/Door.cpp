#include "Door.h"
#include "Simon.h"
#include"Camera.h"

CDoor::CDoor(float x, float y,int id) : CGameObject()
{
	this->x = x;
	this->y = y;
	this->id = id;
	ani = DOOR_ANI_CLOSED;
	isClosed = true;
	isActive = false;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (!isActive)
		return;
	if (isClosed && !Camera::GetInstance()->GetIsAuto())
	{
		ani = DOOR_ANI_OPENING;
		isClosed = false;
		if(Time==0)
		 Time = GetTickCount();
	}
	else if (GetTickCount() - Time > 400 && ani == DOOR_ANI_OPENING)
	{
		ani = DOOR_ANI_OPENED;
		isOpened = true;
		Time = 0;
	}
	else if (isOpened && ((Simon::GetInstance()->x > SIMON_AUTO_GO_THROUGH_FIRST_DOOR && id == 1) || (Simon::GetInstance()->x > SIMON_AUTO_GO_THROUGH_SECOND_DOOR && id == 2)))
	{
		ani = DOOR_ANI_CLOSING;
		isOpened = false;
		if (Time == 0)
			Time = GetTickCount();
	}
	else if(GetTickCount() - Time > 400 && ani == DOOR_ANI_CLOSING)
	{
		ani = DOOR_ANI_CLOSED;
		isClosed = true;
		Time = 0;
		isActive = false;
		Camera::GetInstance()->SetIsAuto(true);
	}
}

void CDoor::Render()
{
	
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CDoor::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + DOOR_BBOX_WIDTH;
	bottom = y + DOOR_BBOX_HEIGHT;
}