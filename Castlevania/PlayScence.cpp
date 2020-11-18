#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Camera.h"
#include "GameMap.h"

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

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_FIREPOT	3
#define OBJECT_TYPE_WHIP	4
#define OBJECT_TYPE_BRICKS_GROUP	5

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

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

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
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

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	
	int ani_set_id = atoi(tokens[3].c_str());
	int amount;
	if (object_type == 5) {
		amount = atoi(tokens[4].c_str());
	}
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = Simon::GetInstance(); 
		player = (Simon*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
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
			obj = new CBrick();
			if (currentMapID == 1)
				obj->SetPosition(x + BRICK_WIDTH * i, y);
			else
				obj->SetPosition(x + BRICK_WIDTH * 2 * i, y);

			obj->SetAnimationSet(ani_set);
			objects.push_back(obj);
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
	//case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_FIREPOT: {
		int type = atof(tokens[4].c_str());

		obj = new CFirePot(type);
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
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (!dynamic_cast<CBrick*>(obj)) {
		obj->SetPosition(x, y);

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}
		
}

void CPlayScene::Load()
{
	if (id == 2)
		LoadTriggerStair();

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
			section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[MAPMATRIX]") {
			section = SCENE_SECTION_MAPMATRIX; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }

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
		}
	}
	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"..\\Resources\\Texture\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	//to assign mapWidth
	int currentMapID = CGame::GetInstance()->GetCurrentSceneID();
	mapWidth = CMaps::GetInstance()->Get(currentMapID)->getMapWidth();
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	CGameObject *obj = new Item(100, 0, ITEM_SMALL_HEART);
	objects.push_back(obj);
	
}
void CPlayScene::LoadTriggerStair() {
	TriggerStairs *triggerStairs = TriggerStairs::GetInstance();
	TriggerStair *s0 = new TriggerStair(1232, 377, TYPE_BELOW, DIRECT_RIGHT);
	TriggerStair *s1 = new TriggerStair(1360, 247, TYPE_ABOVE, DIRECT_LEFT);
	TriggerStair *s2 = new TriggerStair(1424, 247, TYPE_BELOW, DIRECT_RIGHT);
	TriggerStair *s3 = new TriggerStair(1488, 183, TYPE_ABOVE, DIRECT_LEFT);
	TriggerStair *s4 = new TriggerStair(1808, 183, TYPE_ABOVE, DIRECT_RIGHT);
	TriggerStair *s5 = new TriggerStair(1872, 247, TYPE_BELOW, DIRECT_LEFT);
	TriggerStair *s6 = new TriggerStair(2576, 377, TYPE_BELOW, DIRECT_RIGHT);
	TriggerStair *s7 = new TriggerStair(2768, 183, TYPE_ABOVE, DIRECT_LEFT);
	TriggerStair *s8 = new TriggerStair(3408, 247, TYPE_ABOVE, DIRECT_RIGHT);
	TriggerStair *s9 = new TriggerStair(3536, 377, TYPE_BELOW, DIRECT_LEFT);
	triggerStairs->Add(s0);
	triggerStairs->Add(s1);
	triggerStairs->Add(s2);
	triggerStairs->Add(s3);
	triggerStairs->Add(s4);
	triggerStairs->Add(s5);
	triggerStairs->Add(s6);
	triggerStairs->Add(s7);
	triggerStairs->Add(s8);
	triggerStairs->Add(s9);

}
void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		 if (objects[i]->isVanish == true)
		 {
			 if (dynamic_cast<CFirePot*>(objects[i])) {
				 CGameObject *obj; //temp obj to create item

				 CFirePot *firePot = dynamic_cast<CFirePot*>(objects[i]);
				
				 ItemType type = firePot->GetItemType();
				 obj = new Item(firePot->x, firePot->y, type);
				 objects.push_back(obj);
			 }
			objects.erase(objects.begin() + i);
		 }
		else 
			objects[i]->Update(dt, &coObjects);
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

	CGame *game = CGame::GetInstance();
	 

	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	// check if current player pos is in map range and update cam pos accordingly

	if (cx > 0 && cx < (mapWidth - game->GetScreenWidth() - TILE_SIZE / 2)) //to make sure it won't be out of range
	{
		Camera::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}

}

void CPlayScene::Render()
{
	//test cam
	// nhet camera vaoo truoc tham so alpha = 255
	CMaps::GetInstance()->Get(id)->Draw(Camera::GetInstance()->GetPositionVector(), 255);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	// Bbox 2 dau cau thang
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	for (int i = 0; i < 10; i++) {
		TriggerStairs::GetInstance()->Get(i)->Render();
	}
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon *simon = ((CPlayScene*)scence)->GetPlayer();

	if (simon->GetState() == SIMON_STATE_DIE || simon->IsUp() || simon->IsDown()) return;

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
		for (int i = 0; i < 10; i++)
			if (TriggerStairs::GetInstance()->Get(i)->IsContainSimon() && TriggerStairs::GetInstance()->Get(i)->GetType() == 1)
				return;
		if (simon->IsLevelUp()) return;
		simon->SetState(SIMON_STATE_SIT);
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->GetPlayer();

	Camera* cam = Camera::GetInstance();

	// disable control key when Simon die 
	if (simon->GetState() == SIMON_STATE_DIE || simon->IsUp() || simon->IsDown()) return;

	if (game->IsKeyDown(DIK_RIGHT)) {
		if (simon->IsLevelUp() || simon->IsAttack()) return;
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (simon->IsLevelUp() || simon->IsAttack()) return;
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		for (int i = 0; i < 10; i++)
			if (TriggerStairs::GetInstance()->Get(i)->IsContainSimon() && TriggerStairs::GetInstance()->Get(i)->GetType() == 1)
				return;
		if (simon->IsLevelUp()) return;
		simon->SetState(SIMON_STATE_SIT);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	Simon *simon = ((CPlayScene*)scence)->GetPlayer();

	if (simon->GetState() == SIMON_STATE_DIE || simon->IsUp() || simon->IsDown()) return;

	switch (KeyCode)
	{
	case DIK_DOWN:
		if (simon->IsLevelUp()) break;
		simon->SetState(SIMON_STATE_STAND);
		break;
	}
}