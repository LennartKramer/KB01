#ifndef __ENTITYCAMERA_H__
#define __ENTITYCAMERA_H__

#include "Entity.h"


class EntityCamera : Entity
{
public:
	EntityCamera();
	~EntityCamera(void);

	void                Reset();
	void                SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt );
	void                SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane );
	void                Move(POINT CurMousePos,bool MouseButtonPressed);
	void SetDragRect( RECT &rc ) { m_rcDrag = rc; }


	void SetInvertPitch( bool bInvertPitch ) { m_bInvertPitch = bInvertPitch; }
	void SetDrag(FLOAT fTotalDragTimeToZero = 0.25f){ m_fTotalDragTimeToZero = fTotalDragTimeToZero;}
	//void SetDrag( bool bMovementDrag, FLOAT fTotalDragTimeToZero = 0.25f ) { m_bMovementDrag = bMovementDrag; m_fTotalDragTimeToZero = fTotalDragTimeToZero; }
	void SetEnableYAxisMovement( bool bEnableYAxisMovement ) { m_bEnableYAxisMovement = bEnableYAxisMovement; }
	void SetEnablePositionMovement( bool bEnablePositionMovement ) { m_bEnablePositionMovement = bEnablePositionMovement; }
	void SetClipToBoundary( bool bClipToBoundary, D3DXVECTOR3* pvMinBoundary, D3DXVECTOR3* pvMaxBoundary ) { m_bClipToBoundary = bClipToBoundary; if( pvMinBoundary ) m_vMinBoundary = *pvMinBoundary; if( pvMaxBoundary ) m_vMaxBoundary = *pvMaxBoundary; }
    void SetScalers( FLOAT fRotationScaler = 0.01f, FLOAT fMoveScaler = 5.0f )  { m_fRotationScaler = fRotationScaler; m_fMoveScaler = fMoveScaler; }
    void SetNumberOfFramesToSmoothMouseData( int nFrames ) { if( nFrames > 0 ) m_fFramesToSmoothMouseData = (float)nFrames; }
    void SetResetCursorAfterMove( bool bResetCursorAfterMove ) { m_bResetCursorAfterMove = bResetCursorAfterMove; }

    // Functions to get state
    const D3DXMATRIX*  GetViewMatrix() const { return &m_mView; }
    const D3DXMATRIX*  GetProjMatrix() const { return &m_mProj; }
    const D3DXVECTOR3* GetEyePt() const      { return &m_vEye; }
    const D3DXVECTOR3* GetLookAtPt() const   { return &m_vLookAt; }
    float GetNearClip() const { return m_fNearPlane; }
    float GetFarClip() const { return m_fFarPlane; }

	//D3DXMATRIX*  GetWorldMatrix()            { return &m_mCameraWorld; }

    //const D3DXVECTOR3* GetWorldRight() const { return (D3DXVECTOR3*)&m_mCameraWorld._11; } 
    //const D3DXVECTOR3* GetWorldUp() const    { return (D3DXVECTOR3*)&m_mCameraWorld._21; }
    //const D3DXVECTOR3* GetWorldAhead() const { return (D3DXVECTOR3*)&m_mCameraWorld._31; }


private:
	//CameraKeys  MapKey( UINT nKey );
	//bool IsKeyDown( BYTE key ) const { return( (key & KEY_IS_DOWN_MASK) == KEY_IS_DOWN_MASK ); }
    // bool WasKeyDown( BYTE key ) const { return( (key & KEY_WAS_DOWN_MASK) == KEY_WAS_DOWN_MASK ); }

	//void GetInput(bool bGetKeyboardInput, bool bGetMouseInput,bool bResetCursorAfterMove);
    
	void GetInput(bool bGetMouseInput);
	void                        ConstrainToBoundary( D3DXVECTOR3* pV );
    void                        UpdateMouseDelta(POINT CurMousePos);
    void                        UpdateVelocity();
    

    D3DXMATRIX m_mView;              // View matrix 
    D3DXMATRIX m_mProj;              // Projection matrix

	D3DXVECTOR3 m_vDefaultEye;          // Default camera eye position
    D3DXVECTOR3 m_vDefaultLookAt;       // Default LookAt position
    D3DXVECTOR3 m_vEye;                 // Camera eye position
    D3DXVECTOR3 m_vLookAt;              // LookAt position

    //int m_cKeysDown;            // Number of camera keys that are down.
    //BYTE                        m_aKeys[CAM_MAX_KEYS];  // State of input - KEY_WAS_DOWN_MASK|KEY_IS_DOWN_MASK
    //D3DXVECTOR3 m_vKeyboardDirection;   // Direction vector of keyboard input
    //POINT m_ptLastMousePosition;  // Last absolute position of mouse cursor 
    D3DXVECTOR2 m_vMouseDelta;          // Mouse relative delta smoothed over a few frames
	float m_fFramesToSmoothMouseData; // Number of frames to smooth mouse data over



    float m_fCameraYawAngle;      // Yaw angle of camera
    float m_fCameraPitchAngle;    // Pitch angle of camera

    RECT m_rcDrag;               // Rectangle within which a drag can be initiated.
    D3DXVECTOR3 m_vVelocity;            // Velocity of camera
    //bool m_bMovementDrag;        // If true, then camera movement will slow to a stop otherwise movement is instant
    D3DXVECTOR3 m_vVelocityDrag;        // Velocity drag force
    FLOAT m_fDragTimer;           // Countdown timer to apply drag
    FLOAT m_fTotalDragTimeToZero; // Time it takes for velocity to go from full to 0
    D3DXVECTOR2 m_vRotVelocity;         // Velocity of camera

    float m_fFOV;                 // Field of view
    float m_fAspect;              // Aspect ratio
    float m_fNearPlane;           // Near plane
    float m_fFarPlane;            // Far plane

    float m_fRotationScaler;      // Scaler for rotation
    float m_fMoveScaler;          // Scaler for movement

    bool m_bInvertPitch;         // Invert the pitch axis
    bool m_bEnablePositionMovement; // If true, then the user can translate the camera/model 
    bool m_bEnableYAxisMovement; // If true, then camera can move in the y-axis

    bool m_bClipToBoundary;      // If true, then the camera will be clipped to the boundary
    D3DXVECTOR3 m_vMinBoundary;         // Min point in clip boundary
    D3DXVECTOR3 m_vMaxBoundary;         // Max point in clip boundary

    bool m_bResetCursorAfterMove;// If true, the class will reset the cursor position so that the cursor always has space to move 

	D3DXMATRIX m_mCameraWorld;       // World matrix of the camera (inverse of the view matrix)

};

#endif