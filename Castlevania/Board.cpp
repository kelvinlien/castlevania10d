#include "Board.h"
#include "Dagger.h"
#include"Simon.h"
#include"StopWatch.h"
#include "HolyWater.h"

#define DAGGER_SPRITE		40016
#define STOPWATCH_SPRITE	40012
#define	HOLYWATER_SPRITE	40019
Board::Board()
{
	ani_set = CAnimationSets::GetInstance()->Get(10);
}

void Board::Render()
{
	ani_set->at(0)->Render(x,y);
	if (sprite != NULL)
		sprite->Draw(x+310.0f, y +32.7f,255);
}

void Board::Update()
{
	this->x = cam->GetCamX();
	this->y = cam->GetCamY();
	if (time != 0)
		time --;
	DebugOut(L"Time : %d\n", time);
	SetSpriteSubWeap();
}
void Board::SetSpriteSubWeap()
{
	if (dynamic_cast<Dagger *>(Simon::GetInstance()->GetSubWeapon()))
		 sprite = CSprites::GetInstance()->Get(DAGGER_SPRITE);
	else if( dynamic_cast<StopWatch *>(Simon::GetInstance()->GetSubWeapon()))
		sprite = CSprites::GetInstance()->Get(STOPWATCH_SPRITE);
	else if (dynamic_cast<HolyWater *>(Simon::GetInstance()->GetSubWeapon()))
		sprite = CSprites::GetInstance()->Get(HOLYWATER_SPRITE);
	else sprite = NULL;
}