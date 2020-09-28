#include "Camera.h"
Camera * Camera::__instance = NULL;
Camera::Camera()
{
}

Camera::~Camera()
{
}

float Camera::getCamX()
{
	return x;
}

float Camera::getCamY()
{
	return y;
}

void Camera::setCamX(float camX)
{
	this->x = camX;
}

void Camera::setCamY(float camY)
{
	this->y = camY;
}

void Camera::setCamPos(float camX, float camY)
{
	this->x = camX;
	this->y = camY;
}

D3DXVECTOR3 Camera::createPositionVector(float _x, float _y)
{
	return D3DXVECTOR3(_x - x, _y - y, 0);
}

D3DXVECTOR3 Camera::getPositionVector()
{
	return D3DXVECTOR3(x,y,0);
}

void Camera::update(DWORD dt)
{
	x += dt * movingSpeed * hDirection;
	y += dt * movingSpeed * vDirection;
}

Camera * Camera::getInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}
