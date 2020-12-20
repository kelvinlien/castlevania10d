#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "Camera.h"
#include "Utils.h"
#define BOARD_ID 10
class Board 
{
	float x, y;
	int time=10000;
	LPANIMATION_SET ani_set;
	Camera* cam = Camera::GetInstance();
public:
	Board();
	~Board();
	void Render();
	void Update();
};