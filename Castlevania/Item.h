#pragma once
#include "Sprites.h"
#include "GameObject.h"
#include "Animations.h"

#define ITEM_ANI_SET_ID	4

#define TYPE_ITEM_WHIP 0
#define TYPE_ITEM_BIG_HEART 1
#define TYPE_ITEM_SMALL_HEART 2
#define TYPE_ITEM_DAGGER 3
#define TYPE_ITEM_MONEY_BAG 4

#define GRAVITY 0.4f

enum Animation
{
	SMALL_HEART,
	BIG_HEART,
	MONEY_BAG_RED,
	MONEY_BAG_WHITE,
	MONEY_BAG_BLUE,
	WHIP_RED,
	WHIP_BLUE,
	DAGGER
};

class Item :public CGameObject {
public:
	LPANIMATION_SET ani_set;
	float existingTime;
	int widthBBox;
	int heightBBox;
	
	Animation ani;

	Item() {};
	~Item() {  };
	Item(int x, int y, Animation ani);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects); // for update collision
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	Animation GetType() { return ani; }
};
