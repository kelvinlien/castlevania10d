#include "Title.h"
void Title::Render()
{
	int ani = TITLE_ANI_IDLE;
	if (state == TITLE_STATE_BLINK) {
		ani = TITLE_ANI_BLINK;
	}
	animation_set->at(ani)->Render(x, y);
}

void Title::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (state == TITLE_STATE_BLINK)
	{
		if (startBlinkTime == 0)
			startBlinkTime = GetTickCount();
		else if (GetTickCount() - startBlinkTime >= BLINK_TIME)
			CGame::GetInstance()->SwitchScene(5);
	}
}