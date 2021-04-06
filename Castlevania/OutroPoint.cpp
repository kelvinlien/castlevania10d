#include "OutroPoint.h"
void OutroPoint::Render()
{
	animation_set->at(0)->Render(x, y, 255);
}