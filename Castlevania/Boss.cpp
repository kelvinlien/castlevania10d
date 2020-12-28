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
		RandomWaitingPos();
		break;
	case BOSS_STATE_FLYING:
		if (isFlying) return;

		isWaiting = false;
		isFlying = true;
		isReverse = false;
		startWaitTime = 0;
		startFlyTime = GetTickCount();
		isFlying = true;

		if (this->x < targetPos.x) {
			vx = BOSS_FLY_SPEED_X;
		}
		else 
			vx = -BOSS_FLY_SPEED_X;


		if (this->y >= targetPos.y) {
			vy = -BOSS_FLY_SPEED_Y;
		}
		else
			vy = BOSS_FLY_SPEED_Y;
	}
	
}

void CBoss::SetTargetPos() {
	//if (Simon::GetInstance()->x >= this->x)
	//	isNearSimon = true;

	targetPos.x = Simon::GetInstance()->x;
	targetPos.y = Simon::GetInstance()->y;
}

void CBoss::RandomWaitingPos() {
	srand(time(NULL));
	int camX = (int)Camera::GetInstance()->GetCamX();
	int camY = (int)Camera::GetInstance()->GetCamY() ; // 120 is height of board

	waitingPos.x = rand() % (512 - BOSS_FLY_BBOX_WIDTH) + camX;
	waitingPos.y = rand() % (480 - 160) + 80;
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
		flyDistance = sqrt(pow(targetPos.x - this->start_x, 2) + pow(targetPos.y - this->start_y, 2));

	}

	if (isFlying)
	{
		DebugOut(L"[TEST]  leftX: %f\n", leftCamX);
		DebugOut(L"[TEST]  rightX: %f\n", rightCamX);
		DebugOut(L"[TEST]  topY: %f\n", topCamY);
		DebugOut(L"[TEST]  bottomY: %f\n", bottomCamY);

		if (!isReverse)
			fliedDistance = sqrt(pow(this->x - this->start_x, 2) + pow(this->y - this->start_y, 2));
		else {

			fliedDistance = sqrt(pow(this->x - targetPos.x, 2) + pow(this->y - targetPos.y, 2));

		}
		if (isOutCamera()) {
			if (this->x < targetPos.x) {
				vx = BOSS_FLY_SPEED_X;
			}
			else
				vx = -BOSS_FLY_SPEED_X;


			if (this->y >= targetPos.y) {
				vy = -BOSS_FLY_SPEED_Y;
			}
			else
				vy = BOSS_FLY_SPEED_Y;
		}
		if (fliedDistance >= flyDistance && !isReverse) {

			targetPos.x = waitingPos.x;
			targetPos.y = waitingPos.y;
			//vx = -vx/2;
			//vy = -vy/2;
			flyDistance = sqrt(pow(this->x - targetPos.x, 2) + pow(this->y - targetPos.y, 2));

			//fliedDistance = 0;

			/*vx = -0.15;
			vy = -0.1;

			if (this->x < targetPos.x) {
				vx = -vx;
			}

			if (this->y >= targetPos.y) {
				vy = -vy;
			}*/
		}

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
	//if (!isNearSimonByAxisX() && !isNearSimonByAxisY()) {
		x += dx;
		y += dy;
	//}

	/*if (isNearSimonByAxisX()) {
		y += dy;
	} 

	if (isNearSimonByAxisY()) {
		x += dx;
	}
*/		
		/*DebugOut(L"[TEST] fliedDistance: %f\n", fliedDistance);
		DebugOut(L"[TEST]  flyDistance: %f\n", flyDistance);*/
		//DebugOut(L"[TEST]  targetPos.x: %f\n", targetPos.x);
		//DebugOut(L"[TEST]  waitingPos.x: %f\n", waitingPos.x);
		//DebugOut(L"[TEST]  targetPos.y: %f\n", targetPos.y);
		//DebugOut(L"[TEST]  waitingPos.y: %f\n", waitingPos.y);

		if (fliedDistance >= flyDistance && targetPos.x == waitingPos.x && targetPos.y == waitingPos.y) {
			SetState(BOSS_STATE_WAITING);
			isReverse = true;
			DebugOut(L"[TEST] isWaiting....\n");

		}

	//if (isNearSimonByAxisX() && isNearSimonByAxisY())
	//{
		//isAtTarget = true;
		/*DebugOut(L"[TEST] targetPos: %f\n", targetPos);
		DebugOut(L"[TEST] waitingPos: %f\n", waitingPos);*/

		/*if (this->x == waitingPos.x && targetPos.y == waitingPos.y) {
			SetState(BOSS_STATE_WAITING);
		}*/
	//}
}