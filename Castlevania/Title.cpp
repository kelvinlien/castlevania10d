#include "Title.h"
void Title::Render()
{
	int ani = TITLE_ANI_IDLE;
	if (state == TITLE_STATE_BLINK) {
		ani = TITLE_ANI_BLINK;
	}
	animation_set->at(ani)->Render(x, y);
}

