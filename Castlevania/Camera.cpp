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
	if (Simon::GetInstance()->x > 3480)
		moveCamera = true;
	else if (Simon::GetInstance()->x < 3465)
		moveCamera = false;

	// check if current player pos is in map range and update cam pos accordingly
	//if (isAuto)
	//{
	//	x += movingSpeed * dt;
	//	if (x > playerX &&  Simon::GetInstance()->x < SIMON_AUTO_GO_THROUGH_FIRST_DOOR)
	//		isAuto = false;
	//	else if (x > playerX + 285)
	//	{
	//		Simon::GetInstance()->SetAutoWalking(false);
	//		isAuto = false;
	//		moveCamera = false;
	//	}
	//}
/*	else*/ if (Area::GetInstance()->GetAreaID() == 21 && x < 2300)
	{

		if (playerX > Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 1
		{
			DebugOut(L"playerX : %f \n", playerX);

			x = playerX;
			y = 0.0f;
		}
	}
	else if (Area::GetInstance()->GetAreaID() == 22 /*&& x < 2300*/)
	{
		DebugOut(L"Rigt cam : %f \n", playerX);

		if (playerX > Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 1
		{

			x = playerX;
			y = 0.0f;
		}
	}
	else if (Area::GetInstance()->GetAreaID() == 23 /*&& x < 2300*/)
	{
		DebugOut(L"Rigt cam : %f \n", playerX);

		if (playerX > Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 1
		{

			x = playerX;
			y = 0.0f;
		}
	}
	else if (Area::GetInstance()->GetAreaID() == 31 /*&& x < 2300*/)
	{
		DebugOut(L"Rigt cam : %f \n", playerX);

		if (playerX > Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 1
		{

			x = playerX;
			y = 0.0f;
		}
	}
	else
	{
		if (playerX > 0 && playerX < (mapWidth - screenWidth - TILE_SIZE / 2) /*&& moveCamera*/) //to make sure it won't be out of range  
		{

			//cx -= game->GetScreenWidth() / 2;
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