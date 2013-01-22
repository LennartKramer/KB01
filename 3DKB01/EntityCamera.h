#ifndef __ENTITYCAMERA_H__
#define __ENTITYCAMERA_H__

#include "Entity.h"


class EntityCamera : Entity
{
public:
	EntityCamera();
	~EntityCamera(void);

	void Reset();
	void SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt );
	void SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane );
	void Move(POINT CurMousePos,bool MouseButtonPressed);


	void SetEnableYAxisMovement( bool bEnableYAxisMovement ) { m_bEnableYAxisMovement = bEnableYAxisMovement; }
	void SetEnablePositionMovement( bool bEnablePositionMovement ) { m_bEnablePositionMovement = bEnablePositionMovement; }
	void SetClipToBoundary( bool bClipToBoundary, D3DXVECTOR3* pvMinBoundary, D3DXVECTOR3* pvMaxBoundary ) { m_bClipToBoundary = bClipToBoundary; if( pvMinBoundary ) m_vMinBoundary = *pvMinBoundary; if( pvMaxBoundary ) m_vMaxBoundary = *pvMaxBoundary; }
    void SetScalers( FLOAT fRotationScaler = 0.01f)  { m_fRotationScaler = fRotationScaler; }

    // Functions to get state
    const D3DXMATRIX*  GetViewMatrix() const { return &m_mView; }
    const D3DXMATRIX*  GetProjMatrix() const { return &m_mProj; }
    const D3DXVECTOR3* GetEyePt() const      { return &m_vEye; }
    const D3DXVECTOR3* GetLookAtPt() const   { return &m_vLookAt; }
    float GetNearClip() const { return m_fNearPlane; }
    float GetFarClip() const { return m_fFarPlane; }


private:

	void                        ConstrainToBoundary( D3DXVECTOR3* pV );
    void                        UpdateMouseDelta(POINT CurMousePos);
    void                        UpdateVelocity();
    

    D3DXMATRIX m_mView;              // View matrix 
    D3DXMATRIX m_mProj;              // Projection matrix

	D3DXVECTOR3 m_vDefaultEye;          // Default camera eye position
    D3DXVECTOR3 m_vDefaultLookAt;       // Default LookAt position
    D3DXVECTOR3 m_vEye;                 // Camera eye position
    D3DXVECTOR3 m_vLookAt;              // LookAt position

    D3DXVECTOR2 m_vMouseDelta;          // Mouse relative delta smoothed over a few frames
	float m_fFramesToSmoothMouseData; // Number of frames to smooth mouse data over


    float m_fCameraYawAngle;      // Yaw angle of camera
    float m_fCameraPitchAngle;    // Pitch angle of camera

    D3DXVECTOR3 m_vVelocity;            // Velocity of camera
    D3DXVECTOR2 m_vRotVelocity;         // Velocity of camera

    float m_fFOV;                 // Field of view
    float m_fAspect;              // Aspect ratio
    float m_fNearPlane;           // Near plane
    float m_fFarPlane;            // Far plane

    float m_fRotationScaler;      // Scaler for rotation

    bool m_bEnablePositionMovement; // If true, then the user can translate the camera/model 
    bool m_bEnableYAxisMovement; // If true, then camera can move in the y-axis

    bool m_bClipToBoundary;      // If true, then the camera will be clipped to the boundary
    D3DXVECTOR3 m_vMinBoundary;         // Min point in clip boundary
    D3DXVECTOR3 m_vMaxBoundary;         // Max point in clip boundary


};

#endif