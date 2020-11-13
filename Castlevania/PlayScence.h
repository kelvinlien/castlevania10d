#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "Goomba.h"
#include "Koopas.h"
#include "GameMap.h"
#include "FirePot.h"
#include "Item.h"
#include "GameMap.h"
#include "TriggerStair.h"

class CPlayScene: public CScene
{
protected: 
	Simon *player;					// A play scene has to have player, right? 

	Item item; //temp item to save when item created
	vector<LPGAMEOBJECT> objects;
	int mapWidth;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAPMATRIX(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void LoadTriggerStair();

	Simon * GetPlayer() { return player; } 
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

