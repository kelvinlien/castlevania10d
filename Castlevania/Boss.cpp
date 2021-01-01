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
void CBoss::SetDirectWhenCollideEdge() {
	if (this->x <= leftBound || this->x > rightBound)
		nx = -nx;
	if (this->y <= topBound || this->y > bottomBound)
		ny = -ny;
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
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_WAITING:
		if (isWaiting) return;
		this->start_x = this->x;
		this->start_y = this->y;

		isWaiting = true;
		isFlying = false;
		isReverse = false;

		startWaitTime = GetTickCount();
		vx = 0;
		vy = 0;
		fliedDistance = 0;
		RandomWaitingPos();
		break;
	case BOSS_STATE_FLYING:
		if (isFlying) return;

		isWaiting = false;
		isFlying = true;
		isReverse = false;

		startWaitTime = 0;
		//startFlyTime = GetTickCount();
		isFlying = true;

		vx = BOSS_FLY_SPEED_X * this->nx;
		vy = BOSS_FLY_SPEED_Y * this->ny;
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

	DebugOut(L"[TEST] middleLineX: %d\n", middleLineX);
	DebugOut(L"[TEST] middleLineY: %d\n", middleLineY);
	DebugOut(L"[TEST] waitingPos.x: %f\n", waitingPos.x);
	DebugOut(L"[TEST] waitingPos.y: %f\n", waitingPos.y);
	DebugOut(L"[TEST] x: %f\n", x); 
	DebugOut(L"[TEST] y: %f\n", y);


}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (state == BOSS_STATE_IDLE) {
		if (!isActive && Simon::GetInstance()->x >= this->x)
		{
			isActive = true;
			SetState(BOSS_STATE_WAITING);
		}
		else return;
	}

	if (isWaiting) {
		if (GetTickCount() - startWaitTime > BOSS_WAITING_TIME) {
			SetState(BOSS_STATE_FLYING);
		}
		SetTargetPos();
		SetDirect(targetPos);
		flyDistance = sqrt(pow(targetPos.x - this->start_x, 2) + pow(targetPos.y - this->start_y, 2));
	}

	if (isFlying)
	{
		fliedDistance = sqrt(pow(this->x - this->start_x, 2) + pow(this->y - this->start_y, 2));

		if (isOutCamera() && !isReverse) {
			RandomWaitingPos();
			targetPos.x = waitingPos.x;
			targetPos.y = waitingPos.y;
			SetDirect(targetPos);

			vx = vx / 2 * this->nx;
			vy = vy / 2 * this->ny;
			flyDistance = sqrt(pow(this->x - targetPos.x, 2) + pow(this->y - targetPos.y, 2));
			isReverse = true;
			this->start_x = this->x;
			this->start_y = this->y;
		}
		else if (fliedDistance >= flyDistance && !isReverse) {
			targetPos.x = waitingPos.x;
			targetPos.y = waitingPos.y;
			SetDirect(targetPos);

			fliedDistance = 0;
			vx = vx/2 * this->nx;
			vy = vy/2 * this->ny;
			flyDistance = sqrt(pow(this->x - targetPos.x, 2) + pow(this->y - targetPos.y, 2));
			isReverse = true;
			this->start_x = this->x;
			this->start_y = this->y;
		} 
		//else if (isOutCamera() && fliedDistance <= flyDistance) {
		//	targetPos.x = waitingPos.x;
		//	targetPos.y = waitingPos.y;
		//	SetDirect(targetPos);
		//	isReverse = true;
		//	vx = vx * this->nx;
		//	vy = vy  * this->ny;
		//	this->start_x = this->x;
		//	this->start_y = this->y;
		//}

		Fly(targetPos);
		//DebugOut(L"[TEST] distance: %f\n", flyDistance); 

	}
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
		x += dx;
		y += dy;
		if (targetPos.x == waitingPos.x && targetPos.y == waitingPos.y  && fliedDistance >= flyDistance) {
				SetState(BOSS_STATE_WAITING);
				DebugOut(L"[TEST] isWaiting....\n");
		}

		//if (targetPos.x == waitingPos.x && targetPos.y == waitingPos.y && fliedDistance >= flyDistance /*|| isOutCamera() && fliedDistance <= flyDistance*/) {
		//	SetState(BOSS_STATE_WAITING);
		//	DebugOut(L"[TEST] isWaiting....\n");
		//}

		//else if (isOutCamera()) {
		//	vx = -vx;
		//	vy = -vy;
		//}
}