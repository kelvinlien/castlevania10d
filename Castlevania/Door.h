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
	static CDoor *__instance;

	DWORD Time=0;
	int ani;
	//int openTime;
	bool isActive;
	bool turnOffBb;
	bool isClosed;
	bool isOpened;
public:
	CDoor();
	void SetActive(bool active) { isActive = active; }
	//void SetOpenTime(int i) { openTime = i; }
	bool IsActive() { return isActive; }
	bool IsClosed() { return isClosed; }
	bool IsOpened() { return isOpened; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	static CDoor * GetInstance();

};

