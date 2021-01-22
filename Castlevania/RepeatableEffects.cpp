#include "RepeatableEffects.h"
#include "Utils.h"
CRepeatableEffects* CRepeatableEffects::__instance = NULL;

CRepeatableEffects * CRepeatableEffects::GetInstance()
{
	if (__instance == NULL) __instance = new CRepeatableEffects();
	return __instance;
}


void CRepeatableEffects::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (repeatEffects.size() == 0)
		return;
	vector<LPREPEATEFFECT>::iterator it;            
	for (it = repeatEffects.begin(); it != repeatEffects.end();) {
		if ((*it)->isVanish == true) {
			delete * it;
			it = repeatEffects.erase(it);
		}
		else {
			++it;
		}
	}

	for (int i = 0; i < repeatEffects.size(); i++)
		repeatEffects.at(i)->Update(dt, coObjects);
}

void CRepeatableEffects::Render()
{
	if (repeatEffects.size() == 0)
		return;
	for (int i = 0; i < repeatEffects.size(); i++)
		repeatEffects.at(i)->Render();
}