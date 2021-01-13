#include "Background.h"
void Background::Render()
{
	animation_set->at(0)->Render(x, y);
}