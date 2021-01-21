#include "CastleAndBat.h"
void CastleAndBat::Render() {
	int ani = CASTLE_AND_BAT_ANI_ACTIVE;
	if (state == CASTLE_AND_BAT_STATE_IDLE) {
		ani = CASTLE_AND_BAT_ANI_IDLE;
	}
	animation_set->at(ani)->Render(x, y);
}
void CastleAndBat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects ) {
	if (GetTickCount() - startToRender > CASTLE_AND_BAT_ACTIVE_TIME && !isIdle && !CAnimationSets::GetInstance()->Get(0)->at(CASTLE_AND_BAT_ANI_IDLE)->GetLock()) {
		SetState(CASTLE_AND_BAT_STATE_IDLE);
		isIdle = true;
	}
}