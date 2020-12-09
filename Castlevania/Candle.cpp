#include "Candle.h"
#include "Utils.h"
void CCandle::SetItem(int itemType) {
	ItemType type;
	switch (itemType)
	{
	case 1:
		type = ITEM_BIG_HEART;
		break;
	case 2:
		type = ITEM_MONEY_BAG_RED;
		break;
	case 3:
		type = ITEM_MONEY_BAG_WHITE;
		break;
	case 4:
		type = ITEM_MONEY_BAG_BLUE;
		break;
	case 5:
		type = ITEM_WHIP;
		break;
	case 6:
		type = ITEM_STOP_WATCH;
		break;
	case 7:
		type = ITEM_DAGGER;
		break;
	case 8:
		type = ITEM_CROSS;
		break;
	case 9:
		type = ITEM_HOLY_WATER;
		break;
	case 11:
		type = ITEM_VASE;
		break;
	case 12:
		type = ITEM_AXE;
		break;
	default:
		type = ITEM_SMALL_HEART;
		break;
	}
	this->itemType = type;
}
CCandle::CCandle(int itemType)
{

	SetState(CANDLE_STATE_IDLE);
	SetItem(itemType);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CCandle::SetState(int state)
{
	this->state = state;
	if (state == CANDLE_STATE_BREAK)
	{
		break_time = GetTickCount();
	}
}

void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

void CCandle::Render()
{
	int ani = CANDLE_ANI_IDLE;
	if (state == CANDLE_STATE_BREAK) {
		ani = CANLDE_ANI_BREAK;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*if (IsBroken())
	{
		item.Update(dt, coObjects);
	}*/
	CGameObject::Update(dt, coObjects);
	vy = 0;

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	//Candle is set to the wall and not collide with floor like Firepot so empty coEvents checking is bypassed to be able to continue

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

	if (state == CANDLE_STATE_BREAK && ((GetTickCount() - break_time) > CANDLE_BREAK_TIME))
	{
		this->isVanish = true;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}