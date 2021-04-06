#include "OutroBat.h"
void OutroBat::Render()
{
	animation_set->at(0)->Render(x, y, 255);
}