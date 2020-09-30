#include "Item.h"

Item::Item(int x, int y, int typeID) {
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	ani_set = animation_sets->Get(ANI_SET_ID);

	this->x = x;
	this->y = y;
	existingTime = 2000;

	//animation = CAnimations::GetInstance()->Get(typeID);

	switch (typeID)
	{
	case TYPE_ITEM_WHIP:
		break;
	case TYPE_ITEM_BIG_HEART:
		break;
	case TYPE_ITEM_SMALL_HEART:
		break;
	case TYPE_ITEM_DAGGER:
		break;
	case TYPE_ITEM_MONEY_BAG:
		break;
	default:
		break;
	}
}
void Item::Render() {
	ani_set->at(4)->Render(x, y);
}
void Item::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + 32;
	b = y + 32;
}
