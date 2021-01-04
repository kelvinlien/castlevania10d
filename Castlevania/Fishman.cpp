#include "Fishman.h"
#include "Simon.h"
float float_rand(float min, float max)
{
	float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
	return min + scale * (max - min);      /* [min, max] */
}
CFishman::CFishman(float x, float y, int nx, int itemType) :CEnemy()
{
	SetItem(itemType);
	this->nx = nx;
	this->x = x;
	this->y = y;
	this->ybackup = y;
	this->type = 30; // 30 là fishman nên thay bằng enum
	isActive = true;
	SetState(FISH_MAN_STATE_JUMP);
}
void CFishman::SetState(int state)
{
	this->state = state;

	switch (state)
	{
	case FISH_MAN_STATE_JUMP:
		vx = 0;
		vy = FISH_MAN_JUMPING_SPEED;
		isJump = true;
		break;
	case FISH_MAN_STATE_DEAD:
		isDead = true;
		vx = 0;
		vy = 0;
		dieTime = GetTickCount();
		break;
	case FISH_MAN_STATE_WALK:
		if (isShoot) return;
		vy = 0;
		vx = nx * FISH_MAN_WALKING_SPEED;
		break;
	case FISH_MAN_STATE_SHOOT:
		vx = 0;
		isShoot = true;
		startShootTime = GetTickCount();
		shootingTimePeriod = rand() % 2500 + 500;
		bullet->SetIsThrown(true);
		if (nx == -1)
			bullet->SetPosition(x, y + 10);
		else
			bullet->SetPosition(x + 15, y + 10);
		bullet->nx = nx;
		bullet->isVanish = false;
		isShootyet = true;
		break;
	}
}
void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDead && GetTickCount() - dieTime >= FISH_MAN_DIE_TIME)
	{
		startDieTime = GetTickCount();
		isVanish = true;
	}
	if (!isDead)
		CGameObject::Update(dt);

	vy += FISH_MAN_GRAVITY * dt;
	bullet->Update(dt, coObjects);
	if (isWaitToShoot && GetTickCount() - startWaitToShoot >= shootingTimePeriod)
	{
		startWaitToShoot = 0;
		isWaitToShoot = false;
		SetState(FISH_MAN_STATE_SHOOT);

	}
	if (isShoot && (GetTickCount() - startShootTime > FISH_MAN_SHOOTING_TIME))	//enemy fire
	{
		startShootTime = 0;
		isShoot = false;
		nx *= -1;
		SetState(FISH_MAN_STATE_WALK);
		WaitToShoot();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> coObjectsFishman;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick *>(coObjects->at(i)))

			coObjectsFishman.push_back(coObjects->at(i));
	}

	coEvents.clear();
	if (isActive)
		CalcPotentialCollisions(&coObjectsFishman, coEvents);

	// No collision occured, proceed normally

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) {}
		if (ny != 0) {
			SetState(FISH_MAN_STATE_WALK);
			WaitToShoot();
			if (shootingTimePeriod == 0) 
				shootingTimePeriod = rand() % 2500 + 500;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CFishman::WaitToShoot() {
	if (startWaitToShoot != 0) return;
	isWaitToShoot = true;
	startWaitToShoot = GetTickCount();
}

void CFishman::Respawn()
{
	isDead = false;
	y = ybackup;
	srand(time(NULL));
	Camera* cam = Camera::GetInstance();
	float res = float_rand(cam->GetCamX(),cam->GetCamX() + SCREEN_WIDTH);
	x = res;
	isActive = true;
	SetState(FISH_MAN_STATE_JUMP);
	isVanish = false;
}

void CFishman::Render() {

	ani = FISH_MAN_WALK_RIGHT;
	if (isShoot)
	{
		ani = FISH_MAN_SHOOT_RIGHT;
	}
	if (isShoot || isShootyet)
	{
		bullet->Render();
	}
	if (nx < 0) ani = static_cast<animation>(ani - 1); // because animation left always < animation right 1 index
	if (isDead) ani = FISH_MAN_DIE;
	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	animation_set->at(ani)->Render(x, y, color);
	RenderBoundingBox();
}

void CFishman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + FISH_MAN_BBOX_WIDTH;
	bottom = y + FISH_MAN_BBOX_HEIGHT;
}
