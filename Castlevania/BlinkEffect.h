#pragma once
#define BLINK_EFFECT_TEXTURE_ID	75
#define BLINK_EFFECT_SWITCH_SCENE_TEXTURE_ID	76
#define SCREEN_HEIGHT_WITHOUT_FLOOR	471
#include "Textures.h"
#include "Game.h"
#include "Camera.h"

class BlinkEffect
{
	bool isActive;
	static BlinkEffect* __instance;
public:
	BlinkEffect() { isActive = false; };
	void SetIsActive(bool _isActive) { isActive = _isActive; }
	bool GetIsActive() { return isActive; }
	void Draw(int alpha);
	static BlinkEffect* GetInstance();
};

