#pragma once
#include "Holder.h"
#include "Brick.h"

#define FIREPOT_GRAVITY			0.00f
#define FIREPOT_DEFLECT_SPEED 0.2f

#define	FIREPOT_STATE_IDLE	0
#define FIREPOT_STATE_BREAK	100

#define FIREPOT_ANI_IDLE	0
#define FIREPOT_ANI_BREAK	2

#define FIREPOT_BBOX_WIDTH	32
#define FIREPOT_BBOX_HEIGHT	64

#define FIREPOT_BREAK_TIME 200

class CFirePot :public CHolder
{
	DWORD break_time;
	ItemType itemType;
public:
	CFirePot(int itemType);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();

	void SetState(int state);

	//Getter & setter
	void SetItem(int itemType);
	ItemType GetItemType() { return itemType; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
