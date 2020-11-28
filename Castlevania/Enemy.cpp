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
			animation_set->at(ani)->SetLock(true);
			break;
		case ENEMY_STATE_MOVE:
			isLock = false;
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
		type = ITEM_WHIP_RED;
		break;
	case 7:
		type = ITEM_DAGGER;
		break;
	default:
		break;
	}
	this->itemType = type;
}