#include "TriggerStair.h"

TriggerStair::TriggerStair(float l, float t, int type, int direct)
{
	this->type = type;
	this->direct = direct;
	x = l;
	y = t;
	middlePoint = x + width / 2;
	if (direct == 1)
		offset = -6;
	standingPoint = middlePoint + offset;
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

bool TriggerStair::IsFrontContainSimon()
{
	/*if (Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH - 10 >= x && Simon::GetInstance()->GetPostionX() < middlePoint && Simon::GetInstance()->GetPostionY() >= y && Simon::GetInstance()->GetPostionY() + SIMON_BBOX_HEIGHT < y + height)
		return true;
	return false;*/
}

bool TriggerStair::IsBackContainSimon()
{
	//if (Simon::GetInstance()->GetPostionX() + SIMON_BBOX_WIDTH - 10 >= middlePoint && Simon::GetInstance()->GetPostionX() < x + width && Simon::GetInstance()->GetPostionY() >= y && Simon::GetInstance()->GetPostionY() + SIMON_BBOX_HEIGHT < y + height)
	//	return true;
	//return false;
}