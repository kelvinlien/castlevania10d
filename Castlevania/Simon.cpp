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
	case SIMON_STATE_IDLE:
		 vx = 0;
		 break;
	case SIMON_STATE_LEVEL_UP:
		vx = 0;
		if (isLevelUp) return;
		//Để cây roi level up ở đây
		isLevelUp = true;
		break;
	case SIMON_STATE_WALKING_LEFT:
		nx = -1;
		Walk();
		break;
	case SIMON_STATE_WALKING_RIGHT:
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
		y -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
		isSit = false;
		if (isAttack)
			isAttack = false;
		break;
	}

}
void Simon::SetAnimation()
{
	if (state == SIMON_STATE_DIE)
		return;
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

	if (isAttack)
	{
		CWhip::GetInstance()->Render();
	}

	animation_set->at(ani)->Render(x, y, color);
	RenderBoundingBox(x,y);	
}

void Simon::Attack ()
{
	if (isAttack)
		return;
	if (nx > 0) {
		animation_set->at(ATTACK_STAND_RIGHT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(WHIP_ANI_LV1_RIGHT)->ResetFrame();
	}
	else {
		animation_set->at(ATTACK_STAND_LEFT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(WHIP_ANI_LV1_LEFT)->ResetFrame();
	}
	vx = 0;
	isAttack = true;
	attackTime = GetTickCount();
}

void Simon::Sit()
{
	
	if (isSit) return;
	if (nx > 0) {
		animation_set->at(ATTACK_DUCK_RIGHT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(WHIP_ANI_LV1_RIGHT)->ResetFrame();
	}
	else {
		animation_set->at(ATTACK_DUCK_LEFT)->ResetFrame();
		CWhip::GetInstance()->animation_set->at(WHIP_ANI_LV1_LEFT)->ResetFrame();
	}
	vx = 0;
	y += SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	isJump = false;
	isSit = true;
}

void Simon::Jump()
{
	if (isJump || isSit)
		return;
	vy = -SIMON_JUMP_SPEED_Y;
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
void Simon::Update(DWORD dt, vector< LPGAMEOBJECT>*coObjects)
{
	CGameObject::Update(dt);
	vy += SIMON_GRAVITY * dt;

	//Ensure render time >= render attack time
	if (isAttack == true && GetTickCount() - attackTime > 350) {
		isAttack = false;
		CWhip::GetInstance()->Update(dt, coObjects);
		vx = 0;
		if (nx > 0) {
			animation_set->at(ATTACK_DUCK_RIGHT)->ResetFrame();
			animation_set->at(ATTACK_STAND_RIGHT)->ResetFrame();
			CWhip::GetInstance()->animation_set->at(WHIP_ANI_LV1_RIGHT)->ResetFrame();
		}
		else {
			animation_set->at(ATTACK_DUCK_LEFT)->ResetFrame();
			animation_set->at(ATTACK_STAND_LEFT)->ResetFrame();
			CWhip::GetInstance()->animation_set->at(WHIP_ANI_LV1_LEFT)->ResetFrame();
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

		if (nx != 0) vx = 0;
		if (ny != 0) {
			vy = 0;
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
			} // if Goomba
			else if (dynamic_cast<Item *>(e->obj)) {
				Item *item = dynamic_cast<Item *>(e->obj);
				item->isVanish = true;

				if (item->GetType() == WHIP_RED)
						this->SetState(SIMON_STATE_LEVEL_UP);

				else {
					map<int, int>::iterator temp; // element tạm để lưu trữ giá trị map

					if (item->GetType() == DAGGER) {
						temp = weapons.find(DAGGER);
						if (temp != weapons.end()) 
							temp->second += 1; //cộng thêm 1 cái dagger
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

	CWhip::GetInstance()->SetTrend(nx);
	CWhip::GetInstance()->Update(dt, coObjects);
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}
void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x+12;
	top = y;
	right = x + SIMON_BBOX_WIDTH-10;
	bottom = y + SIMON_BBOX_HEIGHT;
	if (isJump)
	{
		if(isAttack)
			bottom = y + SIMON_BBOX_HEIGHT;
		else
			bottom -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
	if (isSit)
	{
		bottom -= SIMON_BBOX_HEIGHT - SIMON_SIT_BBOX_HEIGHT;
	}
}