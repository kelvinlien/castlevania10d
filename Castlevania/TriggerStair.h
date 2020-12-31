#pragma once
#include "GameObject.h"
#include "Simon.h"

#define TYPE_BELOW	0
#define TYPE_ABOVE	1
#define DIRECT_RIGHT	1
#define DIRECT_LEFT	0

class TriggerStair :public CGameObject
{
	float width = 32;
	float height = 63;
	int type;
	int direct;	//stair direction
	float standingPoint;
	float middlePoint;
	float offset = 0;	//distance from standingPoint to middlePoint

public:
	TriggerStair() {};
	TriggerStair(float l, float t, int type, int direct);

	bool IsContainSimon();
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);


	//getter & setter
	int GetType() { return type; }
	int GetDirect() { return direct; }
	float GetStandingPoint() { return standingPoint; }

	~TriggerStair() {};
};
typedef TriggerStair *LTRIGGER_STAIR;

class TriggerStairs
{
	static TriggerStairs * __instance;
	vector<LTRIGGER_STAIR> triggerStairs; // manage every trigger stair

public:
	vector<LTRIGGER_STAIR> GetTriggerStairs() { return triggerStairs; }
	void Add(LTRIGGER_STAIR triggerStair);
	LTRIGGER_STAIR Get(int ID) { return triggerStairs.at(ID); }

	static TriggerStairs * GetInstance();
};