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
	/*DebugOut(L"camera 's x is : %f \n", x);
	DebugOut(L"PlayerX: %f\n", playerX);
	DebugOut(L"AreaID: %d\n", Area::GetInstance()->GetAreaID());
	DebugOut(L"Move camera : \n", moveCamera);*/
	return D3DXVECTOR3(x, y, 0);
}

void Camera::Move(float mapWidth, float screenWidth, float playerX, float playerY, DWORD dt)
{
	/*DebugOut(L"camera 's x is : %f \n", x);
	DebugOut(L"PlayerX: %f\n", playerX);
	DebugOut(L"AreaID: %d\n", Area::GetInstance()->GetAreaID());
	DebugOut(L"Move camera : \n", moveCamera);*/
	if (Area::GetInstance()->GetAreaID() == 21)
	{
		if (Simon::GetInstance()->x >= 3480)
			moveCamera = true;
		else if (Simon::GetInstance()->x < 3465)
			moveCamera = false;
	}
	else if (Area::GetInstance()->GetAreaID() == 22)
	{
		if (Simon::GetInstance()->x >= 4504)
			moveCamera = true;
		else if (Simon::GetInstance()->x < 4489)
			moveCamera = false;
	}
	
	// check if current player pos is in map range and update cam pos accordingly
	if (isAuto)
	{
		x += movingSpeed * dt;
		if (x > playerX)
			if((Area::GetInstance()->GetAreaID() == 21 && Simon::GetInstance()->x < SIMON_AUTO_GO_THROUGH_FIRST_DOOR) || (Area::GetInstance()->GetAreaID() == 22 && Simon::GetInstance()->x < SIMON_AUTO_GO_THROUGH_SECOND_DOOR))
				isAuto = false;
		else if (x >= playerX + 285)
		{
			Simon::GetInstance()->SetAutoWalking(false);
			isAuto = false;
			moveCamera = false;
		}
	}
	/*else if (Area::GetInstance()->GetAreaID() == 21)
	{*/
	else if (playerX >= Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 1
		{
			x = playerX;
			y = 0.0f;
		}
	//}
	//else if (Area::GetInstance()->GetAreaID() == 22)
	//{
	//	if (playerX > Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam()) //cap at door - scene 2 area 2
	//	{
	//		x = playerX;
	//		y = 0.0f;
	//	}
	//}
	//else if (Area::GetInstance()->GetAreaID() == 23)
	//{
	//	if (playerX > Area::GetInstance()->GetLimitLeftCam() && playerX < Area::GetInstance()->GetLimitRightCam())
	//	{
	//		x = playerX;
	//		y = 0.0f;
	//	}
	//}
	else
	{
		if (playerX > 0 && playerX < mapWidth - screenWidth - TILE_SIZE / 2 && moveCamera) //to make sure it won't be out of range  
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
