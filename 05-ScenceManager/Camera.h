#include <d3dx9.h>
#pragma once
class Camera
{
	static Camera * __instance;
	float x = 0.0f;
	float y = 0.0f;
	float movingSpeed = 0.2f;
	int hDirection = 0;
	int vDirection = 0;
public:
	Camera();
	~Camera();
	float getCamX();
	float getCamY();
	void setCamX(float camX);
	void setCamY(float camY);
	void setCamPos(float camX, float camY);
	D3DXVECTOR3 getPositionVector(float x, float y);
	void setHDirection(int h) { hDirection = h; };
	void setVDirection(int v) { vDirection = v; };
	void update(DWORD dt);
	static Camera* getInstance();
};

