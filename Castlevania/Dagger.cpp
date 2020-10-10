#include "Dagger.h"

Dagger::Dagger(int simonX, int simonY) {

	this->ani_set = CAnimationSets::GetInstance()->Get(4); // replace id of animation sets into 4

	this->x = simonX; // after simon is changing into Singleton pattern use Simon x not paremeters
	this->y = simonY;
	this->vx = DAGGER_VX;
}

void Dagger::Render() {
	ani_set->at(3)->Render(x, y); // replace id of animation dagger into 3
	RenderBoundingBox();
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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

			if (dynamic_cast<CFirePot *>(e->obj)) // if e->obj is Goomba 
			{
				CFirePot *firePot = dynamic_cast<CFirePot *>(e->obj);

				// if firepot
				
				 if (e->nx != 0)
				{
					 firePot->isVanish = true;
					 this->isVanish = true;
				}
			} 
			
			
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}



void Dagger::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + DAGGER_WIDTH_BBOX;
	b = y + DAGGER_HEIGHT_BBOX;
}