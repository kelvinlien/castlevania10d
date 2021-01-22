#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Camera.h"
#include "GameMap.h"
#include "Panther.h"
#include "Entity.h"
#include <algorithm>
#include "Door.h"
#include "Fishman.h"
#include "WaterSurface.h"
#include "Background.h"
#include "Helicopter.h"
#include "IntroBat.h"

#include "BlinkEffect.h"
#include "Door.h"
using namespace std;

/*
Load scene resources from scene file (textures, sprites, animations and objects)
See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPMATRIX 7
#define SCENE_SECTION_OBJECT		11

#define SCENE_SECTION_ANI_SET		8
#define SCENE_SECTION_ITEM		9
#define SCENE_SECTION_FIREPOT	10
#define SCENE_SECTION_OBJECT		11

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GHOST	2
#define OBJECT_TYPE_PANTHER	10
#define OBJECT_TYPE_FISHMAN	30
#define OBJECT_TYPE_FIREPOT	3
#define OBJECT_TYPE_CANDLE	4
#define OBJECT_TYPE_BRICKS_GROUP	5
#define OBJECT_TYPE_DOOR			6
#define	OBJECT_TYPE_SMALL_BRICK_GROUP	9
#define OBJECT_TYPE_BROKEN_BRICK	8
#define OBJECT_TYPE_WATER_SURFACE	12
#define OBJECT_TYPE_BAT	20
#define OBJECT_TYPE_INTRO_FLOOR		11
#define OBJECT_TYPE_HELICOPTER		14
#define OBJECT_TYPE_INTRO_BAT		13

#define OBJECT_TYPE_BRICKS_GROUP	5
#define OBJECT_TYPE_EFFECT	21

#define OBJECT_TYPE_PORTAL	50

#define OBJECT_TYPE_CASTLE_AND_BAT	100
#define OBJECT_TYPE_PUSH_ANY_KEY	110
#define OBJECT_TYPE_BACKGROUND	120




#define MAX_SCENE_LINE 1024
#define OBJECT_TYPE_BACKGROUND	120

wchar_t * ConvertToWideChar(char * p)
{
	wchar_t *r;
	r = new wchar_t[strlen(p) + 1];

	char *tempsour = p;
	wchar_t *tempdest = r;
	while (*tempdest++ = *tempsour++);

	return r;
}
CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath) {
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{

	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}
/*
Parse map matrix in section [MAPMATRIX]
*/
void CPlayScene::_ParseSection_MAPMATRIX(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;

	int ID = atoi(tokens[0].c_str());
	wstring matrixString = ToWSTR(tokens[1]);
	CMaps::GetInstance()->Add(matrixString.c_str(), id);
}
/*
Parse a line in section [OBJECTS]
*/

void CPlayScene::_ParseSection_OBJECTS(string line)
{

	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y
	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	
	int ani_set_id = atoi(tokens[3].c_str());
	int amount, axis, brickType, itemType;
	if (object_type == 5 || object_type == 9) {
		amount = atoi(tokens[4].c_str());
	}

	float jumpLeftX, jumpRightX;
	int directX;
	if (object_type == 8)
	{
		brickType = atoi(tokens[4].c_str());
		itemType = atoi(tokens[5].c_str());
	}
	if (object_type == 9)
	{
		axis = atoi(tokens[5].c_str());
	}
	if (object_type == 10)
	{
		jumpLeftX = atoi(tokens[4].c_str());
		jumpRightX = atoi(tokens[5].c_str());
		directX = atoi(tokens[6].c_str());
	}
	if (object_type == 8)
	{
		brickType = atoi(tokens[4].c_str());
		itemType = atoi(tokens[5].c_str());
	}
	if (object_type == 9)
	{
		axis = atoi(tokens[5].c_str());
	}
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	//CPanther *panTest = new CPanther(500, 100, 200, 800, -1);

	//Entity* panther = new Entity(panTest, 160);
	//DebugOut(L"[TEST] panther width and height %f %f!\n", panther->GetObjectWidth(), panther->GetObjectHeight());

	//CCandle *canTest = new CCandle(1);
	//canTest->SetPosition(600, 100);

	//Entity* candle = new Entity(canTest, 0);
	//RECT triggerZone = candle->GetTriggerZone();
	//DebugOut(L"[TEST] candle left and bottom %d %d \n", triggerZone.left, triggerZone.bottom);

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = Simon::GetInstance();
		player = (Simon*)obj;
		player->ReLoadAllAniSet();
		Simon::GetInstance()->SetIsIdleIntro(false);

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GHOST: {
		int itemType = atof(tokens[4].c_str());
		obj = new CGhost(x, y, -1, itemType);
	}
	break;
	case OBJECT_TYPE_PANTHER: 
		obj = new CPanther(x, y, jumpLeftX, jumpRightX, directX);
		break;
	case OBJECT_TYPE_BAT: {
		int itemType = atof(tokens[4].c_str());
		obj = new CBat(x, y, Simon::GetInstance()->nx * -1, itemType);
		break;
	}
	case OBJECT_TYPE_FISHMAN: {
		int itemType = atof(tokens[4].c_str());
		obj = new CFishman(x, y, -Simon::GetInstance()->nx, itemType);

		float randomDistance = rand() % (BRICK_WIDTH * 2 * 16) + 1;
		DebugOut(L"[TEST]Random distance %f \n ", randomDistance);
		obj->SetPosition(x + randomDistance, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}
	break;

	case OBJECT_TYPE_BRICK: {
		int amountOfBrick;
		//to assign mapWidth
		int currentMapID = CGame::GetInstance()->GetCurrentSceneID();
		mapWidth = CMaps::GetInstance()->Get(currentMapID)->getMapWidth();
		if (currentMapID == 1)
			amountOfBrick = mapWidth / BRICK_WIDTH;
		else
			amountOfBrick = mapWidth / (BRICK_WIDTH * 2);

		//first brick
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj = new CBrick();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);

		for (int i = 1; i < amountOfBrick; i++) {
			if (i != 99 && i != 119)
			{
				obj = new CBrick();
				if (currentMapID == 1)
					obj->SetPosition(x + BRICK_WIDTH * i, y);
				else
					obj->SetPosition(x + BRICK_WIDTH * 2 * i, y);

				obj->SetAnimationSet(ani_set);
				objects.push_back(obj);
			}
		}
		break;
	}
	case OBJECT_TYPE_BRICKS_GROUP: {
		int amountOfBrick = amount;

		//first brick
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj = new CBrick();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);

		for (int i = 1; i < amountOfBrick; i++) {
			obj = new CBrick();

			obj->SetPosition(x + BRICK_WIDTH * 2 * i, y);
			obj->SetAnimationSet(ani_set);
			objects.push_back(obj);
		}
		break;
	}
	case OBJECT_TYPE_SMALL_BRICK_GROUP: {
		int amountOfSmallBrick = amount;
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		for (int i = 0; i <= amountOfSmallBrick; i++)
		{
			obj = new CSmallBrick();
			if (axis == 0)
				obj->SetPosition(x + SMALL_BRICK_WIDTH * i, y);
			else
				obj->SetPosition(x, y + SMALL_BRICK_BBOX_HEIGHT * i);
			obj->SetAnimationSet(ani_set);
			objects.push_back(obj);
		}
		break;
	}
	case OBJECT_TYPE_BROKEN_BRICK:
		obj = new CBrokenBrick(brickType, itemType);
		break;
	case OBJECT_TYPE_INTRO_FLOOR: {

		//first brick
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj = new CBrick();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);

		for (int i = 1; i < 35; i++) {
			obj = new CBrick();
			obj->SetPosition(x + BRICK_WIDTH * i, y);
			obj->SetAnimationSet(ani_set);
			objects.push_back(obj);
		}
		break;
	}
	case OBJECT_TYPE_FIREPOT: {
		int type = atof(tokens[4].c_str());

		obj = new CFirePot(type);
		break;
	}

	case OBJECT_TYPE_CANDLE: {
		int type = atof(tokens[4].c_str());
		obj = new CCandle(type);
		break;
	}
	case OBJECT_TYPE_DOOR:
	{
		int id = atof(tokens[4].c_str());
		obj = new CDoor(x, y, id);
		break;
	}
	case OBJECT_TYPE_WATER_SURFACE:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		obj = new CWaterSurface(x, y, r, b);
	}
	break;
	
	case OBJECT_TYPE_HELICOPTER: {
		obj = new CHelicopter();
		break;
	}

	case OBJECT_TYPE_INTRO_BAT: {
		int nx= atof(tokens[4].c_str());
		obj = new CIntroBat(x,y,nx);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{

			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
		}
		break;
	case OBJECT_TYPE_BACKGROUND:
	{
		obj = new Background();
		break;
	}
	case OBJECT_TYPE_PUSH_ANY_KEY:
	{
		obj = new Title();
		break;
	}
	case OBJECT_TYPE_CASTLE_AND_BAT:
	{
		obj = new CastleAndBat();
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	

	// General object setup
	if (!dynamic_cast<CBrick*>(obj) && !dynamic_cast<CFishman*>(obj)) {
		obj->SetPosition(x, y);

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}

}
/*
	Parse Scene Ani_set
*/
void CPlayScene::_ParseSection_SCENE_ANI_SET(string line) {

	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	int id = atof(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);

	ifstream file;
	file.open(path);

	if (file.fail())
		DebugOut(L"[ERR] Cannot open %d\n",line);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;
	char str[MAX_SCENE_LINE];
	while (file.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line[0] == '[') {
			section = SCENE_SECTION_UNKNOWN; continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}
	file.close();
	DebugOut(L"[INFO] Done loading resources %s\n", path);
}
/*

	Parse Scene Object 

*/
void CPlayScene::_ParseSection_SCENE_OBJECT(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	int id = atof(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);

	ifstream file;
	file.open(path);

	if (file.fail())
		DebugOut(L"[ERR] Cannot open %d\n", path);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;
	char str[MAX_SCENE_LINE];
	while (file.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') {
			section = SCENE_SECTION_UNKNOWN; continue;
		}

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}
	file.close();
	DebugOut(L"[INFO] Done loading resources %s\n", path);
}

void CPlayScene::Load()
{
	if (id == 2 || id == 3)
		LoadTriggerStair();

	int currentMapID = CGame::GetInstance()->GetCurrentSceneID();

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAPMATRIX]") {
			section = SCENE_SECTION_MAPMATRIX; continue; 
        }
		if (line == "[FLOOR]" || line == "[FIREPOT]" || line == "[SIMON]" || line == "[POTAL]" || line == "[ENEMY]"){
			section = SCENE_SECTION_OBJECT; continue;
        }
		if (line == "[ITEM]" || line == "[WHIP]"){
			section = SCENE_SECTION_ANI_SET; continue;
        }
		if (line == "[ENEMY]") {
			section = SCENE_SECTION_OBJECT; continue;
		}
		if (line[0] == '[') { 
			section = SCENE_SECTION_UNKNOWN; continue; }	


		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_MAPMATRIX: _ParseSection_MAPMATRIX(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_ANI_SET: _ParseSection_SCENE_ANI_SET(line); break;
			case SCENE_SECTION_OBJECT: _ParseSection_SCENE_OBJECT(line); break;
		}
	}
	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"..\\Resources\\Texture\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//to assign mapWidth
	if (currentMapID != INTRO_SCENE_ID_1 && currentMapID != INTRO_SCENE_ID_2)
	{
		int mapHeight = CMaps::GetInstance()->Get(currentMapID)->getMapHeight();
        mapWidth = CMaps::GetInstance()->Get(currentMapID)->getMapWidth();
	    RECT screen;
	    screen.left = 0;
	    screen.top = 0;
	    int offset = mapWidth > mapHeight ? mapWidth : mapHeight;
	    screen.right = screen.left + offset;
        screen.bottom = screen.top + offset;
	    qtree = new Quadtree(0, screen);
        Camera::GetInstance()->SetAreaID(currentMapID * 10 + 1);
		board = Board::Getinstance();
		Board::Getinstance()->ReloadAni();
		board->SetState_OnBoard(currentMapID);

		mapWidth = CMaps::GetInstance()->Get(currentMapID)->getMapWidth();

		switch (currentMapID) {
		case 1:
			Area::GetInstance()->SetAreaID(11);
			Area::GetInstance()->SetLimitLeftCam(LIMIT_LEFT_CAM_11);
			Area::GetInstance()->SetLimitRightCam(LIMIT_RIGHT_CAM_11);
			break;
		case 2:
			Area::GetInstance()->SetAreaID(21);
			Area::GetInstance()->SetLimitLeftCam(LIMIT_LEFT_CAM_21);
			Area::GetInstance()->SetLimitRightCam(LIMIT_RIGHT_CAM_21);
			Camera::GetInstance()->SetCamPos(0, 0);
			break;
			/*case 3:
			Area::GetInstance()->SetAreaID(31);
			break;*/
		default:
			break;
		}
    }
    DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}
void CPlayScene::LoadTriggerStair() {
	TriggerStairs *triggerStairs = TriggerStairs::GetInstance();
	triggerStairs->Add(new TriggerStair(1232, 377, TYPE_BELOW, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(1360, 247, TYPE_ABOVE, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(1424, 247, TYPE_BELOW, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(1488, 183, TYPE_ABOVE, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(1808, 183, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(1872, 247, TYPE_BELOW, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(2576, 377, TYPE_BELOW, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(2768, 183, TYPE_ABOVE, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(3408, 247, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(3536, 377, TYPE_BELOW, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(3152, 377, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(3792, 377, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(3984, 377, TYPE_BELOW, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(3856, 249, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(4304, 185, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(4368, 249, TYPE_BELOW, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(4688, 249, TYPE_ABOVE, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(4816, 377, TYPE_BELOW, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(5456, 313, TYPE_BELOW, DIRECT_RIGHT));
	triggerStairs->Add(new TriggerStair(5520, 249, TYPE_ABOVE, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(176, 152, TYPE_BELOW, DIRECT_LEFT));
	triggerStairs->Add(new TriggerStair(880, 216, TYPE_BELOW, DIRECT_LEFT));
}
void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	int currentMapID = CGame::GetInstance()->GetCurrentSceneID();
	if (currentMapID == INTRO_SCENE_ID_1 || currentMapID == INTRO_SCENE_ID_2)
	{
		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
	}
	else {
		qtree->Clear();

		for (size_t i = 0; i < objects.size(); i++)
		{
			if (delObjects.size() > 0)
			{
				std::vector<CGameObject*>::iterator it;
				it = std::find(delObjects.begin(), delObjects.end(), objects[i]);
				if (it != delObjects.end())	// Neu objects[i] thuoc mang delObjects
				{
					Board::Getinstance()->RewardingPoints(objects[i]);
					objects.erase(objects.begin() + i);
					delObjects.erase(it);
				}
				else // Neu khong thuoc mang delObjects
				{
					Entity *entity = new Entity(objects[i], 0);
					qtree->Insert(entity);
				}
			}
			else
			{
				Entity *entity = new Entity(objects[i], 0);
				qtree->Insert(entity);
			}
		}

		activeEntities.clear();
		qtree->RetrieveFromCamera(activeEntities);
		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < activeEntities.size(); i++)
		{
			coObjects.push_back(activeEntities[i]->GetGameObject());
		}
		for (size_t i = 0; i < activeEntities.size(); i++)
		{
			CGameObject *current = activeEntities[i]->GetGameObject();

			if (current->isVanish == true)
			{
				if (dynamic_cast<CFirePot*>(current)) {
					CGameObject *obj; //temp obj to create item

					CFirePot *firePot = dynamic_cast<CFirePot*>(current);

					ItemType type = firePot->GetItemType();
					obj = new Item(firePot->x, firePot->y, type);
					objects.push_back(obj);
				}
				else if (dynamic_cast<CGhost*>(current)) {
					CGameObject *obj; //temp obj to create item

					CGhost *Ghost = dynamic_cast<CGhost*>(current);

					ItemType type = Ghost->GetItemType();
					obj = new Item(Ghost->x, Ghost->y, type);
					objects.push_back(obj);
				}
				else if (dynamic_cast<CCandle*>(current)) {
					CGameObject *obj; //temp obj to create item

					CCandle *candle = dynamic_cast<CCandle*>(current);

					ItemType type = candle->GetItemType();
					obj = new Item(candle->x, candle->y, type);
					objects.push_back(obj);
				}
				else if (dynamic_cast<CBrokenBrick*>(current)) {
					CGameObject *obj; //temp obj to create item

					CBrokenBrick *brokenBrick = dynamic_cast<CBrokenBrick*>(current);

					if (brokenBrick->GetItemType() == 4 || brokenBrick->GetItemType() == 10)
					{
						ItemType type = brokenBrick->GetItemType();
						obj = new Item(brokenBrick->x, brokenBrick->y, type);
						objects.push_back(obj);
					}
				}
				delObjects.push_back(current);
			}
			else if (dynamic_cast<CEnemy*>(current)) {
				CEnemy *enemy = dynamic_cast<CEnemy*>(current);
				float eX = enemy->GetPostionX();
				int eD = enemy->GetDirect();
				float l, t, r, b;
				enemy->GetBoundingBox(l, t, r, b);
				float eBBWidth = r - l;
				float camLeftLimit = Camera::GetInstance()->GetCamX();
				float camRightLimit = Camera::GetInstance()->GetCamX() + CGame::GetInstance()->GetScreenWidth();
				if ((eX + eBBWidth <= camLeftLimit && eD < 0) || (eX >= camRightLimit && eD > 0))
				{
					current->isVanish = true;
					delObjects.push_back(current);
				}
				else
				{
					if (BlinkEffect::GetInstance()->GetIsActive())
					{
						if (enemy->GetState() != 30)
							// Conventional state for enemy: death is 30
							enemy->SetState(30);
					}
					current->Update(dt, &coObjects);
				}
			}
			else
			{
				current->Update(dt, &coObjects);
			}
		}

		CRepeatableEffects::GetInstance()->Update(dt, &coObjects);
		if (Camera::GetInstance()->GetCamX() >= 3072 && Camera::GetInstance()->GetCamX() < 4096)
		{
			Area::GetInstance()->SetAreaID(22);
			Area::GetInstance()->SetLimitLeftCam(LIMIT_LEFT_CAM_22);
			Area::GetInstance()->SetLimitRightCam(LIMIT_RIGHT_CAM_22);
		}
		else if (Camera::GetInstance()->GetCamX() >= 4096)
		{
			Area::GetInstance()->SetAreaID(23);
			Area::GetInstance()->SetLimitLeftCam(LIMIT_LEFT_CAM_23);
			Area::GetInstance()->SetLimitRightCam(LIMIT_RIGHT_CAM_23);
		}
		board->Update();
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	if (cx < -14)
	{
		player->x = -14;
	}
	if (cx > 5555)
	{
		player->x = 5555;
	}

	CGame *game = CGame::GetInstance();


	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	Camera::GetInstance()->Move(mapWidth, game->GetScreenWidth(), cx, cy, dt);
}

void CPlayScene::Render()
{
	//test cam
	// nhet camera vaoo truoc tham so alpha = 255
	if (id != INTRO_SCENE_ID_1 && id != INTRO_SCENE_ID_2)
	{
        CMaps::GetInstance()->Get(id)->Draw(Camera::GetInstance()->GetPositionVector(), 255);
		board->Render();
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	
	//Render trigger stairs
	if(id == 2)
		for (int i = 0; i < TriggerStairs::GetInstance()->GetTriggerStairs().size() - 2; i++) 
			TriggerStairs::GetInstance()->Get(i)->Render();
	else if (id == 3)
		for (int i = 20; i < TriggerStairs::GetInstance()->GetTriggerStairs().size(); i++)
			TriggerStairs::GetInstance()->Get(i)->Render();
	for (int i = 0; i < activeEntities.size(); i++)
		activeEntities[i]->GetGameObject()->Render();
	CRepeatableEffects::GetInstance()->Render();
	if (BlinkEffect::GetInstance()->GetIsActive())
	{
		int alpha;
		if (id == 1)
			alpha = 255;
		else
			alpha = 120 + rand() % 70;
		BlinkEffect::GetInstance()->Draw(alpha);
	}
    }
	else
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}

/*
Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i] = NULL;
		delete objects[i];
	}

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	Simon *simon = ((CPlayScene*)scence)->GetPlayer();
	int ID = CGame::GetInstance()->GetCurrentSceneID();

	if (ID == INTRO_SCENE_ID_1) {
		vector<LPGAMEOBJECT> objects = ((CPlayScene*)scence)->GetObjects();

		if (GetTickCount() < CASTLE_AND_BAT_ACTIVE_TIME) return;
		switch (KeyCode)
		{
		case DIK_RETURN:
			for (int i = 0; i < objects.size(); i++) {
				LPGAMEOBJECT e = objects[i];
				if (dynamic_cast<Title*> (e)) {
					if (e->GetState() == TITLE_STATE_BLINK) return;
					e->SetState(TITLE_STATE_BLINK);
				}
				if (dynamic_cast<CastleAndBat*> (e)) {
					CAnimationSets::GetInstance()->Get(0)->at(CASTLE_AND_BAT_ANI_ACTIVE)->SetLock(true);
					CAnimationSets::GetInstance()->Get(0)->at(CASTLE_AND_BAT_ANI_IDLE)->SetLock(true);
				}
			}
		}
	}
	else {
		if (ID == INTRO_SCENE_ID_2) return;
		if (simon->IsHurt()) return;
		if (simon->IsFreeze()) return;
		// disable control key when Simon die or enter an auto area
		if (simon->GetState() == SIMON_STATE_DIE || simon->GetState() == SIMON_STATE_AUTO || simon->IsAutoWalking() || simon->IsReadyToUpStair() || simon->IsReadyToDownStair()) return;
		switch (KeyCode)
		{
		case DIK_SPACE:
			if (!simon->IsJump()) {
				if (simon->IsLevelUp()) return;
				simon->SetState(SIMON_STATE_JUMP);
			}
			break;
		case DIK_A:
		{
			if (simon->IsLevelUp()) return;
			simon->SetState(SIMON_STATE_ATTACK);
			break;
		}
		case DIK_DOWN:
		{
			for (int i = 0; i < TriggerStairs::GetInstance()->GetTriggerStairs().size(); i++)
				if (TriggerStairs::GetInstance()->Get(i)->IsContainSimon() && TriggerStairs::GetInstance()->Get(i)->GetType() == 1 && !simon->IsOnStair())
					return;
			if (simon->IsLevelUp()) return;
			if (simon->IsOnStair())
				simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
			else
				simon->SetState(SIMON_STATE_SIT);
			break;
		}
		}
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->GetPlayer();

	Camera* cam = Camera::GetInstance();
	
	int ID = CGame::GetInstance()->GetCurrentSceneID();

	if (ID != INTRO_SCENE_ID_1)
	{
        if (ID == INTRO_SCENE_ID_2) return;
	// disable control key when Simon die 
	if (simon->IsHurt()) return;
	if (simon->IsFreeze()) return;
	// disable control key when Simon die or enter an auto area
	if (simon->GetState() == SIMON_STATE_DIE || simon->GetState() == SIMON_STATE_AUTO || simon->IsAutoWalking() || simon->IsReadyToUpStair() || simon->IsReadyToDownStair()) return;

		if (game->IsKeyDown(DIK_RIGHT)) {
			if (simon->IsLevelUp() || simon->IsAttack()) return;
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (simon->IsLevelUp() || simon->IsAttack()) return;
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		for (int i = 0; i < TriggerStairs::GetInstance()->GetTriggerStairs().size(); i++)
			if (TriggerStairs::GetInstance()->Get(i)->IsContainSimon() && TriggerStairs::GetInstance()->Get(i)->GetType() == 1)
				return;
		if (simon->IsLevelUp()) return;

		if (simon->IsLevelUp() || simon->IsAttack()) return;
		if (simon->IsOnStair())
			simon->SetState(SIMON_STATE_GO_DOWN_STAIR);
		else
			simon->SetState(SIMON_STATE_SIT);
	}
	else if (game->IsKeyDown(DIK_UP)) {
		if (simon->IsLevelUp()) return;
		if (simon->IsOnStair())
		{
			simon->SetState(SIMON_STATE_GO_UP_STAIR);
		}
	}
	else {
		if (simon->IsOnStair()) return;
		if(!simon->IsJump())
		simon->SetState(SIMON_STATE_IDLE);
	}
}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	Simon *simon = ((CPlayScene*)scence)->GetPlayer();
	int ID = CGame::GetInstance()->GetCurrentSceneID();

	if (ID != INTRO_SCENE_ID_1) {
        if(CGame::GetInstance()->GetCurrentSceneID() == INTRO_SCENE_ID_2) return;
		if (simon->IsHurt()) return;
	if (simon->IsFreeze()) return;
	// disable control key when Simon die or enter an auto area
	if (simon->GetState() == SIMON_STATE_DIE || simon->GetState() == SIMON_STATE_AUTO || simon->IsAutoWalking() || simon->IsReadyToUpStair() || simon->IsReadyToDownStair()) return;

	switch (KeyCode)
	{
	case DIK_DOWN:
		if (simon->IsLevelUp() || simon->IsAttack()) return;

		if (simon->IsLevelUp()) break;
		if (simon->IsAutoWalkOnStair()) break;
		/*if (simon->IsAutoWalkOnStair())
			simon->SetState(SIMON_STATE_AUTOWALK_ON_STAIR);
		else*/
			simon->SetState(SIMON_STATE_STAND);
		break;
	}
    }
}
