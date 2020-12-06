
#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Goomba.h"
#include "Brick.h"
#include "Portal.h"
#include"Game.h"
#include "Item.h"
#include "Whip.h"
#include "Textures.h"
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
	case SIMON_STATE_IDLE:
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
		//if(onStair) {
		//	if (stairNx > 0)             //check the direct of stair
		//		GoDown();
		//	else
		//		GoUp();
		//	break;
		//}
		Walk();
		break;
	case SIMON_STATE_WALKING_RIGHT:
		if (isAttack || isJump) break;
		nx = 1;
		Walk();
		break;
	case SIMON_STATE_JUMP:
		Jump();
		break;
	case SIMON_STATE_ATTACK:
		Attack();
		break;
	case SIMON_STATE_SIT:
		Sit();
		break;
	case SIMON_STATE_STAND:
		Stand();
		break;
	}

}
void Simon::SetAnimation()
{
	if (state == SIMON_STATE_DIE)
		return;
	else if (state == SIMON_STATE_GO_UP_STAIR)
		if (nx > 0)
			ani = STAIR_UP_RIGHT;
		else
			ani = STAIR_UP_LEFT;
	else if (state == SIMON_STATE_GO_DOWN_STAIR)
		if (nx > 0)
			ani = STAIR_DOWN_RIGHT;
		else
			ani = STAIR_DOWN_LEFT;
	/*else if (state == SIMON_STATE_IDLE_ON_STAIR)
		if (nx > 0)
			if (directionY > 0)
				ani = IDLE_STAIR_DOWN_RIGHT;
			else
				ani = IDLE_STAIR_UP_RIGHT;
		else
			if (directionY > 0)
				ani = IDLE_STAIR_DOWN_LEFT;
			else
				ani = IDLE_STAIR_UP_LEFT;*/
	else if (vx == 0)
	{

		if (isJump) {
			if (isAttack) {
				if (nx > 0)
					ani = ATTACK_STAND_RIGHT;
				else
					ani = ATTACK_STAND_LEFT;
			}
			else {
				if (nx > 0)
					ani = JUMP_DUCK_RIGHT;
				else
					ani = JUMP_DUCK_LEFT;
			}
		}
		else
		{
			if (onStair)
			{
				if (directionY < 0)
				{
					if (isAttack) {
						if (isSit)
						{
							if (nx > 0)
								ani = ATTACK_DUCK_RIGHT;
							else
								ani = ATTACK_DUCK_LEFT;
						}
						else {
							if (nx > 0)
								ani = ATTACK_STAND_RIGHT;
							else
								ani = ATTACK_STAND_LEFT;
						}
					}
					else
					{
						if (nx > 0)
							ani = IDLE_STAIR_UP_RIGHT;
						else
							ani = IDLE_STAIR_UP_LEFT;
					}
				}
				else
				{
					if (isAttack) {
						if (isSit)
						{
							if (nx > 0)
								ani = ATTACK_DUCK_RIGHT;
							else
								ani = ATTACK_DUCK_LEFT;
						}
						else {
							if (nx > 0)
								ani = ATTACK_STAND_RIGHT;
							else
								ani = ATTACK_STAND_LEFT;
						}
					}
					else
					{
						if (nx > 0)
							ani = IDLE_STAIR_DOWN_RIGHT;
						else
							ani = IDLE_STAIR_DOWN_LEFT;
					}
				}
			}
			else
			{

				if (isSit)
				{
					if (nx > 0)
						ani = JUMP_DUCK_RIGHT;
					else
						ani = JUMP_DUCK_LEFT;
				}
				else {
					if (nx > 0)
						ani = IDLE_RIGHT;
					else
						ani = IDLE_LEFT;
				}
			}
		}
	}
	else if (vx != 0)
	{
		if (isJump) {
			if (nx > 0)
				ani = JUMP_DUCK_RIGHT;
			else
				ani = JUMP_DUCK_LEFT;
		}
		else
		{
			if (nx > 0)
				ani = WALK_RIGHT;
			else
				ani = WALK_LEFT;
		}
	}
}

void Simon::Render()
{
	SetAnimation(); // set ani variable


	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	if (isLevelUp) color = D3DCOLOR_ARGB(255, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);

	if (isAttack && !isUsingSubWeapon)
	{
		CWhip::GetInstance()->Render();
	}

	animation_set->at(ani)->Render(x, y, color);
	//render subweapon
	if (subWeapons != NULL  && !subWeapons ->isVanish) 
		subWeapons->Render();
	RenderBoundingBox();
}
void Simon::Stand(){
	if (isAttack || isJump)   //Check neu dang nhay ma OnKeyUp DIK_DOWN va luc do dang attack hoac jump thi break.
		return;
	y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	isSit = false;
}
void Simon::Attack()
{
	// normal attack
	if (isAttack)
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
		subWeapons->SetPosition(x, y + 10);
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

void Simon::Sit()
{
	
	if (isJump || isSit || isAttack) return;
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
	if (isJump || isSit || isAttack)
		return;
	vy = -SIMON_JUMP_SPEED_Y * 1.5;
	isJump = true;
}

void Simon::Walk()
{
	if (isAttack || isSit || isJump)
		return;
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
		if (!dynamic_cast<CFirePot *>(coObjects->at(i)))
		{
			//Check collision AABB of Simon & Item
			if (dynamic_cast<Item *>(coObjects->at(i)))
			{
				Item *item = dynamic_cast<Item *>(coObjects->at(i));
				float l1, t1, r1, b1;
				float l2, t2, r2, b2;

				GetBoundingBox(l1, t1, r1, b1);
				item->GetBoundingBox(l2, t2, r2, b2);

				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
				{
					item->isVanish = true;
					if (item->GetType() == ITEM_WHIP_RED) {
						this->SetState(SIMON_STATE_LEVEL_UP);
						CWhip::GetInstance()->LevelUp();
					}
					else {

						if (item->GetType() == ITEM_DAGGER) {
							subWeapons = WeaponManager::GetInstance()->createWeapon(DAGGER);
						}
						else if (item->GetType() == ITEM_BIG_HEART) {
							hearts += 5;
						}
					}
					continue;
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
	if(!canGoUpStair && !canGoDownStair)
		vy += SIMON_GRAVITY * dt;
	
	if (subWeapons != NULL ) {
		if (subWeapons->isVanish) 
			isUsingSubWeapon = false;
		else 
			subWeapons->Update(dt, coObjects);
	}

	//Ensure render time >= render attack time
	if (isAttack == true && GetTickCount() - attackTime > 350) {
		isAttack = false;
		CWhip::GetInstance()->Update(dt, coObjects);
		vx = 0;
		if (nx > 0) {
			animation_set->at(ATTACK_DUCK_RIGHT)->ResetFrame();
			animation_set->at(ATTACK_STAND_RIGHT)->ResetFrame();
			CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() +2)->ResetFrame();
		}
		else {
			animation_set->at(ATTACK_DUCK_LEFT)->ResetFrame();
			animation_set->at(ATTACK_STAND_LEFT)->ResetFrame();
			CWhip::GetInstance()->animation_set->at(CWhip::GetInstance()->GetLevel() -1)->ResetFrame();
		}
		if (isSit && !CGame::GetInstance()->IsKeyDown(DIK_DOWN))  //check neu dang danh luc ngoi thi danh het roi dung hoac ngoi tiep
		{
				y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
				isSit = false;
		}
	}

	//when simon level up whip
	CheckLevelUpState(dt);
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when simon die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		
		x += dx;
		y += dy;

		if (nx != 0 && /*(state == SIMON_STATE_GO_UP_STAIR || state == SIMON_STATE_GO_DOWN_STAIR)*/onStair && GetTickCount() - time >= 150)
		{
			vx = 0;
			vy = 0;
			SetState(SIMON_STATE_IDLE_ON_STAIR);
		}

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

		if (nx != 0)
		{
			//if (!canGoDownStair)
				vx = 0;
		}
		if (ny != 0) {
			//if (!canGoDownStair)
				vy = 0;
		}

		if (CGame::GetInstance()->GetCurrentSceneID() == 2)
		{
			for (int i = 0; i < 10; i++)
			{
				if (triggerStairs->Get(i)->IsContainSimon())
				{
					SetReadyToGoStair(i);
					if (readyToUpStair || readyToDownStair)
					{
						SetSimonAutoActionToGoStair(i);
						/*if (canGoUpStair || canGoDownStair)
							onStair = true;
						else
							onStair = false;*/
					}
				}
			}
		}
		DebugOut(L"[CHECK] Simon left: %f\n", x + 12.0f);
		DebugOut(L"[CHECK] Simon y: %f\n", y);
		DebugOut(L"[CHECK] Simon right: %f\n", x + SIMON_BBOX_WIDTH - 10.0f);
		DebugOut(L"[CHECK] Simon bottom: %f\n", y + SIMON_BBOX_HEIGHT);
		DebugOut(L"[CHECK] Simon vx: %f\n", this->vx);
		DebugOut(L"[CHECK] Simon vy: %f\n", this->vy);
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
						SetState(SIMON_STATE_IDLE);
				}
			} // if Item
			else if (dynamic_cast<Item *>(e->obj)) 
			{
				Item *item = dynamic_cast<Item *>(e->obj);
				item->isVanish = true;
				if (item->GetType() == ITEM_WHIP_RED) {
					this->SetState(SIMON_STATE_LEVEL_UP);
					CWhip::GetInstance()->LevelUp();
				}
				else {

					if (item->GetType() == ITEM_DAGGER) {
						subWeapons = WeaponManager::GetInstance()->createWeapon(DAGGER);
					}
					else if (item->GetType() == ITEM_BIG_HEART) {
						hearts += 5;
					}
				}
			}
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CBrick *>(e->obj))
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
		}
	}

	CWhip::GetInstance()->SetDirect(nx);
	CWhip::GetInstance()->Update(dt, coObjects);
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}
void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 12;
	top = y;
	right = x + SIMON_BBOX_WIDTH - 10;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isJump)
	{
		bottom -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
	if (isSit)
	{
		bottom -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}

void Simon::SetReadyToGoStair(int i)
{
	if (triggerStairs->Get(i)->GetType() == 0 && CGame::GetInstance()->IsKeyDown(DIK_UP))
	{
		readyToUpStair = true;
		readyToDownStair = false;
	}
	else if (triggerStairs->Get(i)->GetType() == 1 && CGame::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		readyToDownStair = true;
		readyToUpStair = false;
	}
}

void Simon::SetSimonAutoActionToGoStair(int i)
{
	if (triggerStairs->Get(i)->GetDirect() == 1)
	{
		if (x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint())
		{
			this->nx = 1;
			Walk();
			if (x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() && x + 12 >= triggerStairs->Get(i)->GetStandingPoint() - 43)
			{
				if (triggerStairs->Get(i)->GetType() == 0)
				{
					//for sure Simon only stand at 1 point before going up
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 38)
						x = triggerStairs->Get(i)->GetStandingPoint() - 50;
					GoUp();
				}
				else
				{
					//for sure Simon only stand at 1 point before going down
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 45)
						x = triggerStairs->Get(i)->GetStandingPoint() - 57;
					GoDown();
				}
				stairNx = triggerStairs->Get(i)->GetDirect();
			}
			
		}
		else
		{
			this->nx = -1;
			Walk();
			if (x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() && x + 12 >= triggerStairs->Get(i)->GetStandingPoint() - 43)
			{
				if (triggerStairs->Get(i)->GetType() == 0)
				{
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 38)
						x = triggerStairs->Get(i)->GetStandingPoint() - 50;
					GoUp();
				}
				else
				{
					if (x + 12 != triggerStairs->Get(i)->GetStandingPoint() - 45)
						x = triggerStairs->Get(i)->GetStandingPoint() - 57;
					GoDown();
				}
				stairNx = triggerStairs->Get(i)->GetDirect();
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
				if (triggerStairs->Get(i)->GetType() == 0)
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 36)
						x = triggerStairs->Get(i)->GetStandingPoint() - 14;
					GoUp();
				}
				else
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 44)
						x = triggerStairs->Get(i)->GetStandingPoint() - 6;
					GoDown();
				}
				stairNx = triggerStairs->Get(i)->GetDirect();
			}
		}
		else
		{
			this->nx = -1;
			Walk();
			if (x + 12 >= triggerStairs->Get(i)->GetStandingPoint() && x + SIMON_BBOX_WIDTH - 10 < triggerStairs->Get(i)->GetStandingPoint() + 43)
			{
				if (triggerStairs->Get(i)->GetType() == 0)
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 36)
						x = triggerStairs->Get(i)->GetStandingPoint() - 14;
					GoUp();
				}
				else
				{
					if (x + SIMON_BBOX_WIDTH - 10 != triggerStairs->Get(i)->GetStandingPoint() + 44)
						x = triggerStairs->Get(i)->GetStandingPoint() - 6;
					GoDown();
				}
				stairNx = triggerStairs->Get(i)->GetDirect();
			}
		}
	}
	time = GetTickCount();
}

void Simon::GoUp()
{
	onStair = true;
	canGoUpStair = true;
	canGoDownStair = false;
	SetState(SIMON_STATE_GO_UP_STAIR);
	vy = -0.1;
	directionY = -1;
	if (nx == 1)
		vx = 0.1;
	else
		vx = -0.1;
}

void Simon::GoDown()
{
	onStair = true;
	canGoDownStair = true;
	canGoUpStair = false;
	SetState(SIMON_STATE_GO_DOWN_STAIR);
	vy = 0.1;
	directionY = 1;
	if (nx == 1)
		vx = 0.1;
	else
		vx = -0.1;
}