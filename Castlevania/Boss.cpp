#include "Boss.h"
#include "Simon.h"

CBoss::CBoss()
{
	type = 15;
	isActive = false;
	isFlying = false;
	vx = 0;
	vy = 0;
}
void CBoss::SetDirect(D3DXVECTOR2 targetPos) {
	if (this->x <= targetPos.x)
		this->nx = 1;
	else if (this->x > targetPos.x)
		this->nx = -1;

	if (this->y <= targetPos.y)
		this->ny = 1;
	else if (this->y >= targetPos.y)
		this->ny = -1;
}

void CBoss::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (ani == BOSS_ANI_IDLE)
	{
		left = x + 32;
		top = y + 4;
		right = left + BOSS_IDLE_BBOX_WIDTH;
		bottom = top + BOSS_IDLE_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x + BOSS_FLY_BBOX_WIDTH;
		bottom = y + BOSS_FLY_BBOX_HEIGHT;
	}
}

void CBoss::SetState(int state)
{
	CEnemy::SetState(state);
	switch (state)
	{
	case BOSS_STATE_WAITING:
		this->start_x = this->x;
		this->start_y = this->y;

		isWaiting = true;
		isFlying = false;

		startWaitTime = GetTickCount();
		vx = 0;
		vy = 0;
		fliedDistance = 0;
		RandomWaitingPos();
		DebugOut(L"[TEST] isWaiting....\n");
		break;
	case BOSS_STATE_FLY_TO_TARGET:
		DebugOut(L"[TEST] flying to target....\n");

		isWaiting = false;
		isFlying = true;
		startWaitTime = 0;
		isFlying = true;

		vx = BOSS_FLY_SPEED_X * this->nx;
		vy = BOSS_FLY_SPEED_Y * this->ny;
		break;
	case BOSS_STATE_FLY_STRAIGHT:
		isWaiting = false;
		isFlying = true;
		startWaitTime = 0;
		isFlying = true;

		vy = BOSS_FLY_SPEED_Y * this->ny;
		break;
	case BOSS_STATE_FLY_BACK:
		DebugOut(L"[TEST] flying back....\n");
		this->start_x = this->x;
		this->start_y = this->y;
		targetPos.x = waitingPos.x;
		targetPos.y = waitingPos.y;
		isWaiting = false;

		SetDirect(targetPos);
		startWaitTime = 0;
		vx = BOSS_FLY_SPEED_X / 2 * this->nx;
		vy = BOSS_FLY_SPEED_Y / 2 * this->ny;
		flyDistance = sqrt(pow(targetPos.x - this->start_x, 2) + pow(targetPos.y - this->start_y, 2));

		//DebugOut(L"[TEST] middleLineX: %d\n", middleLineX);
		//DebugOut(L"[TEST] middleLineY: %d\n", middleLineY);
		break;
	case ENEMY_STATE_HURT:
		if (startStopTime == 0)
		{
			startStopTime = GetTickCount();
			isLock = true;
			animation_set->at(ani)->SetLock(true);
			backUpVx = vx;
			backUpVy = vy;
			vx = 0;
			vy = 0;
			health--;
		}
		break;
	}
}

void CBoss::SetTargetPos() {

	targetPos.x = Simon::GetInstance()->x;
	targetPos.y = Simon::GetInstance()->y;
}

void CBoss::RandomWaitingPos() {
	srand(time(NULL));
	int middleLineX = (leftBound + rightBound) / 2;
	int middleLineY = (topBound + bottomBound) / 2;
	if (this->x >= middleLineX)
		waitingPos.x = rand() % (middleLineX - leftBound + 1) + leftBound;
	else if (this->x < middleLineX)
		waitingPos.x = rand() % (rightBound - middleLineX + 1) + middleLineX;

	if (this->y >= middleLineY)
		waitingPos.y = rand() % (middleLineY - topBound + 1) + topBound;
	else if (this->y < middleLineY)
		waitingPos.y = rand() % (bottomBound - middleLineY + 1) + middleLineY;

	//DebugOut(L"[TEST] middleLineX: %d\n", middleLineX);
	//DebugOut(L"[TEST] middleLineY: %d\n", middleLineY);
	//DebugOut(L"[TEST] waitingPos.x: %f\n", waitingPos.x);
	//DebugOut(L"[TEST] waitingPos.y: %f\n", waitingPos.y);
	//DebugOut(L"[TEST] x: %f\n", x); 
	//DebugOut(L"[TEST] y: %f\n", y);


}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if(startStopTime!=0 && GetTickCount()- startStopTime > BOSS_STOP_TIME)
	{
		animation_set->at(ani)->SetLock(false);
		startStopTime = 0;
		isLock = false;
		vx = backUpVx;
		vy = backUpVy;
		this->state = BOSS_STATE_WAITING;
	}
	if (!isLock) {
		if (state == BOSS_STATE_IDLE) {
			if (!isActive && Simon::GetInstance()->x >= this->x)
			{
				isActive = true;
				SetState(BOSS_STATE_WAITING);
			}
			else return;
		}

		if (state == BOSS_STATE_WAITING) {
			SetTargetPos();
			SetDirect(targetPos);
			flyDistance = sqrt(pow(targetPos.x - this->start_x, 2) + pow(targetPos.y - this->start_y, 2));

			if (GetTickCount() - startWaitTime > BOSS_WAITING_TIME) {

				if (abs(this->x - Simon::GetInstance()->x) <= NEAR_DISTANCE_BOSS_AND_SIMON)
					SetState(BOSS_STATE_FLY_STRAIGHT);
				else
					SetState(BOSS_STATE_FLY_TO_TARGET);
			}
		}

		else if (state == BOSS_STATE_FLY_TO_TARGET)
		{
			fliedDistance = sqrt(pow(this->x - this->start_x, 2) + pow(this->y - this->start_y, 2));
			Fly(targetPos);
		}

		else if (state == BOSS_STATE_FLY_STRAIGHT)
		{
			fliedDistance = sqrt(pow(this->x - this->start_x, 2) + pow(this->y - this->start_y, 2));
			FlyStraight(targetPos);
		}

		else if (state == BOSS_STATE_FLY_BACK) {
			fliedDistance = sqrt(pow(this->x - this->start_x, 2) + pow(this->y - this->start_y, 2));
			FlyBack(targetPos);
		}
	}
	DebugOut(L"[TEST] Health point %d\n", health);
}

void CBoss::Render()
{
	SetAnimation();
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBoss::SetAnimation()
{
	ani = BOSS_ANI_IDLE;
	if (isActive) ani = BOSS_ANI_FLY;
}

void CBoss::Fly(D3DXVECTOR2 targetPos)
{
	
	if (fliedDistance >= flyDistance || this->y >= BOT_BOUND || this->x <= LEFT_BOUND || this->x >= RIGHT_BOUND) {
		SetState(BOSS_STATE_FLY_BACK);
		return;
	}
	
	x += dx;
	y += dy;
}

void CBoss::FlyStraight(D3DXVECTOR2 targetPos)
{

	if (fliedDistance >= flyDistance || this->y >= BOT_BOUND || this->x <= LEFT_BOUND || this->x >= RIGHT_BOUND) {
		SetState(BOSS_STATE_FLY_BACK);
		return;
	}
	y += dy;
}


void CBoss :: FlyBack(D3DXVECTOR2 targetPos) {
	if (fliedDistance >= flyDistance || this->y <= TOP_BOUND || this->x <= LEFT_BOUND || this->x >= RIGHT_BOUND) {
		DebugOut(L"[TEST] prepare to waiting....\n");
		SetState(BOSS_STATE_WAITING);
		return;
	}
	x += dx;
	y += dy;
}