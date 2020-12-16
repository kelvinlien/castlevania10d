#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32
#define TYPE_BIG_BRICK	0
#define TYPE_4_SMALL_BRICKS	1
#define TYPE_3_SMALL_BRICKS	2
#define STATE_BRICK_IDLE	0
#define STATE_BRICK_BREAK	1

enum Animation
{
	ANI_BIG_BRICK,
	ANI_4_SMALL_BRICKS,
	ANI_3_SMALL_BRICKS
	//ANI_BROKEN_BRICK
};

class CBrokenBrick :public CGameObject
{
	int brickType;
	bool isBroken;
	Animation ani;
	//DWORD break_time;
	ItemType itemType;
public:
	//getter & setter
	int GetBrickType() { return brickType; }
	void SetBrickType(int type) { this->brickType = type; }
	bool GetIsBroken() { return isBroken; }
	void SetIsBroken(bool isBroken) { this->isBroken = isBroken; }
	ItemType GetItemType() { return itemType; }
	void SetItem(int itemType);
	void SetState(int state);

	CBrokenBrick(int brickType, int itemType);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

