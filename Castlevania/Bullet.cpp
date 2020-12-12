#include "Bullet.h"
#include "Camera.h"
#include "Simon.h"


Bullet::Bullet(int x, int y, int nx) 
{
	this->nx = nx;
	this->x = x;
	this->y = y;
	vx = BULLET_SPEED * nx;
	isVanish = false;
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (isVanish) return;

	CGameObject::Update(dt, coObject);
	x += dx;
	if (x > Camera::GetInstance()->GetCamX() + SCREEN_WIDTH || x < Camera::GetInstance()->GetCamX())
	{
		isVanish = true;
	}
}

void Bullet::Render()
{
	if (isVanish) return;
	int ani = 0;
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void Bullet::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;

}

