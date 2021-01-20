#pragma once
#include "GameObject.h"
#include "Game.h"
#define TITLE_STATE_BLINK  100
#define BLINK_TIME	1500

#define TITLE_ANI_IDLE	0
#define TITLE_ANI_BLINK	1

class Title : public CGameObject
{
	DWORD startBlinkTime = 0;
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) {};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	Title() {};
};

