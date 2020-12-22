#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Camera.h"
#include"Sprites.h"
#include"Sprites.h"
#define BOARD_ID 10
class Board
{
	float x, y;
	int time = 10000;
	LPANIMATION_SET ani_set;
	Camera* cam = Camera::GetInstance();

	CSprite * sprite;

public:
	Board();
	void Render();
	void Update();
	void SetSpriteSubWeap();
	~Board();
};