#pragma once
#include "GameObject.h"
#include "Simon.h"

#define TYPE_BELOW	0
#define TYPE_ABOVE	1
#define DIRECT_RIGHT	1
#define DIRECT_LEFT	0

class TriggerStair :public CGameObject
{
	int width = 32;
	int height = 63;
	int type;
	int direct;	//stair direction
	int standingPoint;
	int middlePoint;
	int offset = 6;	//distance from standingPoint to middlePoint

public:
	TriggerStair() {};
	TriggerStair(float l, float t, int type, int direct);

	bool IsFrontContainSimon();
	bool IsBackContainSimon();
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);


	//getter & setter
	int GetType() { return type; }
	int GetDirect() { return direct; }
	int GetStandingPoint() { return standingPoint; }

	~TriggerStair() {};
};
typedef TriggerStair *LTRIGGER_STAIR;
