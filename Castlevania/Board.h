#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Camera.h"
#include "Utils.h"
#include "Sprites.h"
#define BOARD_ID 10
class Board 
{
	float x, y;
	int time=10000;
	DWORD flashingTime = 0;
	LPANIMATION_SET ani_set;
	Camera* cam = Camera::GetInstance();
	CSprite * doubleShot;

public:
	Board();
	~Board();
	void Render();
	void Update();
	int GenerateAlpha();
};