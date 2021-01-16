#include "Area.h"
Area * Area::__instance = NULL;

Area *Area::GetInstance()
{
	if (__instance == NULL) __instance = new Area();
	return __instance;
}