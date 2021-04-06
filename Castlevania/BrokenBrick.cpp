#include "BrokenBrick.h"
#include "RepeatableEffect.h"
#include "RepeatableEffects.h"

CBrokenBrick::CBrokenBrick(int brickType, int itemType)
{
	this->x = x;
	this->y = y;
	this->brickType = brickType;
	SetItem(itemType);
	isBroken = false;
	SetState(STATE_BRICK_IDLE);
}

void CBrokenBrick::SetItem(int itemType) {
	ItemType type;
	switch (itemType)
	{
	case 4:
		type = ITEM_MONEY_BAG_BLUE;
		break;
	case 10:
		type = ITEM_CHICKEN_THIGH;
		break;
	case 13:
		type = ITEM_DOUBLE_SHOT;
		break;
	default:
		break;
	}
	this->itemType = type;
}

void CBrokenBrick::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case STATE_BRICK_IDLE:
		if (brickType == TYPE_BIG_BRICK)
			ani = ANI_BIG_BRICK;
		else if (brickType == TYPE_4_SMALL_BRICKS)
			ani = ANI_4_SMALL_BRICKS;
		else
			ani = ANI_3_SMALL_BRICKS;
		break;
	case STATE_BRICK_BREAK:
		isBroken = true;
		//break_time = GetTickCount();
	}
}

void CBrokenBrick::Render()
{
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBrokenBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrokenBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vector<LPGAMEOBJECT> firepotCoObjects;

	coEvents.clear();

	CalcPotentialCollisions(&firepotCoObjects, coEvents);

	if (isBroken) //&& GetTickCount() - break_time >= 500)
	{
		this->isVanish = true;
		CRepeatableEffects::GetInstance()->repeatEffects.push_back(new CRepeatableEffect(this->x, this->y, RUBBLE_FRAGMENT));
	}

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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
