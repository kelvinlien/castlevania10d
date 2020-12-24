#include "Board.h"


Board::Board()
{
	ani_set = CAnimationSets::GetInstance()->Get(10);
	HP_set = CAnimationSets::GetInstance()->Get(8);
	font = new CFont();
}

Board::~Board()
{
}

void Board::Render()
{

	ani_set->at(0)->Render(x,y);
	font->Render(std::to_string(score), x + 105, 15);
	font->Render(std::to_string(time), x + 300, 15);
	font->Render(std::to_string(state), x + 480, 15);
	font->Render(std::to_string(simon->GetHearts()), x + 400, 35);

	for (int i = 0; i < 16; i++)
	{
		HP_set->at(39)->Render((x + 120) + i * 10, 32);
		HP_set->at(39)->Render((x + 120) + i * 10, 52);
	}
	for (int i = 0; i < 16; i++)
	{
		HP_set->at(38)->Render((x+120) + i * 10, 52);
	}
	for (int i = 0; i < board_health; i++)
	{
		HP_set->at(37)->Render((x + 120) + i * 10, 32);
		healtime =0;
		
	}

}

void Board::Update()
{

	this->x = cam->GetCamX();
	this->y = cam->GetCamY();

	if ((healtime / 2) > 100)
	{
		if (board_health < simon->GetHealth())
			board_health++;
		else
			board_health = simon->GetHealth();
	}
	if (time != 0 && healtime / 2 > 100)
	{
		score--;
		time--;
	}
	healtime = GetTickCount64();
}
