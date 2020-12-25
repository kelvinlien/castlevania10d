#include"Enemy.h"
CEnemy::CEnemy() :CGameObject()
{
	isActive = false;
	state = ENEMY_STATE_MOVE;
	isLock = false;
}
void CEnemy::SetState(int state)
{
	this->state = state;
	switch (state)
	{
		case ENEMY_STATE_STOP:
			isLock = true;
			backUpVx = vx;   // save vx, vy for reuse it when we set to state move
			backUpVy = vy;  
			this->vx = 0.0;
			this->vy = 0.0;
			this->animation_set->at(ani)->SetLock(true);
			break;
		case ENEMY_STATE_MOVE:
			isLock = false;
			this->vx = backUpVx;
			this->vy = backUpVy;
			this->animation_set->at(ani)->SetLock(false);
			break;
	}
}
void CEnemy::SetItem(int itemType) {
	ItemType type;
	switch (itemType)
	{
	case 0:
		type = ITEM_SMALL_HEART;
		break;
	case 1:
		type = ITEM_BIG_HEART;
		break;
	case 5:
		type = ITEM_WHIP;
		break;
	case 7:
		type = ITEM_DAGGER;
		break;
	default:
		break;
	}
	this->itemType = type;
}