#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Camera.h"
#include"Sprites.h"
#include"Sprites.h"
#include "Game.h"
#include "Utils.h"
#include "Simon.h"
#include "Font.h"
#include "Enemy.h"
#include "Holder.h"
#include "Item.h"
#define BOARD_ID 12
#define ENEMY_POINT_WORTH	10
#define HOLDER_POINT_WORTH	5
#define ITEM_POINT_WORTH	5
#define ONE_THOUSAND_POINT	1000
#define FOUR_HUNDRED_POINT	400
#define SEVEN_HUNDRED_POINT	700
class Board
{
	float x = 0;
	float y = 0;

	int time = 300;
	int stage;
	int score=0;
	int board_health=16;

	bool time_flag = true;
	bool isFinish = false;

	CFont* font;

	DWORD healtime;
	DWORD flashingTime = 0;
	LPANIMATION_SET ani_set;
	CSprite * board;
	CSprite * item;
	CSprite * WhiteHP;
	CSprite * simonRedHP;
	CSprite * bossOrangeHP;
	CSprite * doubleShot;

	Camera* cam= Camera::GetInstance();;
	Simon* simon = Simon::GetInstance();
	static Board* _instance;
public:
	Board();
	~Board();
	void Render();
	void Update();
	int GenerateAlpha();

	void SetScore(int _score) { this->score = _score; }
	int GetScore() { return score; }

	void SetTime(int _time) { this->time = time; }
	int GetTime() { return time; }

	void SetBoardHealth(int BoardHealth) { this->board_health = BoardHealth; }
	int GetBoardHealth() { return board_health; }

	bool Check_isFinish (){ return isFinish;}
	void SetFinish(bool _isFinish) { isFinish = _isFinish; }
	void SetState_OnBoard(int _stage) { this->stage = _stage; }
	void SetSpriteSubWeap();
	void RewardingPoints(CGameObject* obj);
	static Board* Getinstance();
	void ReloadAni();
};