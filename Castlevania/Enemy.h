#pragma once
#include"GameObject.h"
using namespace std;
class CEnemy: public CGameObject
{
protected:
	bool isActive;
	int type;
public:
	CEnemy();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }
	void SetActive() { if (!isActive) isActive = true; }
};

