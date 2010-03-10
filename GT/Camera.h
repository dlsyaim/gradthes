#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include "Vector3D.h"

// Camera's move speed
#define MOVESPEED	20.0f
// 窗口的高度和宽度
#define Window_Width	   640
#define Window_Height	   480

class CCamera {
public:
	CCamera();
	// Used to return the camera's information
	CVector3 Position()	{ return m_vPosition;}
	CVector3 View()		{ return m_vView;}
	CVector3 UpVector()	{ return m_vUpVector;	}
	CVector3 Strafe()	{ return m_vStrafe;}

	// Initialize the camera
	void PositionCamera(float posX, float posY, float posZ,
			 		    float viewX, float viewY, float viewZ,
						float upX, float upY, float upZ);
	void PositionCamera(const CVector3 &pos, const CVector3 &view, const CVector3 &up);

	// Use gluLookAt() to position the camera in the scene.
	void Look();
	// Update camera's orientation and other information.
	void Update();
	// Update camera's orientation and other information.
	void Update(int virtualKey);
	void Update(LPPOINT lpPoint);
private:
	// Move the camera's orientation through moving mouse.
	void SetViewByMouse(void); 
	void SetViewByMouse(LPPOINT lpPoint);

	// Rotate the camera's orientation around the specified axis.
	void RotateView(float angle, const CVector3 &vAxis);

	// Move the camera to the left or the right.
	void StrafeCamera(float speed);

	// Move the camera forward and backward
	void MoveCamera(float speed);

	// Make sure the keyborad's controling of the moving of the camera.
	void CheckForMovement();
	
	// Make sure the keyborad's controling of the moving of the camera.
	void CheckForMovement(int virtualKey);

	CVector3 m_vPosition;	// Camera's position
	CVector3 m_vView;		    // Camera's viewpoint
	CVector3 m_vUpVector;	// Camera's up vector
	CVector3 m_vStrafe;		// Camera's strafe vector
};

#endif
