#include "Camera.h"
#include "Define.h"
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

void Camera::Move(float mapWidth, float screenWidth, float playerX, float playerY)
{
	// check if current player pos is in map range and update cam pos accordingly
	switch (areaID)
	{
	case 21:
		//if (playerX > 0 && playerX < 2285) //cap at door - scene 2 area 1
		//{
		//	x = playerX;
		//	y = 0.0f;
		//}
		//else
		//	x = 2285;
		//break;
	default:
		if (playerX > 0 && playerX < (mapWidth - screenWidth - TILE_SIZE / 2)) //to make sure it won't be out of range
		{
			x = playerX;
			y = 0.0f;
		}
		break;
	}
}

Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}
