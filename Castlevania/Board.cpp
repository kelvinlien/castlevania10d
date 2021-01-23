#include "Board.h"
#include "Dagger.h"
#include"Simon.h"
#include"StopWatch.h"
#include "HolyWater.h"
#include "Axe.h"
#include "Boss.h"
#include "Game.h"
#define DAGGER_SPRITE		40016
#define STOPWATCH_SPRITE	40012
#define	HOLYWATER_SPRITE	40019
#define	AXE_SPRITE			51021
Board* Board::_instance = NULL;

Board* Board::Getinstance()
{
	if (_instance == NULL)
		_instance = new Board();
	return _instance;
}

Board::Board()
{
	board = CSprites::GetInstance()->Get(100000);
	ani_set = CAnimationSets::GetInstance()->Get(BOARD_ID);
	WhiteHP = CSprites::GetInstance()->Get(80039);
	bossOrangeHP = CSprites::GetInstance()->Get(80038);
	simonRedHP= CSprites::GetInstance()->Get(80037);
	font = new CFont();
	doubleShot = CSprites::GetInstance()->Get(40024);
}

Board::~Board()
{
}

void Board::Render()
{
	//ani_set->at(0)->Render(x, y);
	board->DrawBoard(0, 0);
	font->Render(std::to_string(score), 107, 15, 8);
	font->Render(std::to_string(time), 304, 15, 4);
	font->Render(std::to_string(stage), 480, 15, 2);
	font->Render(std::to_string(simon->GetHearts()), 400, 35, 2);
	font->Render(std::to_string(simon->GetLife()), 400, 55, 2);
	//Khung HP 
	for (int i = 0; i < 16; i++)
	{
		WhiteHP->DrawBoard((120) + i * 10, 32);
		WhiteHP->DrawBoard((120) + i * 10, 52);
	}
	//enemy
	DebugOut(L"[TEST] Health point %d\n", CBoss::GetInstance()->GetHealthBoss());
	for (int i = 0; i < CBoss::GetInstance()->GetHealthBoss(); i++)
	{
		bossOrangeHP->DrawBoard((120) + i * 10, 52);
	}
	//simon
	for (int i = 0; i < board_health; i++)
	{
		simonRedHP->DrawBoard((120) + i * 10, 32);
	}
	if(time_flag)
		healtime = GetTickCount();
	if (item != NULL)
		item->DrawBoard(312.0f, 32.7f,255);
	if(Simon::GetInstance()->IsDoubleShot())
	doubleShot->DrawBoard(312.0f, 35.0f, GenerateAlpha());
}

void Board::ReloadAni()
{
	board = CSprites::GetInstance()->Get(100000);
	WhiteHP = CSprites::GetInstance()->Get(80039);
	bossOrangeHP = CSprites::GetInstance()->Get(80038);
	simonRedHP = CSprites::GetInstance()->Get(80037);
	font = new CFont();
	doubleShot = CSprites::GetInstance()->Get(40024);
	SetSpriteSubWeap();
}

void Board::Update()
{
	x = cam->GetCamX();
	y = cam->GetCamY();
	if (!isFinish) 
	{
		if(simon->IsFreeze())
		simon->SetisFreeze(false);
		if (GetTickCount() - healtime >= 1000)
		{
			if (board_health < simon->GetHealth())
			{
				board_health += 1;
			}
			else
			{
				board_health = simon->GetHealth();
			}
				time_flag = true;
		}
		else
			time_flag = false;
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
		{
			isFinish = false;
			CGame::GetInstance()->SwitchScene(6);
		}
	}
	SetSpriteSubWeap();
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
void Board::SetSpriteSubWeap()
{
	if (dynamic_cast<Dagger *>(Simon::GetInstance()->GetSubWeapon()))
		 item = CSprites::GetInstance()->Get(DAGGER_SPRITE);
	else if( dynamic_cast<StopWatch *>(Simon::GetInstance()->GetSubWeapon()))
		item = CSprites::GetInstance()->Get(STOPWATCH_SPRITE);
	else if (dynamic_cast<HolyWater *>(Simon::GetInstance()->GetSubWeapon()))
		item = CSprites::GetInstance()->Get(HOLYWATER_SPRITE);
	else if (dynamic_cast<Axe *>(Simon::GetInstance()->GetSubWeapon()))
		item = CSprites::GetInstance()->Get(AXE_SPRITE);
	else item = NULL;

}

void Board::RewardingPoints(CGameObject * obj)
{
	if (dynamic_cast<CEnemy*>(obj))
	{
		if (dynamic_cast<CEnemy*>(obj)->IsDefeated())
		{
			SetScore(GetScore() + ENEMY_POINT_WORTH);
			dynamic_cast<CEnemy*>(obj)->SetIsDefeated(false);
		}
	}
	else if (dynamic_cast<CHolder*>(obj))
	{
		SetScore(GetScore() + HOLDER_POINT_WORTH);
	}
	else if (dynamic_cast<Item*>(obj))
	{
		Item* item = dynamic_cast<Item*>(obj);
		if (item->isEaten)
		{
			SetScore(GetScore() + ITEM_POINT_WORTH);
		}
	}
}