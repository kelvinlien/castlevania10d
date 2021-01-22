#include "Camera.h"
#include "Define.h"
#include "Utils.h"
#include "Simon.h"
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
	return D3DXVECTOR3(x, y, 0);
}

void Camera::Move(float mapWidth, float screenWidth, float playerX, float playerY, DWORD dt)
{	
	// check if current player pos is in map range and update cam pos accordingly
	if (isAuto)
	{
		x += movingSpeed * dt;
		if (x > playerX && ((Area::GetInstance()->GetAreaID() == 21 && Simon::GetInstance()->x < SIMON_AUTO_GO_THROUGH_FIRST_DOOR) || (Area::GetInstance()->GetAreaID() == 22 && Simon::GetInstance()->x < SIMON_AUTO_GO_THROUGH_SECOND_DOOR)))
			isAuto = false;

		else if (x >= playerX + 150)
		{
			Simon::GetInstance()->SetAutoWalking(false);
			isAuto = false;
		}
	}
	else if (playerX >= Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 1
	{
		x = playerX;
		y = 0.0f;
	}
	DebugOut(L"Cam x, Simon x, playerX, area id and Area limits %f %f %f %d %f %f\n", this->x, Simon::GetInstance()->x, playerX, Area::GetInstance()->GetAreaID(),Area::GetInstance()->GetLimitLeftCam(), Area::GetInstance()->GetLimitRightCam());
}

Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}
