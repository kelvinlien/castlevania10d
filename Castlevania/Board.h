#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Camera.h"
#include "Game.h"
#include "Utils.h"
#include "Simon.h"
#include "Font.h"
#define BOARD_ID 10
class Board 
{
	float x = 0.0f;
	float y = 0.0f;

	int time=1000;
	int state;
	int score=0;
	int board_health=0;

	bool time_flag = true;
	bool isFinish = false;

	CFont* font;

	DWORD healtime;

	LPANIMATION_SET ani_set;
	LPANIMATION_SET HP_set;

	Camera* cam= Camera::GetInstance();;
	Simon* simon = Simon::GetInstance();

	static Board* _instance;
public:
	Board();
	~Board();

	void Render();
	void Update();

	void SetScore(int _score) { this->score += _score; }
	int GetScore() { return score; }

	void SetTime(int _time) { this->time = time; }
	int GetTime() { return time; }

	bool Check_isFinish (){ return isFinish;}
	void SetFinish(bool _isFinish) { isFinish = _isFinish; }

	void SetState_OnBoard(int _state) { this->state = _state; }

	static Board* Getinstance();
};