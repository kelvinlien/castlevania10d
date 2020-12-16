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
#include "SmallBrick.h"
#include "WaterSurface.h"

Simon* Simon::__instance = NULL;

Simon* Simon::GetInstance()
{
	if (__instance == NULL) __instance = new Simon();
	return __instance;
}
Simon::Simon() : CGameObject()
{
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
		y -= 30;
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
			vx = 0;
			break;
	case SIMON_STATE_LEVEL_UP:
		vx = 0;
		if (isLevelUp) return;
		isLevelUp = true;
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (isAttack) break;
		nx = -1;
		Walk();
		break;
	case SIMON_STATE_WALKING_RIGHT:
		if (isAttack) break;
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
	case SIMON_STATE_HURT:
		//On stair's logic here
		StartUntouchable();
		Hurt();
		break;
	case SIMON_STATE_SIT_AFTER_FALL:
		SitAfterFall();
		break;
	}
	
}
void Simon::SetAnimation()
{
//	if (state == SIMON_STATE_DIE) return;
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
	if (subWeapons != NULL && !subWeapons->isVanish) {
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
void Simon::Stand(){
	if (isAttack || isJump)   //Check neu dang nhay ma OnKeyUp DIK_DOWN va luc do dang attack hoac jump thi break.
		return;
	y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	isSit = false;
	isFall = false;
	isJump = false;
}

void Simon::Hurt() {
	startHurt = GetTickCount();
	vx = -0.1*nx;
	vy = -0.4f;
	isHurt = true;
	y -= 17;
}
void Simon::SitAfterFall() {
	startSit = GetTickCount();
	isSit = true; 
	isFall = true;
	y += 17;
	vx = 0;
	vy = 0;
}
void Simon::StartUntouchable() {
	isUntouchable = true;
	startUntouchable = GetTickCount();
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
			subWeapons->SetPosition(x - 15, y + 15);
			subWeapons->nx = nx;
			isAttack = true;
			attackTime = GetTickCount();
			isUsingSubWeapon = true;
			subWeapons->isVanish = false;
			DebugOut(L"[INFO] 3\n");
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
	if (isJump || isSit || isAttack || isHurt)
		return;
	vy = -SIMON_JUMP_SPEED_Y;
	isJump = true;
}

void Simon::Walk()
{
	if (isAttack || isSit || isJump)
		return;
	if (flag)
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

					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
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

	//Update when Simon is hurt
	if (isFall && (GetTickCount() - startSit > SIMON_SIT_AFTER_FALL_TIME))
	{
		startSit = 0;

		if (health <= 0) {
			SetState(SIMON_STATE_DIE);
		}
		else
			SetState(SIMON_STATE_STAND);
	}
	if (isUntouchable && (GetTickCount() - startUntouchable > SIMON_UNTOUCHABLE_TIME))
	{
		startUntouchable = 0;
		isUntouchable = false;

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
				flag = true;
				SetState(SIMON_STATE_AUTO);
			}
		}

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
				item->BeingProcessed();

			}
			else if (dynamic_cast<CEnemy *>(e->obj))
			{
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
			else if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					if (isHurt && (GetTickCount() - startHurt > SIMON_HURT_TIME))
					{

							isHurt = false;
							isJump = false;
							//y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
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
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
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
