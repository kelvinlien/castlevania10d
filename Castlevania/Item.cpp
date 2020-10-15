#include "Item.h"
#include "Simon.h"


Item::Item(int x, int y, Animation ani) {
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	ani_set = animation_sets->Get(ITEM_ANI_SET_ID);

	this->x = x;
	this->y = y;
	existingTime = 20000;

	this->ani = ani;
	switch (this->ani)
	{
	case SMALL_HEART:
		widthBBox = 16;
		heightBBox = 16;
	break;
	case BIG_HEART:
		widthBBox = 24;
		heightBBox = 16;
		break;
	case WHIP_RED:
		widthBBox = 32;
		heightBBox = 32;
		break;
	case DAGGER:
		widthBBox = 32;
		heightBBox = 16;
		break;
	default:
		break;
	}
}
void Item::Render() {
	ani_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vy = GRAVITY;

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally

	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

					//if (nx != 0) vx = 0;
					if (ny != 0) {
						vy = 0;
						//counting time to vanish item
						if (existingTime <= 0)
						{
							this->isVanish = true;
						}
						existingTime -= dt;
					}
		}
	}

void Item::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}