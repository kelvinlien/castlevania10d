#pragma once
#pragma once
#include <Windows.h>
#include <d3dx9.h>

class Area
{
	int areaID;
	float spawnPos = 50;
	float limitLeftCam = 0;
	float limitRightCam;

	static Area * __instance;
public:
	Area() {};

	int GetAreaID() { return areaID; }
	float GetSpawnPos() { return spawnPos; }
	float GetLimitLeftCam() { return limitLeftCam; }
	float GetLimitRightCam() { return limitRightCam; }

	void SetAreaID(int areaID) { this->areaID = areaID; }
	void SetSpawnPos(float spawnPos) { this->spawnPos = spawnPos; }
	void SetLimitLeftCam(float limitLeftCam) { this->limitLeftCam = limitLeftCam; }
	void SetLimitRightCam(float limitRightCam) { this->limitRightCam = limitRightCam; }

	static Area* GetInstance();

};
