#pragma once
#include "GameObject.h"
#include "Enemy.h"
class CEnemyFactory :public CGameObject
{
	static CEnemyFactory * __instance;
	int enemyNumber, enemyType;

public:
	vector<CEnemy*> enemies;
	CEnemyFactory();
	static CEnemyFactory * GetInstance();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	void Render() {};
	
	//Getter
	int GetEnemyNumber() { return enemyNumber; }
	int GetEnemyType() { return enemyType; }
};