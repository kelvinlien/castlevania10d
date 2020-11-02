#pragma once
#include "GameObject.h"
#include "Item.h"

#define TYPE_FIREPOT	0
#define TYPE_CANDLE	1



class CHolder :public CGameObject
{
	int holderType;
	bool isBroken = false;

public:
	CHolder();
	Item item;

	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) = 0;

	virtual void Render() = 0;

	//Getter & setter
	int GetHolderType() { return holderType; }
	void SetHolderType(int type) { this->holderType = type; }

	void SetBroken(bool isBroken) { this->isBroken = isBroken; }
	bool IsBroken() { return isBroken; }
};

