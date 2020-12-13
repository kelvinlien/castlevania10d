#pragma once
#include"Fragment.h"
#include"GameObject.h"
class CRepeatableEffect:public CGameObject
{
	vector<LPFRAGMENT> fragments;
	type fragmentType;
public:
	CRepeatableEffect(float x, float y, type FragmentType);
	void SetType(float x, float y,type FragmentType);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Render();
	~CRepeatableEffect();
};

