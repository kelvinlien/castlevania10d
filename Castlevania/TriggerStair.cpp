#include "TriggerStair.h"

TriggerStairs * TriggerStairs::__instance = NULL;
TriggerStairs *TriggerStairs::GetInstance()
{
	if (__instance == NULL) __instance = new TriggerStairs();
	return __instance;
}

void TriggerStairs::Add(LTRIGGER_STAIR triggerStair)
{
	triggerStairs.push_back(triggerStair);
}


TriggerStair::TriggerStair(float l, float t, int type, int direct)
{
	this->type = type;
	this->direct = direct;
	x = l;
	y = t;
	//middlePoint = x + width / 2;
	//if (direct == 1)
	//	offset = -0;
	////if (type == 0)
	//	standingPoint = middlePoint + offset;
	//else
		//standingPoint = middlePoint - 50;
	if (direct == DIRECT_RIGHT)
		standingPoint = x + width + 8;
	else
		standingPoint = x - 4;
	if (type == TYPE_BELOW)
		outPoint = y + height - 16;
	else
		outPoint = y + height + 16;
}


void TriggerStair::Render()
{
	RenderBoundingBox();
}

void TriggerStair::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

bool TriggerStair::IsContainSimon()
{
	if (Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH - 10 >= x && Simon::GetInstance()->GetPostionX() + 12 < x + width && Simon::GetInstance()->GetPostionY() >= y && Simon::GetInstance()->GetPostionY() < y + height + 1)
		return true;
	return false;
}