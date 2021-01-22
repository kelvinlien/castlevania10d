#include "Bat.h"
#include "Simon.h"
CBat::CBat(float x, float y, int nx, int itemType) :CEnemy()
{
	SetItem(itemType);
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->type = 20; // 20 là bat nên thay bằng enum
	isActive = true;
	vx = BAT_FLY_SPEED_X * this->nx;
}
void CBat::SetState(int state)
{
	CEnemy::SetState(state);
	if (state == ENEMY_STATE_DIE) {
		die_time = GetTickCount();
		vx = 0;
	}
}
void CBat::Respawn()
{
	y = Simon::GetInstance()->GetPostionY();
	srand(time(NULL));
	int res = rand() % (2 - 1 + 1) + 1;
	Camera* cam = Camera::GetInstance();
	switch (res)
	{
	case 1:
		x = cam->GetCamX() - 20;
		nx = 1;
		break;
	case 2:
		x = cam->GetCamX() + SCREEN_WIDTH + 20;
		nx = -1;
		break;
	}
	isActive = true;
	SetState(BAT_STATE_IDLE);
	isVanish = false;
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == ENEMY_STATE_DIE && ((GetTickCount() - die_time) > BAT_DIE_TIME))
	{
		startDieTime = GetTickCount();
		isVanish = true;
	}
	else if (state != ENEMY_STATE_DIE && isLock != true)
		vx = BAT_FLY_SPEED_X * this->nx;

	CGameObject::Update(dt);
	vy += amplitude;
	
	if (vy >= BAT_FLY_SPEED_Y || vy <= -BAT_FLY_SPEED_Y)
		amplitude *= -1;

	x += dx;
	y += dy;

}

void CBat::Render() {

	ani = BAT_ANI_RIGHT;
	if (this->nx < 0) ani = BAT_ANI_LEFT;
	if (state == ENEMY_STATE_DIE) 
		ani = BAT_ANI_DIE;

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y, color);
	RenderBoundingBox();
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}
