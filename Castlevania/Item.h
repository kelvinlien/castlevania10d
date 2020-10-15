#pragma once
#include "Sprites.h"
#include "GameObject.h"
#include "Animations.h"

#define ITEM_ANI_SET_ID	4

#define GRAVITY 0.4f

enum Animation
{
	ANI_SMALL_HEART,
	ANI_BIG_HEART,
	ANI_MONEY_BAG_RED,
	ANI_MONEY_BAG_WHITE,
	ANI_MONEY_BAG_BLUE,
	ANI_WHIP_RED,
	ANI_WHIP_BLUE,
	ANI_DAGGER
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
