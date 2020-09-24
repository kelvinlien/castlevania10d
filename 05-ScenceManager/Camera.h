#include <d3dx9.h>
#pragma once
class Camera
{
	static Camera * __instance;
	float x = 0.0f;
	float y = 0.0f;
	float movingSpeed = 1.0f;
	int direction = 0;
public:
	Camera();
	~Camera();
	float getCamX();
	float getCamY();
	void setCamX(float camX);
	void setCamY(float camY);
	void setCamPos(float camX, float camY);
	D3DXVECTOR3 getPositionVector(float x, float y);
	void setDirection(int d) { direction = d; };
	void update(DWORD dt);
	static Camera* getInstance();
};

