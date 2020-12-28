#include "BlinkEffect.h"
#include "GameMap.h"
BlinkEffect* BlinkEffect::__instance = NULL;

void BlinkEffect::Draw(int alpha)
{
	Camera* cam = Camera::GetInstance();
	CGame* game = CGame::GetInstance();
	int mapID = game->GetCurrentSceneID();
	CMaps* maps = CMaps::GetInstance();
	int mapHeight = maps->Get(mapID)->getMapHeight();
	if(mapID == 1)
		game->Draw(cam->GetCamX(), cam->GetCamY(), CTextures::GetInstance()->Get(BLINK_EFFECT_SWITCH_SCENE_TEXTURE_ID), 0, 0, 800, 508, alpha);
	else
		game->Draw(cam->GetCamX(), cam->GetCamY() + SCREEN_HEIGHT_WITHOUT_FLOOR - mapHeight, CTextures::GetInstance()->Get(BLINK_EFFECT_TEXTURE_ID), 0, 0, 800, 508, alpha);
}

BlinkEffect * BlinkEffect::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new BlinkEffect();
	}
	return __instance;
}