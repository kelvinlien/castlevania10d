#include "EnemyFactory.h"
CEnemyFactory * CEnemyFactory::__instance = NULL;
CEnemyFactory::CEnemyFactory()
{

}

CEnemyFactory * CEnemyFactory::GetInstance()
{
	if (__instance == NULL)
		__instance = new CEnemyFactory();
	return __instance;
}