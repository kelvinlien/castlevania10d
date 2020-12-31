#pragma once
#pragma once
#include <Windows.h>
#include <d3dx9.h>
#define LIMIT_LEFT_CAM_11	0
#define LIMIT_RIGHT_CAM_11	2285
#define LIMIT_LEFT_CAM_21	0
#define LIMIT_RIGHT_CAM_21	2285
#define LIMIT_LEFT_CAM_22	3072
#define LIMIT_RIGHT_CAM_22	3310
#define LIMIT_LEFT_CAM_23	4076
#define LIMIT_RIGHT_CAM_23	4864
#define LIMIT_LEFT_CAM_31	0
#define LIMIT_RIGHT_CAM_31	2285
class Area
{
	int areaID = 21;
	float spawnPosX = 50;
	float spawnPosY = 0;
	float limitLeftCam = 0;
	float limitRightCam;

	static Area * __instance;
public:
	Area() {};

	int GetAreaID() { return areaID; }
	float GetSpawnPosX() { return spawnPosX; }
	float GetSpawnPosY() { return spawnPosY; }
	float GetLimitLeftCam() { return limitLeftCam; }
	float GetLimitRightCam() { return limitRightCam; }

	void SetSpawnPos();
	void SetAreaID(int areaID) { this->areaID = areaID; }
	void SetLimitLeftCam(float limitLeftCam) { this->limitLeftCam = limitLeftCam; }
	void SetLimitRightCam(float limitRightCam) { this->limitRightCam = limitRightCam; }

	static Area* GetInstance();

};
