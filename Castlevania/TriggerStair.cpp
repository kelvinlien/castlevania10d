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
	if (direct == DIRECT_RIGHT)
		standingPoint = x + width + 8;
	else
		standingPoint = x - 4;
	if (type == TYPE_BELOW)
		outPoint = y + height - 1;
	else
		outPoint = y + height + 1;
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
	if (Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH - 10 >= x && Simon::GetInstance()->GetPostionX() + 12 < x + width && Simon::GetInstance()->GetPostionY() >= y && Simon::GetInstance()->GetPostionY() + SIMON_BBOX_HEIGHT < y + height + 1)
		return true;
	return false;
}