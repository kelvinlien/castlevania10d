#include"Enemy.h"
CEnemy::CEnemy() :CGameObject()
{
	isActive = false;
}
void CEnemy::Respawn()
{
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