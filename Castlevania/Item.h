#pragma once
#include "Sprites.h"
#include "GameObject.h"
#include "Animations.h"

#define ITEM_ANI_SET_ID	4

#define EFFECT_ANI_SET_ID	7

#define GRAVITY 0.3f

#define TIME_BEFORE_SWITCHING_TO_OTHER_BACKGROUND_COLOR_WHILE_USING_CROSS	500

enum ItemType
{
	ITEM_SMALL_HEART,
	ITEM_BIG_HEART,
	ITEM_MONEY_BAG_RED,
	ITEM_MONEY_BAG_WHITE,
	ITEM_MONEY_BAG_BLUE,
	ITEM_WHIP,
	ITEM_STOP_WATCH,
	ITEM_DAGGER,
	ITEM_CROSS,
	ITEM_HOLY_WATER,
	ITEM_CHICKEN_THIGH,
	ITEM_AXE,
	ITEM_ORD,
	ITEM_DOUBLE_SHOT
};

enum EffectType
{
	BURN_EFFECT,
	FOUR_HUNDRED_EFFECT,
	SEVEN_HUNDRED_EFFECT,
	ONE_THOUSAND_EFFECT,
	HIT_EFFECT
};

class Item :public CGameObject {
public:
	LPANIMATION_SET ani_set;
	float existingTime;
	float effectTime;
	int widthBBox;
	int heightBBox;
	bool isEaten;
	
	ItemType ani;

	EffectType effect;

	Item() {};
	~Item() {  };
	Item(int x, int y, ItemType ani);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects); // for update collision
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	ItemType GetType() { return ani; }
	void BeingProcessed();
};
