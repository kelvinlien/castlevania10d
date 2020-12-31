#include "Area.h"
#include"Game.h"
Area * Area::__instance = NULL;

Area *Area::GetInstance()
{
	if (__instance == NULL) __instance = new Area();
	return __instance;
}

void Area::SetSpawnPos()
{
	switch (CGame::GetInstance()->GetCurrentSceneID())
	{
	case 1:
	case 2:
		spawnPosX = 50.0f;
		spawnPosY = 0;
		break;
	case 3:
		spawnPosX = 50.0f;
		spawnPosY = 10.0f;
		break;
	default:
		spawnPosX = 1000.0f;
		spawnPosY = 0;
		break;
	}
}