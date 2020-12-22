#include "Board.h"
#include "Simon.h"

Board::Board()
{
	ani_set = CAnimationSets::GetInstance()->Get(10);
	doubleShot = CSprites::GetInstance()->Get(40020);
}

void Board::Render()
{
	ani_set->at(0)->Render(x,y);

	if(Simon::GetInstance()->IsDoubleShot())
	doubleShot->Draw(x + 420.0f, y + 38.0f, GenerateAlpha());
	
}

void Board::Update()
{
	this->x = cam->GetCamX();
	this->y = cam->GetCamY();
	if (time != 0)
		time --;
	DebugOut(L"Time : %d\n", time);

	if (Simon::GetInstance()->IsDoubleShot() && flashingTime == 0)
		flashingTime = GetTickCount();
	else if (Simon::GetInstance()->IsDoubleShot() == false)
		flashingTime = 0;
}
int Board::GenerateAlpha() {
	int randNum = 255;
	if (GetTickCount() - flashingTime < 2000)
		randNum = rand() % 256;
	return randNum;
}