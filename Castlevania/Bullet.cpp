#include "Bullet.h"
#include "Camera.h"
#include "Simon.h"


Bullet::Bullet(int nx) 
{
	this->nx = nx;
	vx = BULLET_SPEED;
	isVanish = true;
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (!isFlying) return;

	CGameObject::Update(dt, coObject);
	x += dx;
	if (x > Camera::GetInstance()->GetCamX + SCREEN_WIDTH || x < Camera::GetInstance()->GetCamX())
	{
		isFlying = false;
	}
}

void Bullet::Render()
{
	int ani;
	if (!isFlying) return;

	ani[BULLET_ANI]->Render(x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
	//RenderBoundingBox();
}

void Bullet::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;

}

