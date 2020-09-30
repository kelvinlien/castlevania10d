#pragma once
#include "GameObject.h"

#define TYPE_WHIP	0
#define TYPE_DAGGER	1

class CWeapon :public CGameObject
{
	float start_x;			// initial position of Mario at scene
	float start_y;
	int weaponType;

public:
	CWeapon();
	bool isAvailable;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

	virtual void Render() = 0;

	int GetWeaponType() {	return weaponType;}
	void SetWeaponType(int type) {this->weaponType = type;}
};

