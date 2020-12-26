#include "EnemyFactory.h"

CEnemyFactory::CEnemyFactory()
{

}

CEnemyFactory * CEnemyFactory::GetInstance()
{
	if (__instance == NULL)
		__instance = new CEnemyFactory();
	return __instance;
}

void CEnemyFactory::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

}

void CEnemyFactory::Render()
{

}