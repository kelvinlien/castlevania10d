#include "Dagger.h"


Dagger::Dagger() : CWeapon()
{
	ani = CWeapon::animation_set->at(1);
}
void Dagger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}