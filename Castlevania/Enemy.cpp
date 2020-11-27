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
		break;
	case ENEMY_STATE_MOVE:
		isLock = false;
		break;
	default:
		break;
	}
}