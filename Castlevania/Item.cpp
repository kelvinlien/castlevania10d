#include "Item.h"
#include "Simon.h"
#include "Weapon.h"
#include "Game.h"
#include "BlinkEffect.h"
#include "Board.h"

Item::Item(int x, int y, ItemType ani) {
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();
	ani_set = animation_sets->Get(ITEM_ANI_SET_ID);

	this->x = x;
	this->y = y;
	existingTime = 2000;
	effectDuration = 0;
	isEaten = false;
	effect = BURN_EFFECT;

	this->ani = ani;
	switch (this->ani)
	{
	case ITEM_SMALL_HEART:
		widthBBox = 16;
		heightBBox = 16;
		start_x = x;
		vx = 0.1;
	break;
	case ITEM_BIG_HEART:
		widthBBox = 24;
		heightBBox = 20;
		start_x = x;
		break;
	case ITEM_MONEY_BAG_RED:
		widthBBox = 30;
		heightBBox = 30;
		start_x = x;
		break;
	case ITEM_MONEY_BAG_WHITE:
		widthBBox = 30;
		heightBBox = 30;
		start_x = x;
		break;
	case ITEM_MONEY_BAG_BLUE:
		widthBBox = 30;
		heightBBox = 30;
		start_x = x;
		break;
	case ITEM_WHIP:
		widthBBox = 32;
		heightBBox = 32;
		start_x = x;
		break;
	case ITEM_DAGGER:
		widthBBox = 32;
		heightBBox = 16;
		start_x = x;
		break;
	case ITEM_STOP_WATCH:
		widthBBox = 40;
		heightBBox = 32;
		start_x = x;
		break;
	case ITEM_CROSS:
		widthBBox = 32;
		heightBBox = 32;
		start_x = x;
		break;
	case ITEM_HOLY_WATER:
		widthBBox = 32;
		heightBBox = 32;
		start_x = x;
		break;
	case ITEM_CHICKEN_THIGH:
		widthBBox = 32;
		heightBBox = 26;
		start_x = x;
		break;
	case ITEM_AXE:
		widthBBox = 30;
		heightBBox = 28;
		start_x = x;
		break;
	case ITEM_ORD:
		widthBBox = 24;
		heightBBox = 28;
		start_x = x;
		existingTime = 10000;
		break; 
	case ITEM_DOUBLE_SHOT:
		widthBBox = 28;
		heightBBox = 28;
		start_x = x;
		break;
	default:
		break;
	}
}
void Item::Render() {
	if (isEaten)
	{
		if (ani != ITEM_CROSS)
		{
			ani_set->at(effect)->Render(x, y);
		}
	}
	else
	{
		ani_set->at(ani)->Render(x, y);
	}
	RenderBoundingBox();
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy = GRAVITY;
	if (ani == ITEM_SMALL_HEART)
	{
		vy = GRAVITY / 2;
		if ((start_x > x && start_x - x > 30.0 && vx < 0) || (start_x < x && x - start_x > 30.0 && vx > 0))
		{
			vx = -vx;
		}
	}
	if (isEaten)
	{
		vy = 0;
	}
	CGameObject::Update(dt, coObjects);
	vector<LPGAMEOBJECT> coObjectsItem;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*> (coObjects->at(i))|| dynamic_cast<CSmallBrick*> (coObjects->at(i)))
			coObjectsItem.push_back(coObjects->at(i));
	}
	coEvents.clear();

	CalcPotentialCollisions(&coObjectsItem, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	float rdx = 0;
	float rdy = 0;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	x += min_tx * dx + nx * 0.4f;
	y += min_ty * dy + ny * 0.4f;
	if (nx != 0) vx = 0;
	if (ny != 0) {
		vx = 0;
		vy = 0;
	}
	if (isEaten)
	{
		if (effectDuration <= 0)
		{
			BlinkEffect::GetInstance()->SetIsActive(false);
			this->isVanish = true;
		}
		effectDuration -= dt;
	}
	//counting time to vanish item	
	else
	{
		if (existingTime <= 0)
		{
			this->isVanish = true;
		}
		existingTime -= dt;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Item::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}

void Item::BeingProcessed()
{
	Simon *simon = Simon::GetInstance();
	Board* board = Board::Getinstance();
	isEaten = true;
	switch (ani)
	{
	case ITEM_SMALL_HEART:
		simon->SetHearts(simon->GetHearts() + 1);
		break;
	case ITEM_BIG_HEART:
		simon->SetHearts(simon->GetHearts() + 5);
		break;
	case ITEM_ORD:
		simon->SetHealth(SIMON_MAX_HEALTH); 
		board->SetFinish(true);
		break;
	case ITEM_CHICKEN_THIGH:
		if (simon->GetHealth() + 6 >= 16)
			simon->SetHealth(SIMON_MAX_HEALTH);
		else
			simon->SetHealth(simon->GetHealth() + 6);
		break;
	case ITEM_DOUBLE_SHOT:
		simon->SetIsDoubleShot(true);
		break;
	case ITEM_MONEY_BAG_RED:
		effect = ONE_THOUSAND_EFFECT;
		this->y -= 20;
		effectDuration = 1000;
		widthBBox = 37;
		heightBBox = 16;
		break;
	case ITEM_MONEY_BAG_WHITE:
		effect = SEVEN_HUNDRED_EFFECT;
		this->y -= 20;
		effectDuration = 1000;
		widthBBox = 28;
		heightBBox = 16;
		break;
	case ITEM_MONEY_BAG_BLUE:
		effect = FOUR_HUNDRED_EFFECT;
		this->y -= 20;
		effectDuration = 1000;
		widthBBox = 29;
		heightBBox = 16;
		break;
	case ITEM_WHIP:
		simon->SetState(SIMON_STATE_LEVEL_UP);
		CWhip::GetInstance()->LevelUp();
		break;
	case ITEM_DAGGER:
		simon->SetSubWeapons(WeaponManager::GetInstance()->createWeapon(DAGGER));
		break;
	case ITEM_STOP_WATCH:
		simon->SetSubWeapons(WeaponManager::GetInstance()->createWeapon(STOPWATCH));
		break;
	case ITEM_CROSS:
		effectDuration = 1000;
		BlinkEffect::GetInstance()->SetIsActive(true);
		//BlinkEffect::GetInstance()->StartEffect(GetTickCount());
		break;
	case ITEM_HOLY_WATER:
		simon->SetSubWeapons(WeaponManager::GetInstance()->createWeapon(HOLYWATER));
		break;
	case ITEM_AXE:
		simon->SetSubWeapons(WeaponManager::GetInstance()->createWeapon(AXE));
		break;
	default:
		break;
	}

	if (effectDuration == 0)
	{
		isVanish = true;
	}
	else
	{
		CAnimationSets * animation_sets = CAnimationSets::GetInstance();
		ani_set = animation_sets->Get(EFFECT_ANI_SET_ID);
	}
}
