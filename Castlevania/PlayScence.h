#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "FirePot.h"
#include "Koopas.h"
#include "GameMap.h"
#include "FirePot.h"
#include "Candle.h"
#include "Item.h"
#include "GameMap.h"
#include "Panther.h"
#include "Background.h"
#include "Title.h"
#include "CastleAndBat.h"
#include "RepeatableEffects.h"
#include  "Bat.h"
#include "TriggerStair.h"
#include "Board.h"
#include "Fishman.h"
#include"Ghost.h"
#include "Quadtree.h"
#include "Area.h"
#define PLAY_SCENE_1_ID	1
#define PLAY_SCENE_2_ID	2
#define PLAY_SCENE_3_ID	3
#define INTRO_SCENE_ID_1	4
#define INTRO_SCENE_ID_2	5
#define OUTRO_SCENE_ID	6
#define TRIGGER_STAIR_1_PLAY_SCENE_3_ID	19
#define TRIGGER_STAIR_2_PLAY_SCENE_3_ID	20

#include"Ghost.h"

#include "BrokenBrick.h"
class CPlayScene: public CScene
{
protected: 
	CRepeatableEffects *effects;	//list contain effects
	Simon *player;					// A play scene has to have player, right?
	CGhost *ghost;					// Beta ghost for testing purpose
	CPanther *panther;
	CBat* bat;
	CFishman* fishman;
	Quadtree *qtree;
	Board* board;
	Item item; //temp item to save when item created
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> delObjects;
	vector<Entity*> activeEntities;
	int mapWidth;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAPMATRIX(string line);
	void _ParseSection_SCENE_ANI_SET(string line);
	void _ParseSection_SCENE_OBJECT(string line);
public:
	
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void LoadTriggerStair();

	Simon * GetPlayer() { return player; } 
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
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