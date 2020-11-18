#include <d3dx9.h>
#pragma once
class Camera
{
	static Camera * __instance;
	float x = 0.0f;
	float y = 0.0f;
	float movingSpeed = 0.2f;
	int hDirection = 0;
public:
	Camera();
	~Camera();
	float GetCamX();
	float GetCamY();
	void SetCamX(float camX);
	void SetCamY(float camY);
	void SetCamPos(float camX, float camY);
	D3DXVECTOR3 CreatePositionVector(float x, float y);
	D3DXVECTOR3 GetPositionVector();
	static Camera* GetInstance();
};

