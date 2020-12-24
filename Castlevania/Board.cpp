#include "Board.h"


Board::Board()
{
	ani_set = CAnimationSets::GetInstance()->Get(10);
}

void Board::Render()
{
	ani_set->at(0)->Render(x,y);
}

void Board::Update()
{
	this->x = cam->GetCamX();
	this->y = cam->GetCamY();
	if (time != 0)
		time --;
}
