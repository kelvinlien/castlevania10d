#include "FirePot.h"
CFirePot::CFirePot()
{

}

void CFirePot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIREPOT_BBOX_WIDTH;
	bottom = y + FIREPOT_BBOX_HEIGHT;
}

void CFirePot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;
}

void CFirePot::Render()
{
	int ani = FIREPOT_ANI_1;
	animation_set->at(ani)->Render(x, y);
	
	ani == FIREPOT_ANI_2;
	animation_set->at(ani)->Render(x, y);
	
	//RenderBoundingBox();
}