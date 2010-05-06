#include "stdafx.h"
#include "Camera.h"
#include <windows.h>
#include <gl\glut.h>
#include <math.h>

// Initialize Camera's properties. 
CCamera::CCamera()
{
	// Initialize the camera to the default direction of the OpenGL.
	CVector3 vPos(0.0f, 0.0f, 0.0f);
	CVector3 vView(0.0f, 0.0f, -1.0f);
	CVector3 vUp(0.0f, 1.0f, 0.0f);

	m_vPosition	= vPos;
	m_vView		= vView;
	m_vUpVector	= vUp;

	//SetCursorPos(Window_Width >> 1, Window_Height >> 1);
	//ShowCursor(FALSE);
}

// Set camera's position
void CCamera::PositionCamera(float posX, float posY, float posZ,
							 float viewX, float viewY, float viewZ,
							 float upX, float upY, float upZ)
{
	// Initialize the camera
	CVector3 vPos	= CVector3(posX, posY, posZ);
	CVector3 vView	= CVector3(viewX, viewY, viewZ);
	CVector3 vUp	= CVector3(upX, upY, upZ);

	m_vPosition = vPos;
	m_vView     = vView;
	m_vUpVector = vUp;

	// Normalize the vector from m_vView to m_vPosition
	m_vView = m_vPosition + (m_vView - m_vPosition).GetNormalized();
	//SetCursorPos(Window_Width >> 1, Window_Height >> 1);
}

// Set camera's position
void CCamera::PositionCamera(const CVector3 &pos, const CVector3 &view, const CVector3 &up)
{
	// Initialize the camera
	m_vPosition = pos;
	m_vView = view;
	m_vUpVector = up;

	// Normalize the vector from m_vView to m_vPosition
	m_vView = m_vPosition + (m_vView-m_vPosition).GetNormalized();
	SetCursorPos(Window_Width >> 1, Window_Height >> 1);
}

// Move the Camera's orientation through moving mouse.
void CCamera::SetViewByMouse(void)
{
	POINT mousePos;						// Struct storing the mouse's position
	//int middleX = Window_Width  >> 1;	// Half of the window's width
	//int middleY = Window_Height >> 1;	// Half of the window's height
	float angleY = 0.0f;				// Store the angle of looking up or down
	float angleZ = 0.0f;				// Store the angle of looking left or right
	static float currentRotX = 0.0f;	// Store the total angle of looking up or down.
	
	// Get the current position of the mouse.
	GetCursorPos(&mousePos);	
	// Store the origin positionn of the mouse.
	static int originX = mousePos.x;
	static int originY = mousePos.y;

	
	//// If the mouse is still in the middle of window, just return.
	//if ((mousePos.x == middleX) && (mousePos.y == middleY))
	//{
	//	return;
	//}

	// Position the mouse back to the middle of the window.
	//SetCursorPos(middleX, middleY);

	// Get the mouse's moving direction
	//angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	//angleZ = (float)((middleY - mousePos.y)) / 1000.0f;
	angleY += (float) (originX - mousePos.x) / 1000.0f;
	angleZ += (float) (originY - mousePos.y) / 1000.0f;

	originX = mousePos.x;
	originY = mousePos.y;

	// Store an angle which means rotated angle which used to limits the camera's 360 rotation of up and down.
	currentRotX -= angleZ;  

	// If larger than 1.3, no rotation
	if (currentRotX > 1.3f)
	{
		currentRotX = 1.3f;
	}
	//  If lower than -1.3, no rotation
	else if (currentRotX < -1.3f)
	{
		currentRotX = -1.3f;
	}
	// Or rotate the view line around the current position
	else
	{
		// Rotate the camera's around the strafe vector 
		RotateView(angleZ, m_vStrafe);
	}
	// Rotate the camera around the up vector 
	RotateView(angleY, CVector3(0,1,0));

}

// Move the Camera's orientation through moving mouse.
void CCamera::SetViewByMouse(LPPOINT lpPoint)
{
	POINT mousePos;						        // Struct storing the mouse's position
	int middleX = lpPoint->x;					// Half of the window's width
	int middleY = lpPoint->y;					// Half of the window's height
	float angleY = 0.0f;				                // Store the angle of looking up or down
	float angleZ = 0.0f;				                // Store the angle of looking left or right
	static float currentRotX = 0.0f;	            // Store the total angle of looking up or down.
	
	// Get the current position of the mouse.
	GetCursorPos(&mousePos);	
	// Store the origin positionn of the mouse.
	static int originX = mousePos.x;
	static int originY = mousePos.y;

	
	// If the mouse is still in the middle of window, just return.
	if ((mousePos.x == middleX) && (mousePos.y == middleY))
	{
		return;
	}

	// Position the mouse back to the middle of the window.
	SetCursorPos(middleX, middleY);

	// Get the mouse's moving direction
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;
	//angleY += (float) (originX - mousePos.x) / 1000.0f;
	//angleZ += (float) (originY - mousePos.y) / 1000.0f;

	//originX = mousePos.x;
	//originY = mousePos.y;

	// Store an angle which means rotated angle which used to limits the camera's 360 rotation of up and down.
	currentRotX -= angleZ;  

	// If larger than 1.3, no rotation
	if (currentRotX > 1.3f)
	{
		currentRotX = 1.3f;
	}
	//  If lower than -1.3, no rotation
	else if (currentRotX < -1.3f)
	{
		currentRotX = -1.3f;
	}
	// Or rotate the view line around the current position
	else
	{
		// Rotate the camera's around the strafe vector 
		RotateView(angleZ, m_vStrafe);
	}
	// Rotate the camera around the up vector 
	RotateView(angleY, CVector3(0,1,0));

}

// Rotate the camera's around the specified vector 
void CCamera::RotateView(float angle, const CVector3 &vAxis)
{
	CVector3 vNewView;
	CVector3 vView = m_vView - m_vPosition;	

	vNewView = vView.GetRotatedAxis(angle, vAxis);

	m_vView = m_vPosition + vNewView;
}

// The keyborad's controling of the moving of the camera.
void CCamera::CheckForMovement()
{	
	if (GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)
	{
		MoveCamera(MOVESPEED);		
	}

	if (GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)
	{
		MoveCamera(-MOVESPEED);		
	}
	
	if (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)
	{
		StrafeCamera(-MOVESPEED);	
	}
	
	if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)
	{
		StrafeCamera(MOVESPEED);	
	}
}

// The keyborad's controling of the moving of the camera.
void CCamera::CheckForMovement(int virtualKey)
{	
	if (virtualKey == VK_UP || virtualKey == 'W')
	{
		MoveCamera(MOVESPEED);		
	}

	if (virtualKey == VK_DOWN || virtualKey == 'S')
	{
		MoveCamera(-MOVESPEED);		
	}
	
	if (virtualKey == VK_LEFT || virtualKey == 'A')
	{
		StrafeCamera(-MOVESPEED);	
	}
	
	if (virtualKey == VK_RIGHT || virtualKey == 'D')
	{
		StrafeCamera(MOVESPEED);	
	}
}

// Move the camera to the left or the right.
void CCamera::StrafeCamera(float speed)
{
	m_vPosition.x += m_vStrafe.x * speed;
	m_vPosition.z += m_vStrafe.z * speed;
	m_vView.x += m_vStrafe.x * speed;
	m_vView.z += m_vStrafe.z * speed;
}

// Move the camera forward and backward
void CCamera::MoveCamera(float speed)
{
	CVector3 vView = m_vView - m_vPosition;
	m_vPosition.x += vView.x * speed;
	m_vPosition.z += vView.z * speed;
	//m_vPosition.y += vView.y * speed;
	m_vView.x += vView.x * speed;
	m_vView.z += vView.z * speed;
	//m_vView.y += vView.y * speed;
}

// Update the camera's orientation and other properties.
void CCamera::Update(void)
{
	// Update the camera's strafe vector
	m_vStrafe = ((m_vView - m_vPosition).CrossProduct(m_vUpVector)).GetNormalized();

	// Mouse moves camera
	SetViewByMouse();

	// Keyborad moves camera
	// Because the implementation of responsing for keyboard events is placed in another function, we comment this line of code.
	//CheckForMovement();
}

// Update the camera's orientation and other properties.
void CCamera::Update(LPPOINT lpPoint)
{
	// Update the camera's strafe vector
	m_vStrafe = ((m_vView - m_vPosition).CrossProduct(m_vUpVector)).GetNormalized();

	// Mouse moves camera
	SetViewByMouse(lpPoint);

	// Keyborad moves camera
	// Because the implementation of responsing for keyboard events is placed in another function, we comment this line of code.
	//CheckForMovement();
}

// Update camera's orientation and other information.
void CCamera::Update(int virtualKey)
{
	// Update the camera's strafe vector
	m_vStrafe = ((m_vView - m_vPosition).CrossProduct(m_vUpVector)).GetNormalized();

	// The keyboard moves camera
	CheckForMovement(virtualKey);
}


// Position the camera in the scene
void CCamera::Look(void)
{
	// Position Camera
	gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,
			  m_vView.x,	 m_vView.y,     m_vView.z,
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}