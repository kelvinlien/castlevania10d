#pragma once
#include "GameObject.h"
#include "RepeatableEffect.h"
class CRepeatableEffects: CGameObject
{
	static CRepeatableEffects * __instance;
	vector<LPREPEATEFFECT> repeatEffects;
public:
	
	CRepeatableEffects() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Render();
	static CRepeatableEffects * GetInstance();
	~CRepeatableEffects() {};
};

