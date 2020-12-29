#include "Board.h"

Board* Board::_instance = NULL;

Board* Board::Getinstance()
{
	if (_instance == NULL)
		_instance = new Board();
	return _instance;
}

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
	ani_set->at(0)->Render(x + 140, y + 20);
	font->Render(std::to_string(score), x + 245, 35, 6);
	font->Render(std::to_string(time), x + 440, 35, 4);
	font->Render(std::to_string(stage), x + 620, 35, 2);
	font->Render(std::to_string(simon->GetHearts()), x + 540, 55, 2);
	//Khung HP 
	for (int i = 0; i < 16; i++)
	{
		HP_set->at(39)->Render((x + 260) + i * 10, 52);
		HP_set->at(39)->Render((x + 260) + i * 10, 72);
	}
	//enemy
	for (int i = 0; i < 16; i++)
	{
		HP_set->at(38)->Render((x + 260) + i * 10, 72);
	}
	//simon
	for (int i = 0; i < board_health; i++)
	{
		HP_set->at(37)->Render((x + 260) + i * 10, 52);
	}
	if(time_flag)
		healtime = GetTickCount();
}

void Board::Update()
{
	x = cam->GetCamX();
	y = cam->GetCamY();
	if (!isFinish) 
	{
		if(simon->IsFreeze())
		simon->SetisFreeze(false);
		if (board_health < simon->GetHealth())
			board_health += 1;
		else
			board_health = simon->GetHealth();
		if (time != 0 && GetTickCount() - healtime >= 1000)
		{
			time--;
			healtime = 0;
			time_flag = true;
		}
		else
			time_flag = false;
	}
	else
	{
		simon->SetisFreeze(true);
		if (GetTickCount() - healtime >= 1000)
		{
			if (board_health < 16)
				board_health += 1;
			time_flag = true;
		}
		else
			time_flag = false;
		if (time != 0 && board_health == 16)
		{
			time--;
			score += 10;
		}
		if (simon->GetHearts()!=0 && time == 0)
		{
			simon->SetHearts(simon->GetHearts() - 1);
			score += 100;
		}
		if (simon->GetHearts() == 0)
			isFinish = false;
	}
}
