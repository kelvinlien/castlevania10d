#include "GameMap.h"
#include "Define.h"
#include <string> 
#include "Utils.h"
#include "Sprites.h"
CMaps * CMaps::__instance = NULL;

CMaps *CMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CMaps();
	return __instance;
}


CMap::CMap(int mapID, LPCWSTR dataPath) {
	this->mapID = mapID;
	this->LoadMap(dataPath);
}

void CMap::LoadMap(LPCWSTR dataPath) {
	CSprites *sprites = CSprites::GetInstance();
	fstream fs;

	fs.open(dataPath, ios::in);

	if (fs.fail()) {
		fs.close();
		return;
	}

	string line;
	getline(fs, line);
	stringstream ss(line);
	ss >> this->mapWidth >> this->mapHeight;

	while (!fs.eof())
	{
		getline(fs, line);

		vector<LPSPRITE> mapSprites;
		stringstream ss(line);
		int n;
		int idTile;

		while (ss >> n)
		{
			idTile = n + 1000;
			mapSprites.push_back(sprites->Get(idTile));
		}
		titles.push_back(mapSprites);
	}
	fs.close();
}

void CMaps::Add(LPCWSTR dataPath, int ID)
{
	LPTILEMAP tilemap = new CMap(ID, dataPath);
	tilemaps[ID] = tilemap;
}

void CMap::Draw(D3DXVECTOR3 camPosition, int alpha) {

	int startCol = (int)camPosition.x / 32;
	int endCol = startCol + SCREEN_WIDTH / 32;
	int numOfRow = titles.size();
	for (int i = 0; i < numOfRow ; i++)
	{
		for (int j = startCol; j <= endCol; j++)
		{
			// +camPosition.x để luôn giữ camera ở chính giữa, vì trong hàm Game::Draw() có trừ cho camPosition.x làm các object đều di chuyển theo
			// +(int)camPosition.x % 32 để giữ cho camera chuyển động mượt
			float x = TILE_SIZE * (j - startCol) + camPosition.x - (int)camPosition.x % 32;
			float y = TILE_SIZE * i + 80;
			titles[i][j]->Draw(x, y, D3DCOLOR_ARGB(alpha, 255, 255, 255));
		}
	}
}
