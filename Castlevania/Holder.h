#pragma once
#include "GameObject.h"

#define TYPE_FIREPOT	0
#define TYPE_CANDLE	1

class CHolder :public CGameObject
{
	float start_x;			
	float start_y;
	int holderType;

public:
	CHolder();
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) = 0;

	virtual void Render() = 0;

	int GetHolderType() { return holderType; }
	void SetHolderType(int type) { this->holderType = type; }
};

