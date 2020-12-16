#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Game.h"
#include "Sprites.h"
#include "Textures.h"

class CMap {
	vector<vector<LPSPRITE>> titles;
	int mapWidth;					
	int mapHeight;						
	int mapID;	

public: 
	CMap() {}
	CMap(int mapID, LPCWSTR dataPath);

	void LoadMap(LPCWSTR dataPath); // load map matrix
	void Draw(D3DXVECTOR3 camPosition, int alpha); 
	int getMapWidth() { return this->mapWidth; }
};
typedef CMap * LPTILEMAP;

class CMaps
{
	static CMaps * __instance;
	unordered_map<int, LPTILEMAP> tilemaps; // quản lý các title map

public:
	void Add(LPCWSTR filePath, int ID);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }

	static CMaps * GetInstance();
};