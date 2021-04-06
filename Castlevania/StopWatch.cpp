#include "StopWatch.h"
#include"Ghost.h"
#include"Panther.h"
#include"Fishman.h"
#include "Bat.h"
StopWatch::StopWatch()
{
	isVanish = true;
}


void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
	if (stopTime == 0)
	{
		stopTime = GetTickCount();
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy *e = NULL;
				switch (dynamic_cast<CEnemy *>(coObjects->at(i))->GetType())
				{
				case 2:
					e = dynamic_cast<CGhost *>(coObjects->at(i));
					break;
				case 10:
					e = dynamic_cast<CPanther *>(coObjects->at(i));
					break;
				case 20:
					e = dynamic_cast<CBat *>(coObjects->at(i));
					break;
				case 30:
					e = dynamic_cast<CFishman *>(coObjects->at(i));
					break;
				default:
					break;
				}
				e->SetState(ENEMY_STATE_STOP);
			}
		}
	}
	if (GetTickCount() - stopTime > 3000)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CEnemy*>(coObjects->at(i)))
			{
				CEnemy *e = NULL;
				switch (dynamic_cast<CEnemy *>(coObjects->at(i))->GetType())
				{
				case ENEMY_TYPE_GHOST:
					e = dynamic_cast<CGhost *>(coObjects->at(i));
					break;
				case ENEMY_TYPE_PANTHER:
					e = dynamic_cast<CPanther *>(coObjects->at(i));
					break;
				case ENEMY_TYPE_BAT:
					e = dynamic_cast<CBat *>(coObjects->at(i));
					break;
				case ENEMY_TYPE_FISHMAN:
					e = dynamic_cast<CFishman *>(coObjects->at(i));
					break;
				default:
					break;
				}
				e->SetState(ENEMY_STATE_MOVE);
			}
		}
		stopTime = 0;
		this->isVanish = true;
	}
}

