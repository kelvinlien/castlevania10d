#include "Bullet.h"


Bullet::Bullet()
{
	isVanish = true;
}
void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + Bullet_BBOX_WIDTH;
	bottom = y + Bullet_BBOX_HEIGHT;
}

void Bullet::SetAnimation() {
	if (nx > 0)
		ani = CWeapon::animation_set->at(ANI_Bullet_RIGHT);
	else
		ani = CWeapon::animation_set->at(ANI_Bullet_LEFT);
}

void Bullet::Render() {
	if (!isVanish && GetIsThrown()) {
		this->SetAnimation();
		ani->Render(x, y);
		RenderBoundingBox();
	}
}

void Bullet::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (!dynamic_cast<CFirePot *>(coObjects->at(i)) && !dynamic_cast<CCandle *>(coObjects->at(i)))
		{

			//Check collision AABB of Simon & Bullet
			if (dynamic_cast<Simon *>(coObjects->at(i)))
			{
				{
					float l1, t1, r1, b1;
					float l2, t2, r2, b2;

					GetBoundingBox(l1, t1, r1, b1);
					Simon::GetInstance()->GetBoundingBox(l2, t2, r2, b2);

					if (!(r1 < l2 || l1 > r2 || t1 > b2 || b1 < t2))
					{
						this->x += dx;
						return;
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



void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (!GetIsThrown()) return;
	vx = nx * Bullet_VX;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (x < Camera::GetInstance()->GetCamX() ||
			x > Camera::GetInstance()->GetCamX() + SCREEN_WIDTH) {
			isVanish = true;
			SetIsThrown(false);
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
				//this->isVanish = true;
				//e->obj->isVanish = true;
				x += dx;
			}
			if (dynamic_cast<CCandle*>(e->obj))
			{
				//this->isVanish = true;
				//e->obj->isVanish = true;
				x += dx;
			}
			if (dynamic_cast<CBrick*>(e->obj))
			{
				x += dx;
			}
			if (dynamic_cast<Simon*>(e->obj))
			{
				this->x += dx;
			
				if (!Simon::GetInstance()->IsUntouchable()) {
					int health  = Simon::GetInstance()->GetHealth();
					health -= 2;
					Simon::GetInstance()->SetHealth(health);
					if (Simon::GetInstance()->nx == this->nx) {

						Simon::GetInstance()->nx = -this->nx;
					}

					Simon::GetInstance()->SetState(SIMON_STATE_HURT);
				}
				else {
					if (e->nx != 0) Simon::GetInstance()->x += dx;
					if (e->ny != 0) Simon::GetInstance()->y += dy;
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

