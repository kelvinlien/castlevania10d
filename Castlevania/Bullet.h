#pragma once
#include "Weapon.h"
#include "FirePot.h"
#include "Simon.h"
#include "Candle.h"
#include "Camera.h"
#include "Define.h"
#include "Utils.h"
#define Bullet_BBOX_HEIGHT 16
#define Bullet_BBOX_WIDTH 16
#define Bullet_VX 0.35f
#define ANI_Bullet_LEFT 13
#define ANI_Bullet_RIGHT 13


class Bullet :public CWeapon {
	LPANIMATION ani;
public:
	Bullet();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetAnimation();
};