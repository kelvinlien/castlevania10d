#pragma once
#include"GameObject.h"
#include "Item.h"
using namespace std;
class CEnemy: public CGameObject
{
protected:
	bool isActive;
	int type;
	ItemType itemType;
	DWORD startDieTime;
public:
	CEnemy();
	void SetActive() { if (!isActive) isActive = true; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)=0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)=0;
	virtual void Render()=0;
	virtual void SetState(int state) { this->state = state; }
	virtual void Respawn();
	// Getter && Setter
	int GetType() { return type; }
	ItemType GetItemType() { return itemType; }
	void SetItem(int itemType);
	DWORD GetStartDieTime() { return startDieTime; }
	void SetStartDieTime(DWORD time) { startDieTime = time; }
};

