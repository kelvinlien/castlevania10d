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
	int time=10000;
	int state;
	int score=10000;
	CFont* font;
	DWORD healtime;
	LPANIMATION_SET ani_set;
	LPANIMATION_SET HP_set;
	Camera* cam = Camera::GetInstance();
	Simon* simon = Simon::GetInstance();
	int board_health=0;
public:
	Board();
	~Board();
	void Render();
	void SetState_OnBoard(int _state) { this->state = _state; }
	void Update();
};