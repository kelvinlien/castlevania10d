#pragma once
#include "Holder.h"
#define CANDLE_DEFLECT_SPEED 0.2f

#define	CANDLE_STATE_IDLE	0
#define CANDLE_STATE_BREAK	100

#define CANDLE_ANI_IDLE	1
#define CANLDE_ANI_BREAK	2

#define CANDLE_BBOX_WIDTH	16
#define CANDLE_BBOX_HEIGHT	32

#define CANDLE_BREAK_TIME 200

class CCandle :public CHolder
{
	DWORD break_time;
	ItemType itemType;
public:
	CCandle(int itemType);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	virtual void Render();

	void SetState(int state);

	//Getter & setter
	void SetItem(int itemType);
	ItemType GetItemType() { return itemType; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

