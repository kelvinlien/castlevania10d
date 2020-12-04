#include "Camera.h"
#include "Define.h"
#include "Utils.h"
Camera * Camera::__instance = NULL;
Camera::Camera()
{
	isAuto = false;
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
	DebugOut(L"camera 's x is : %f \n", x);
	return D3DXVECTOR3(x,y,0);
}

void Camera::Move(float mapWidth, float screenWidth, float playerX, float playerY,DWORD dt)
{
	// check if current player pos is in map range and update cam pos accordingly
	if (isAuto)
	{
		x += movingSpeed * dt;
		if (x > playerX)
			isAuto = false;
	}
	else if (areaID == 21 && x<2300)
	{
		if (playerX > 0 && playerX < 2285) //cap at door - scene 2 area 1
		{
			x = playerX;
			y = 0.0f;
		}
		else
		{
			x = 2285;
		}
	}
	else{
		if (playerX > 0 && playerX < (mapWidth - screenWidth - TILE_SIZE / 2)) //to make sure it won't be out of range
		{
			x = playerX;
			y = 0.0f;
		}
	}
}

Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}
