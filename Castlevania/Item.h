#pragma once
#include "Sprites.h"
#include "GameObject.h"
#include "Animations.h"

#define ITEM_ANI_SET_ID	4

#define GRAVITY 0.2f

enum ItemType
{
	ITEM_SMALL_HEART,
	ITEM_BIG_HEART,
	ITEM_MONEY_BAG_RED,
	ITEM_MONEY_BAG_WHITE,
	ITEM_MONEY_BAG_BLUE,
	ITEM_WHIP_RED,
	ITEM_WHIP_BLUE,
	ITEM_DAGGER,
	ITEM_STOP_WATCH,
	ITEM_CROSS,
	ITEM_HOLY_WATER
};

class Item :public CGameObject {
public:
	LPANIMATION_SET ani_set;
	float existingTime;
	int widthBBox;
	int heightBBox;
	
	ItemType ani;

	Item() {};
	~Item() {  };
	Item(int x, int y, ItemType ani);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects); // for update collision
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	ItemType GetType() { return ani; }
};
