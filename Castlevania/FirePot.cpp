#include "FirePot.h"
#include"Brick.h"
void CFirePot:: SetItem(int itemType) {
	ItemType type;
	switch (itemType)
	{
	case 0:
		type = ITEM_SMALL_HEART;
		break;
	case 1:
		type = ITEM_BIG_HEART;
		break;
	case 5:
		type = ITEM_WHIP_RED;
		break;
	case 7:
		type = ITEM_DAGGER;
		break;
	default:
		break;
	}
	this->itemType = type;
}
CFirePot::CFirePot(int itemType)
{

	SetState(FIREPOT_STATE_IDLE);
	SetItem(itemType);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CFirePot::SetState(int state)
{
	this->state = state;
	if (state == FIREPOT_STATE_BREAK)
		break_time = GetTickCount();
}

void CFirePot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIREPOT_BBOX_WIDTH;
	bottom = y + FIREPOT_BBOX_HEIGHT;
}

void CFirePot::Render()
{
	int ani = FIREPOT_ANI_IDLE;
	if (state == FIREPOT_STATE_BREAK) {
		ani = FIREPOT_ANI_BREAK;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CFirePot::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*if (IsBroken())
	{
		item.Update(dt, coObjects);
	}*/
	CGameObject::Update(dt, coObjects);
	vy += FIREPOT_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<LPGAMEOBJECT> firepotCoObjects;

	for (int i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
			firepotCoObjects.push_back(coObjects->at(i));
	}
	coEvents.clear();
   
	CalcPotentialCollisions(&firepotCoObjects, coEvents);
	
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

		// block 
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

		if (ny != 0) {
			vy = 0;
		}

		if (state == FIREPOT_STATE_BREAK && ((GetTickCount() - break_time) > FIREPOT_BREAK_TIME))
		{
			this->isVanish = true;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
