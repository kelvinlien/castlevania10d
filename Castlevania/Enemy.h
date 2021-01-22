#pragma once
#include"GameObject.h"
#include "Item.h"

#define ENEMY_STATE_STOP	600
#define ENEMY_STATE_MOVE	700
#define ENEMY_STATE_DEAD	30

using namespace std;
class CEnemy: public CGameObject
{
protected:
	bool isActive;
	bool isLock;
	bool isdefeated;
	int type;
	ItemType itemType;
	int ani;
	float backUpVx;
	float backUpVy;

	DWORD startDieTime;
public:
	CEnemy();
	void SetActive() { if (!isActive) isActive = true; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)=0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)=0;
	virtual void Render()=0;
	virtual void Respawn();
	// Getter && Setter
	int GetType() { return type; }
	ItemType GetItemType() { return itemType; }
	void SetItem(int itemType);
	virtual void SetState(int state);
	DWORD GetStartDieTime() { return startDieTime; }
	void SetStartDieTime(DWORD time) { startDieTime = time; }
};

