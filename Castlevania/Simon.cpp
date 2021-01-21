#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Goomba.h"
#include "Brick.h"
#include "Portal.h"
#include "Game.h"
#include "Item.h"
#include "Whip.h"
#include "Candle.h"
#include "BlinkEffect.h"
#include "SmallBrick.h"
#include "Door.h"
#include "Camera.h"
#include "Bat.h"
#include "BrokenBrick.h"
#include "WaterSurface.h"
Simon* Simon::__instance = NULL;

Simon* Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
	return __instance;
}
Simon::Simon() : CGameObject()
{
	triggerStairs = TriggerStairs::GetInstance();

	SetState(SIMON_STATE_IDLE);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	CWhip::GetInstance();
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_DIE:
		isDead = true;
		isUntouchable = false;
		isSit = false;
		isFall = false;
		y -= 20;
		vy = 0;
		break;
	case SIMON_STATE_AUTO:
		if (!flag)
		{
			nx = -1;
		}
		else
		{
			nx = 1;
		}
		Walk();
		break;
	case SIMON_STATE_IDLE:
		isOnStair = false;
		isAutoWalkOnStair = false;
		vx = 0;
		break;
	case SIMON_STATE_LEVEL_UP:
		vx = 0;
		if (isLevelUp) return;
		isLevelUp = true;
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (isAttack || isJump) break;
		nx = -1;
		if (isOnStair) {
			directionY = 1;
			GoDown();
			if (stairNx == DIRECT_RIGHT && stairNy == TYPE_ABOVE || stairNx == DIRECT_LEFT && stairNy == TYPE_BELOW)           //check the direct of stair
			{
				directionY = -1;
				GoUp();
			}
			break;
		}
		Walk();
		break;
	case SIMON_STATE_WALKING_RIGHT:
		if (isAttack || isJump) break;
		nx = 1;
		if (isOnStair) {
			directionY = -1;
			GoUp();
			if (stairNx == DIRECT_RIGHT && stairNy == TYPE_ABOVE || stairNx == DIRECT_LEFT && stairNy == TYPE_BELOW)
			{
				directionY = 1;
				GoDown();
			}
			break;
		}
		Walk();
		break;
	case SIMON_STATE_JUMP:
		if (readyToDownStair || readyToUpStair) return;
		Jump();
		break;
	case SIMON_STATE_ATTACK:
		if (readyToDownStair || readyToUpStair) return;
		Attack();
		break;
	case SIMON_STATE_SIT:
		if (readyToDownStair || readyToUpStair) return;
		Sit();
		break;
	case SIMON_STATE_STAND:
		//if (readyToDownStair || readyToUpStair) return;
		Stand();
		break;
	case SIMON_STATE_HURT:
		//On stair's logic here
		StartUntouchable();
		Hurt();
		break;
	case SIMON_STATE_SIT_AFTER_FALL:
		SitAfterFall();
		break;
	case SIMON_DROP_DOWN_AFTER_HURT_ON_STAIR:
		vy = 0.4f;
		isSit = true;
		break;
	case SIMON_STATE_GO_UP_STAIR:
		if (!isOnStair) return;
		readyToUpStair = false;
		readyToDownStair = false;
		nx = 1;
		directionY = -1;

		if (stairNx == DIRECT_LEFT && stairNy == TYPE_BELOW || stairNx ==  DIRECT_RIGHT && stairNy == TYPE_ABOVE) {
			nx = -1;
		}
		GoUp();
		break;
	case SIMON_STATE_GO_DOWN_STAIR:
		if (!isOnStair) return;
		readyToUpStair = false;
		readyToDownStair = false;
		nx = -1;
		directionY = 1;

		if (stairNx == DIRECT_LEFT && stairNy == TYPE_BELOW || stairNx == DIRECT_RIGHT && stairNy == TYPE_ABOVE) {
			nx = 1;
		}
		GoDown();
		break;
	case SIMON_STATE_AUTOWALK_ON_STAIR:
		isAutoWalkOnStair = true;
		break;
	case SIMON_STATE_IDLE_ON_STAIR:
		vy = 0;
		vx = 0;
		isAutoWalkOnStair = false;
		readyToDownStair = false;
		readyToUpStair = false;
		break;

	}
	
}
void Simon::SetAnimation()
{
	if (!isOnStair) {
		if (isDead)
			ani = DEATH_RIGHT;
		else if (isHurt)
			ani = HURT_RIGHT;
		else if (isJump && isAttack)
			ani = ATTACK_STAND_RIGHT;
		else if (isJump)
			ani = JUMP_DUCK_RIGHT;
		else if (isAttack && isSit)
			ani = ATTACK_DUCK_RIGHT;
		else if (isAttack)
			ani = ATTACK_STAND_RIGHT;
		else if (isSit)
			ani = JUMP_DUCK_RIGHT;
		else if (vx != 0)
			ani = WALK_RIGHT;
		else
			ani = IDLE_RIGHT;
	}
	else {
		if (isAttack && directionY < 0)
			ani = ATTACK_UP_RIGHT;
		else if (isAttack && directionY > 0)
			ani = ATTACK_DOWN_RIGHT;
		else if (vx != 0 && directionY < 0)
			ani = STAIR_UP_RIGHT;
		else if (vx != 0 && directionY > 0)
			ani = STAIR_DOWN_RIGHT;
		else if (directionY < 0)
			ani = IDLE_STAIR_UP_RIGHT;
		else
			ani = IDLE_STAIR_DOWN_RIGHT;
	}

	if (nx < 0) ani = static_cast<animation>(ani - 1); // because animation left always < animation right 1 index
}

void Simon::Render()
{
	SetAnimation(); // set ani variable

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	if (isLevelUp) color = D3DCOLOR_ARGB(255, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	else if (isUntouchable) color = D3DCOLOR_ARGB(255, rand() % 255 + 1, rand() % 255 + 1, 127);
	if (isAttack && !isUsingSubWeapon)
	{
		CWhip::GetInstance()->Render();
	}

	animation_set->at(ani)->Render(x, y, color);

	if (isUsingSubWeapon && (animation_set->at(ani)->GetCurrentFrame() == 2)) {
		subWeapons->SetIsThrown(true);
	}
	
	//render subweapon
	if (subWeapons != NULL && !subWeapons->isVanish && subWeapons->GetIsThrown()) {
		subWeapons->Render();
	}
	RenderBoundingBox();

	
	if (flag)
	{
		int startCol = (int)Camera::GetInstance()->GetCamX() / 32;
		int endCol = startCol + SCREEN_WIDTH / 32;
		int numOfRow = CMaps::GetInstance()->Get(1)->GetTitles().size();
		for (int i = 0; i < numOfRow; i++)
		{
			for (int j = startCol; j <= endCol; j++)
			{
				float x = TILE_SIZE * (j - startCol) + Camera::GetInstance()->GetCamX() - (int)Camera::GetInstance()->GetCamX() % 32;
				float y = TILE_SIZE * i + 151;
				//draw back part of the castle
				if (j >= 44)
					CMaps::GetInstance()->Get(1)->GetTitles()[i][j]->Draw(x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
	}
}
void Simon::Stand() {
	if (isAttack || isJump || isOnStair)   //Check neu dang nhay ma OnKeyUp DIK_DOWN va luc do dang attack hoac jump thi break.
		return;
	y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	isSit = false;
	isFall = false;
	isJump = false;
}

void Simon::Hurt() {
	startHurt = GetTickCount();
	isHurt = true;
	if (isOnStair) return;
	vx = -0.1*nx;
	vy = -0.4f;
	y -= 17;
}

void Simon::SitAfterFall() {
	startSit = GetTickCount();
	isSit = true;
	isFall = true;
	if (isOnStair) {
		isOnStair = false;
		y += 20;
		vy = 0.4f;
	}
	else {
		y += 17;
		vx = 0;
		vy = 0;
	}
	
}

void Simon::StartUntouchable() {
	isUntouchable = true;
	startUntouchable = GetTickCount();
}
void Simon::Attack()
{
	// normal attack
	if (isAttack || isDead || isHurt || isFall || isAutoWalkOnStair)
		return;
	if (!(CGame::GetInstance()->IsKeyDown(DIK_UP))) {
		vx = 0;
		isAttack = true;
		attackTime = GetTickCount();
	}
	// when using sub weapon
	if ((CGame::GetInstance()->IsKeyDown(DIK_UP) && subWeapons != NULL && isUsingSubWeapon)) return;
	else if ((CGame::GetInstance()->IsKeyDown(DIK_UP) && subWeapons != NULL && !isUsingSubWeapon && hearts > 0)) {
		hearts--;
		switch (WeaponManager::GetInstance()->GetAvailable())
		{
		case DAGGER:
			subWeapons->SetPosition(x, y + 10);
			break;
		case HOLYWATER:
			if (nx == 1)
				subWeapons->SetPosition(x + SIMON_BBOX_WIDTH - 14, y + 20);
			else if (nx == -1)
				subWeapons->SetPosition(x, y + 20);
			break;
		case STOPWATCH:
			break;
		case AXE:
			if (nx == 1)
				subWeapons->SetPosition(x + SIMON_BBOX_WIDTH - 14, y + 20);
			else if (nx == -1)
				subWeapons->SetPosition(x, y + 20);
			break;
		}
		subWeapons->nx = nx;

		isUsingSubWeapon = true;
		subWeapons->isVanish = false;

		isAttack = true;
		attackTime = GetTickCount();
	}
	else
		isUsingSubWeapon = false;

	// set animation for whip
	if (nx > 0) {
		animation_set->at(ATTACK_STAND_RIGHT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() + 2)->ResetFrame();
	}
	else {
		animation_set->at(ATTACK_STAND_LEFT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() - 1)->ResetFrame();
	}

}
void Simon::GoUp()
{
	if (isAttack) return;

	vx = nx * SIMON_ON_STAIR_SPEED_X;
	vy = directionY * SIMON_ON_STAIR_SPEED_Y;
	isAutoWalkOnStair = true;
	isOnStair = true;
	isSit = false;
	isJump = false;
}
void Simon::GoDown()
{
	if (isAttack) return;
	vx = nx * SIMON_ON_STAIR_SPEED_X;
	vy = directionY * SIMON_ON_STAIR_SPEED_Y;
	isOnStair = true;
	isAutoWalkOnStair = true;
	isSit = false;
	isJump = false;
}
void Simon::AutoWalkOnStair() {
	x += dx;
	y += dy;
	
	simonAutoWalkDistance = abs(x - backupOnStairX);

	if (simonAutoWalkDistance >= autoWalkDistance)
	{
		isAutoWalkOnStair = false;

		// cases for auto walk
		if (nx > 0)
			this->x = this->x - abs(autoWalkDistance - simonAutoWalkDistance);
		else 
			this->x = this->x + abs(autoWalkDistance - simonAutoWalkDistance);

		if (directionY > 0)
			this->y = this->y - abs(autoWalkDistance - simonAutoWalkDistance);
		else
			this->y = this->y + abs(autoWalkDistance - simonAutoWalkDistance);

		backupOnStairX = this->x;
		backupOnStairY = this->y;
		simonAutoWalkDistance = 0;
		SetState(SIMON_STATE_IDLE_ON_STAIR);
	}

	if (this->y + SIMON_BBOX_HEIGHT < aboveStairOutPoint || !readyToUpStair && this->y + SIMON_BBOX_HEIGHT > belowStairOutPoint) {
		SetState(SIMON_STATE_IDLE);
		return;
	}
}

void Simon::Sit()
{

	if (isJump || isSit || isAttack || isOnStair) return;
	if (nx > 0) {
		animation_set->at(ATTACK_DUCK_RIGHT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() + 2)->ResetFrame();
	}
	else {
		animation_set->at(ATTACK_DUCK_LEFT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() - 1)->ResetFrame();
	}
	vx = 0;
	y += SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	isJump = false;
	isSit = true;

}

void Simon::Jump()
{
	if (isJump || isSit || isAttack || isHurt || isOnStair)
		return;
	vy = -SIMON_JUMP_SPEED_Y * 1.5;
	isJump = true;
}

void Simon::Walk()
{
	if (isAttack || isSit || isJump)
		return;
	if (flag || isAutoWalking)
		vx = nx * SIMON_WALKING_SPEED / 2;
	else 	
		vx = nx * SIMON_WALKING_SPEED;
	isAttack = false;
}

void Simon::CheckLevelUpState(DWORD dt) {
	if (isLevelUp) {
		levelUpTime -= dt;
		if (levelUpTime <= 0)
			isLevelUp = false;
	}
	else {
		levelUpTime = SIMON_TIME_LEVEL_UP_WHIP;
		isLevelUp = false;
	}
}

void Simon::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!dynamic_cast<CFirePot *>(coObjects->at(i)) && !dynamic_cast<CCandle *>(coObjects->at(i)))
		{
			if (isOnStair && dynamic_cast<CBrick *>(coObjects->at(i)))
				continue;
			
			//Check collision AABB of Simon & Item
			if (dynamic_cast<Item *>(coObjects->at(i)))
			{
				Item *item = dynamic_cast<Item *>(coObjects->at(i));
				if (item->isEaten)
				{
					continue;
				}
				else
				{
					float l1, t1, r1, b1;
					float l2, t2, r2, b2;

					GetBoundingBox(l1, t1, r1, b1);
					item->GetBoundingBox(l2, t2, r2, b2);

					if (!(r1 < l2 || l1 > r2 || t1 > b2|| b1 < t2))
					{
						item->BeingProcessed();
						DebugOut(L"[Info] subWeapons: %d\n", subWeapons);
						continue;
					}
				}
			}
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
			if (e->t > 0 && e->t <= 1.0f)
				coEvents.push_back(e);
			else
				delete e;
			
		}
		
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void Simon::Update(DWORD dt, vector< LPGAMEOBJECT>*coObjects)
{
	CGameObject::Update(dt);
	if (!canGoUpStair && !canGoDownStair && !isOnStair)
		vy += SIMON_GRAVITY * dt;

	if (isOnStair && isAutoWalkOnStair) {
		AutoWalkOnStair();
	}
	if (subWeapons != NULL) {
		if (subWeapons->isVanish)
			isUsingSubWeapon = false;
		else
			subWeapons->Update(dt, coObjects);
	}
	if (isDoubleShot && GetTickCount64()-buffTime > 6000)
	{
		isDoubleShot = false;
	}
	//Ensure render time >= render attack time
	if (isAttack == true && GetTickCount() - attackTime > 350) {
		isAttack = false;
		CWhip::GetInstance()->Update(dt, coObjects);
		vx = 0;
		if (nx > 0) {
			animation_set->at(ATTACK_DUCK_RIGHT)->ResetFrame();
			animation_set->at(ATTACK_STAND_RIGHT)->ResetFrame();
			CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() + 2)->ResetFrame();
		}
		else {
			animation_set->at(ATTACK_DUCK_LEFT)->ResetFrame();
			animation_set->at(ATTACK_STAND_LEFT)->ResetFrame();
			CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() - 1)->ResetFrame();
		}
		if (isSit && !CGame::GetInstance()->IsKeyDown(DIK_DOWN))  //check neu dang danh luc ngoi thi danh het roi dung hoac ngoi tiep
		{
			y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
			isSit = false;
		}
	}

	//auto move simon and camera when simon hit the door in playscene 2 
	for (int i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<CDoor*>(coObjects->at(i))) {
			CDoor *door = dynamic_cast<CDoor *>(coObjects->at(i));
			if (door->GetId() == doorId && isAutoWalking) {
				if (door->IsOpened() && (this->x < SIMON_AUTO_GO_THROUGH_FIRST_DOOR || this->x < SIMON_AUTO_GO_THROUGH_SECOND_DOOR))
					Walk();
				else
					SetState(SIMON_STATE_IDLE);
			}
		}
	}



	//when simon level up whip
	CheckLevelUpState(dt);
	if (state == SIMON_STATE_DIE && GetTickCount64() - dieTime > 600)
	{
		ResetSimon();
		dieTime = 0;
	}

	//Update when Simon is hurt
	if (isFall && (GetTickCount() - startSit > SIMON_SIT_AFTER_FALL_TIME))
	{
		startSit = 0;

		if (health <= 0) {
			SetState(SIMON_STATE_DIE);
			dieTime = GetTickCount64();
		}
		else 
			SetState(SIMON_STATE_STAND);
	}
	if (isUntouchable && (GetTickCount() - startUntouchable > SIMON_UNTOUCHABLE_TIME))
	{
		startUntouchable = 0;
		isUntouchable = false;

	} 
	//hurt on stair
	if (isOnStair && isHurt && (GetTickCount() - startHurt > SIMON_HURT_TIME))
	{

		isHurt = false;
		isJump = false;
		if (health <= 0) {

			SetState(SIMON_STATE_SIT_AFTER_FALL);
		}
		else 
			SetState(SIMON_STATE_IDLE_ON_STAIR);
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> coObjectsWhenDie;

	coEvents.clear();

	// turn off collision when simon die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	else {
		//to make sure when simon die he just can collide with Brick
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CBrick *>(coObjects->at(i)))
				coObjectsWhenDie.push_back(coObjects->at(i));
		}
		CalcPotentialCollisions(&coObjectsWhenDie, coEvents);
	}

	/*if (CGame::GetInstance()->GetCurrentSceneID() == 3 && y < 120)
		CGame::GetInstance()->SwitchScene(2);*/

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{

		x += dx;
		y += dy;

		if (nx != 0 && (readyToDownStair || readyToUpStair) && GetTickCount() - time >= 150)
		{
			StopAtFirstStepOnStair();
		}

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		if (!isHurt) {
			if (nx != 0 && state != SIMON_STATE_AUTO) {
				vx = 0;
			}
			if (ny != 0) {
				vy = 0;
			}
		}
		

		if (CGame::GetInstance()->GetCurrentSceneID() == 1)
		{
			if (x >= SIMON_AUTO_GO_BACK_POSITION_X && flag == false)
			{
				SetState(SIMON_STATE_AUTO);
			}
			else if (x >= SIMON_AUTO_GO_AHEAD_POSITION_X && x < SIMON_AUTO_GO_BACK_POSITION_X)
			{
				SetState(SIMON_STATE_AUTO);
			}
		}

		if (CGame::GetInstance()->GetCurrentSceneID() == 2)
		{
			for (int i = 0; i < TriggerStairs::GetInstance()->GetTriggerStairs().size(); i++)
			{
				if (triggerStairs->Get(i)->IsContainSimon())
				{
					SetReadyToGoStair(i);
					if (readyToUpStair || readyToDownStair)
					{
						SetSimonAutoActionToGoStair(i);
					}
				}
			}
		}
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			// if Item
			if (dynamic_cast<Item *>(e->obj))
			{
				Item *item = dynamic_cast<Item *>(e->obj);

				item->BeingProcessed();

			}
			else if (dynamic_cast<CEnemy *>(e->obj))
			{
				if (dynamic_cast<CBat *>(e->obj))
					e->obj->SetState(ENEMY_STATE_DIE);

				if (!isUntouchable) {
					health -= 2;
					if (e->obj->nx == nx) {

						this->nx = -e->obj->nx;
					}
					
					SetState(SIMON_STATE_HURT);
				}
				else {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				if(startBlinkEffect == 0)
					startBlinkEffect = GetTickCount();
				if (GetTickCount() - startBlinkEffect >= 500)
				{
					BlinkEffect::GetInstance()->SetIsActive(false);

					CPortal *p = dynamic_cast<CPortal *>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
					flag = false;
					SetState(SIMON_STATE_IDLE);
				}
				else
					BlinkEffect::GetInstance()->SetIsActive(true);		
			}
			else if (dynamic_cast<CBrick *>(e->obj))
			{
				if (isOnStair)
					continue;
				if (e->ny < 0)
				{
					if (isHurt && (GetTickCount() - startHurt > SIMON_HURT_TIME))
					{

							isHurt = false;
							isJump = false;
							SetState(SIMON_STATE_SIT_AFTER_FALL);
					}
					if (isJump)
					{
						y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
						isJump = false;
					}
				}
			}
			else if (dynamic_cast<CWaterSurface *>(e->obj))
			{
				//effect
				x += dx;
				y += dy;
				health = 0;
			}
			else if (dynamic_cast<CSmallBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					if (isJump == true)
					{
						y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
						isJump = false;
					}
				}
			}
			else if (dynamic_cast<CDoor *>(e->obj))
			{
				CDoor *door = dynamic_cast<CDoor *>(e->obj);
				if (!door->IsActive() && this->x - door->GetPostionX() < 0)
				{
					doorId = door->GetId();
					SetState(SIMON_STATE_IDLE);
					isAutoWalking = true;
					door->SetActive(true);
					Camera::GetInstance()->SetIsAuto(true);
				}
				if (door->IsActive())
				{
					x += dx;
				}
			}
			
			else if (dynamic_cast<CSmallBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					if (isJump == true)
					{
						y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
						isJump = false;
					}
				}
			}
			else if (dynamic_cast<CBrokenBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					if (isHurt && (GetTickCount() - startHurt > SIMON_HURT_TIME))
					{

						isHurt = false;
						isJump = false;
						SetState(SIMON_STATE_SIT_AFTER_FALL);
					}
					if (isJump)
					{
						y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
						isJump = false;
					}
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CDoor *>(e->obj))
			{
				CDoor *door = dynamic_cast<CDoor *>(e->obj);
				if (!door->IsActive() && this->x - door->GetPostionX() < 0)
				{
					doorId = door->GetId();
					SetState(SIMON_STATE_IDLE);
					isAutoWalking = true;
					door->SetActive(true);
					Camera::GetInstance()->SetIsAuto(true);
				}
				else if (door->IsActive())
				{
					x += dx;
				}
			}
		}
	}

	CWhip::GetInstance()->SetDirect(nx);
	CWhip::GetInstance()->Update(dt, coObjects);
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Simon::ResetSimon()
{
	isDead = false;
	nx = 1;
	cam=Camera::GetInstance();
	
	SetState(SIMON_STATE_IDLE);
	switch (area->GetInstance()->GetAreaID())
	{
	case 21:
		game->GetInstance()->SwitchScene(2);
		SetPosition(50, 0);
		cam->SetCamPos(0, 0);
		break;
	case 22:
		game->GetInstance()->SwitchScene(2);
		SetPosition(RESPAWN_POS_22, 0);
		cam->SetCamPos(LIMIT_LEFT_CAM_22, 0);
		break;
	case 23:
		game->GetInstance()->SwitchScene(2);
		SetPosition(RESPAWN_POS_23, 0);
		cam->SetCamPos(LIMIT_LEFT_CAM_23, 0);
		break;
	default:
		break;
	}
}

void Simon::StopAtFirstStepOnStair() {
	backupOnStairX = this->x;
	backupOnStairY = this->y;
	vx = 0;
	vy = 0;
	readyToDownStair = false;
	readyToUpStair = false;
	canGoDownStair = false;
	canGoUpStair = false;
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 12;
	top = y;
	right = x + SIMON_BBOX_WIDTH - 10;
	bottom = y + SIMON_BBOX_HEIGHT;

	if (isDead) {
		left -= 12;
		right += 12;
		top += 40;
		bottom += 2;
	}
	if (isJump)
	{
		if (isHurt) return;
		bottom -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
	if (isSit)
	{
		if (isHurt) return;
		bottom -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}
void Simon::SetReadyToGoStair(int i)
{
	if (triggerStairs->Get(i)->GetType() == TYPE_BELOW && CGame::GetInstance()->IsKeyDown(DIK_UP))
	{
		readyToUpStair = true;
		readyToDownStair = false;
	}
	else if (triggerStairs->Get(i)->GetType() == TYPE_ABOVE && CGame::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		readyToDownStair = true;
		readyToUpStair = false;
	}
}

void Simon::SetSimonAutoActionToGoStair(int i)
{
	if (triggerStairs->Get(i)->GetDirect() == DIRECT_RIGHT)
	{
		if (x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint())
		{
			this->nx = 1;
			Walk();
			if (x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() && x + 12 >= triggerStairs->Get(i)->GetStandingPoint() - 43)
			{
				if (triggerStairs->Get(i)->GetType() == TYPE_BELOW)
				{
					//for sure Simon only stand at 1 point before going up
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 38)
						x = triggerStairs->Get(i)->GetStandingPoint() - 50;
					GoUp1Step();
				}
				else
				{
					//for sure Simon only stand at 1 point before going down
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 45)
						x = triggerStairs->Get(i)->GetStandingPoint() - 57;
					GoDown1Step();
				}
			}
		}
		else
		{
			this->nx = -1;
			Walk();
			if (x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() && x + 12 >= triggerStairs->Get(i)->GetStandingPoint() - 43)
			{
				if (triggerStairs->Get(i)->GetType() == TYPE_BELOW)
				{
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 38)
						x = triggerStairs->Get(i)->GetStandingPoint() - 50;
					GoUp1Step();
				}
				else
				{
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 45)
						x = triggerStairs->Get(i)->GetStandingPoint() - 57;
					GoDown1Step();
				}
			}
		}
	}
	else
	{
		if (x + 12 < triggerStairs->Get(i)->GetStandingPoint())
		{
			this->nx = 1;
			Walk();
			if (x + 12 >= triggerStairs->Get(i)->GetStandingPoint() && x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() + 43)
			{
				if (triggerStairs->Get(i)->GetType() == TYPE_BELOW)
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 36)
						x = triggerStairs->Get(i)->GetStandingPoint() - 14;
					GoUp1Step();
				}
				else
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 44)
						x = triggerStairs->Get(i)->GetStandingPoint() - 6;
					GoDown1Step();
				}
			}
		}
		else
		{
			this->nx = -1;
			Walk();
			if (x + 12 >= triggerStairs->Get(i)->GetStandingPoint() && x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() + 43)
			{
				if (triggerStairs->Get(i)->GetType() == TYPE_BELOW)
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 36)
						x = triggerStairs->Get(i)->GetStandingPoint() - 14;
					GoUp1Step();
				}
				else
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 44)
						x = triggerStairs->Get(i)->GetStandingPoint() - 6;
					GoDown1Step();
				}
			}
		}
	}
	stairNx = triggerStairs->Get(i)->GetDirect();
	stairNy = triggerStairs->Get(i)->GetType();
	SetStairOutPoint(i);
	time = GetTickCount();
}

void Simon::GoUp1Step()
{
	isOnStair = true;
	canGoUpStair = true;
	canGoDownStair = false;
	vy = -0.1;
	directionY = -1;
	if (nx == 1)
		vx = 0.1;
	else
		vx = -0.1;

}

void Simon::GoDown1Step()
{
	isOnStair = true;
	canGoDownStair = true;
	canGoUpStair = false;
	vy = 0.1;
	directionY = 1;
	if (nx == 1)
		vx = 0.1;
	else
		vx = -0.1;
}
void Simon::SetStairOutPoint(int i)
{
	if (i % 2 == 0)
	{
		if (triggerStairs->Get(i)->GetType() == TYPE_BELOW)
		{
			belowStairOutPoint = triggerStairs->Get(i)->GetOutPoint();
			aboveStairOutPoint = triggerStairs->Get(i + 1)->GetOutPoint();
		}
		else
		{
			aboveStairOutPoint = triggerStairs->Get(i)->GetOutPoint();
			belowStairOutPoint = triggerStairs->Get(i + 1)->GetOutPoint();
		}
	}
	else
	{
		if (triggerStairs->Get(i)->GetType() == TYPE_BELOW)
		{
			belowStairOutPoint = triggerStairs->Get(i)->GetOutPoint();
			aboveStairOutPoint = triggerStairs->Get(i - 1)->GetOutPoint();
		}
		else
		{
			aboveStairOutPoint = triggerStairs->Get(i)->GetOutPoint();
			belowStairOutPoint = triggerStairs->Get(i - 1)->GetOutPoint();
		}
	}
}