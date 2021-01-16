#include <d3dx9.h>
#include "Area.h"
#include "Define.h"
#pragma once
class Camera
{
	static Camera * __instance;
	float x = 0;
	float y = 0.0f;
	// camera vx
	float movingSpeed = 0.2f;
	// horizontal direction - direction on the x axis
	int hDirection = 0;
	// areaID = sceneID * 10 + x, x is area order in that scene
	// eg: scene 2, area 2 ==> areaID = 22
	int areaID = 11;
	bool isAuto;
	bool moveCamera = true;
public:
	Camera();
	~Camera();
	float GetCamX();
	float GetCamY();
	float GetLeftSide();
	float GetRightSide();
	void SetCamX(float camX);
	void SetCamY(float camY);
	void SetCamPos(float camX, float camY);
	D3DXVECTOR3 CreatePositionVector(float x, float y);
	D3DXVECTOR3 GetPositionVector();
	void SetAreaID(int id) { areaID = id; }
	int GetAreaID() { return areaID; }
	void SetIsAuto(bool _isAuto) { isAuto = _isAuto; }
	bool GetIsAuto() { return isAuto; }
	void Move(float mapWidth, float screenWidth, float playerX, float playerY, DWORD dt);
	static Camera* GetInstance();
};