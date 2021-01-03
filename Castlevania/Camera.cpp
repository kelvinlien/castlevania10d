#include "Camera.h"
Camera * Camera::__instance = NULL;
Camera::Camera()
{
}

Camera::~Camera()
{
}

float Camera::GetCamX()
{
	return x;
}

float Camera::GetCamY()
{
	return y;
}
float Camera::GetLeftSide()
{
	return x;
}
float Camera::GetRightSide()
{
	return x + SCREEN_WIDTH;
}
void Camera::SetCamX(float camX)
{
	this->x = camX;
}

void Camera::SetCamY(float camY)
{
	this->y = camY;
}

void Camera::SetCamPos(float camX, float camY)
{
	this->x = camX;
	this->y = camY;
}

D3DXVECTOR3 Camera::CreatePositionVector(float _x, float _y)
{
	return D3DXVECTOR3(_x - x, _y - y, 0);
}

D3DXVECTOR3 Camera::GetPositionVector()
{
	return D3DXVECTOR3(x,y,0);
}

Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}
