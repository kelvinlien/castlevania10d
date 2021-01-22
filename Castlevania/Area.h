#pragma once
#pragma once
#include <Windows.h>
#include <d3dx9.h>
#define LIMIT_LEFT_CAM_11	0
#define LIMIT_RIGHT_CAM_11	1000
#define LIMIT_LEFT_CAM_21	0
#define LIMIT_RIGHT_CAM_21	2562
#define LIMIT_LEFT_CAM_22	3072
#define LIMIT_RIGHT_CAM_22	3585
#define LIMIT_LEFT_CAM_23	4096
#define LIMIT_RIGHT_CAM_23	5104

#define RESPAWN_POS_22	3122
#define RESPAWN_POS_23	4126
class Area
{
	int areaID = 0;
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