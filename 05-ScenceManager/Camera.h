#include <d3dx9.h>
#pragma once
class Camera
{
	static Camera * __instance;
	float x = 0.0f;
	float y = 0.0f;
public:
	Camera();
	~Camera();
	float getCamX();
	float getCamY();
	void setCamX(float camX);
	void setCamY(float camY);
	void setCamPos(float camX, float camY);
	static Camera* getInstance();
};

