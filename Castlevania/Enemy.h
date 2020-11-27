#pragma once
#include"GameObject.h"

#define ENEMY_STATE_STOP	600
#define ENEMY_STATE_MOVE	700
using namespace std;
class CEnemy: public CGameObject
{
protected:
	bool isActive;
	bool isLock;
	int type;
public:
	CEnemy();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)=0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL)=0;
	virtual void Render()=0;
	virtual void SetState(int state);
	void SetActive() { if (!isActive) isActive = true; }
};

