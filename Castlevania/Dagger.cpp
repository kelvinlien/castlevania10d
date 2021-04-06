#include "Dagger.h"
#include "Ghost.h"
#include "Panther.h"
#include "BrokenBrick.h"
#include "Bat.h"
#include "Fishman.h"
#include "Boss.h"
Dagger::Dagger()
{
	isVanish = true;
}
void Dagger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}

void Dagger::SetAnimation() {
	if (nx > 0)
		ani = CWeapon::animation_set->at(ANI_DAGGER_RIGHT);
	else
		ani = CWeapon::animation_set->at(ANI_DAGGER_LEFT);
}

void Dagger::Render() {
	if (!isVanish && GetIsThrown()) {
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}



void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
	CGameObject::Update(dt, coObjects);
	vector<LPGAMEOBJECT> coObjectsDagger;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (!dynamic_cast<Simon*> (coObjects->at(i)))
			coObjectsDagger.push_back(coObjects->at(i));
	}
	if (!GetIsThrown()) return;
	vx = nx * DAGGER_VX;
	coEvents.clear();

	CalcPotentialCollisions(&coObjectsDagger, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (x < Camera::GetInstance()->GetCamX() ||
			x > Camera::GetInstance()->GetCamX() + SCREEN_WIDTH) {
			isVanish = true;
			SetIsThrown(false);
		}
		float l1, t1, r1, b1;
		float l2, t2, r2, b2;
		GetBoundingBox(l1, t1, r1, b1);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CFirePot*>(coObjects->at(i)))
			{
				CFirePot* e = dynamic_cast<CFirePot*>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(FIREPOT_STATE_BREAK);
			}
			else if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy* e = NULL;

				switch (dynamic_cast<CEnemy*>(coObjects->at(i))->GetType())
				{
				case ENEMY_TYPE_GHOST:
					e = dynamic_cast<CGhost*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_PANTHER:
					e = dynamic_cast<CPanther*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_BAT:
					e = dynamic_cast<CBat*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_FISHMAN:
					e = dynamic_cast<CFishman*>(coObjects->at(i));
					break;
				case ENEMY_TYPE_BOSS:
					e = dynamic_cast<CBoss*>(coObjects->at(i));
				default:
					break;
				}
				if (e != NULL) {
					e->GetBoundingBox(l2, t2, r2, b2);
					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
						e->SetState(ENEMY_STATE_DIE);
				}
				else if (dynamic_cast<CBrokenBrick*>(coObjects->at(i)))
				{
					CBrokenBrick* e = dynamic_cast<CBrokenBrick*>(coObjects->at(i));
					e->GetBoundingBox(l2, t2, r2, b2);
					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
						e->SetState(STATE_BRICK_BREAK);
				}
			}
			else if (dynamic_cast<CCandle*>(coObjects->at(i)))
			{
				CCandle* e = dynamic_cast<CCandle*>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(CANDLE_STATE_BREAK);
			}
			else if (dynamic_cast<CBrokenBrick*>(coObjects->at(i)))
			{
				CBrokenBrick* e = dynamic_cast<CBrokenBrick*>(coObjects->at(i));
				e->GetBoundingBox(l2, t2, r2, b2);
				if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					e->SetState(STATE_BRICK_BREAK);
			}
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CFirePot*>(e->obj))
			{
				this->isVanish = true;
				e->obj->isVanish = true;
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				x += dx;
			}
			if (dynamic_cast<CCandle*>(e->obj))
			{
				e->obj->isVanish = true;
				this->isVanish = true;
			}
			if (dynamic_cast<CEnemy*>(e->obj))
			{
				CEnemy* enemy=NULL;
				this->isVanish = true;
				//e->obj->isVanish = true;
				switch (dynamic_cast<CEnemy*>(e->obj)->GetType())
				{
				case 2:
					enemy = dynamic_cast<CGhost*>(e->obj);
					break;
				case 10:
					enemy = dynamic_cast<CPanther*>(e->obj);
					break;
				case 20:
					enemy = dynamic_cast<CBat*>(e->obj);
					break;
				case 15:
					enemy = dynamic_cast<CBoss*>(e->obj);
					break;
				default:
					break;
				}
				enemy->SetState(ENEMY_STATE_DIE);
				
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

