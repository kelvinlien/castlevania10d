#include "Door.h"
#include "Simon.h"
#include"Camera.h"
CDoor::CDoor(float x, float y)
{
	this->x = x;
	this->y = y;
	ani = DOOR_ANI_CLOSED;
	turnOffBb = false;
	isActive = false;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (!isActive)
		return;

	if (ani == DOOR_ANI_CLOSED && Camera::GetInstance()->GetCamX() >= 56)
	{
		ani = DOOR_ANI_OPENING;
		isClosed = false;
		Time = GetTickCount();
		turnOffBb = true;
	}
	else if (GetTickCount() - Time >= 500 && ani == DOOR_ANI_OPENING)
	{
		ani = DOOR_ANI_OPENED;
		isOpened = true;
		turnOffBb = true;
		Time = 0;
	}
	else if (ani = DOOR_ANI_OPENED && Camera::GetInstance()->GetCamX() >= 100)
	{
		ani = DOOR_ANI_CLOSING;
		isOpened = false;
		Time = GetTickCount();
		turnOffBb = true;
	}
	else if (GetTickCount() - Time >= 500 && ani == DOOR_ANI_CLOSING)
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
	if (turnOffBb)
		return;
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