#pragma once
#include"GameObject.h"


#define DOOR_ANI_CLOSED	0
#define DOOR_ANI_OPENED	1
#define DOOR_ANI_OPENING	2
#define DOOR_ANI_CLOSING	3

#define DOOR_BBOX_WIDTH		17
#define DOOR_BBOX_HEIGHT	96

class CDoor : public CGameObject
{
	DWORD Time;
	int ani;
	//int openTime;
	bool isActive;
	bool turnOffBb;
	bool isClosed;
	bool isOpened;
public:
	CDoor(float x, float y);
	void SetActive(bool active) { isActive = active; }
	//void SetOpenTime(int i) { openTime = i; }
	bool GetActive() { return isActive; }
	bool GetIsClosed() { return isClosed; }
	bool GetIsOpened() { return isOpened; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

