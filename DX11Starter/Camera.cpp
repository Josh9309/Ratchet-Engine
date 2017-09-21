#include "Camera.h"
#include <Windows.h>

using namespace DirectX;

Camera::Camera()
{
	position = XMVectorZero();
	forward = XMVectorZero();
	rotation = XMFLOAT3(0, 0, 0);
	speed = 1;

	//Intialize View Matrix
	//Direct X uses XMVectors to represent Quaternions
	XMVECTOR viewQuaternion = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //calculates rotation quaternion based off rotation

	XMFLOAT3 unitForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMVECTOR defaultForward = XMLoadFloat3(&unitForward);
	forward = XMVector3Rotate(defaultForward, viewQuaternion);

	//Create temp Vectors for look to method
	XMFLOAT3 up = XMFLOAT3(0, 1.0f, 0);
	XMVECTOR upVector = XMLoadFloat3(&up);
	XMMATRIX viewMat = XMMatrixLookToLH(position, forward, upVector);

	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(viewMat)); //stores matrix in to 4x4 XMFLOAT version

}

Camera::Camera(DirectX::XMFLOAT3  pos, DirectX::XMFLOAT3 rot, float moveSpeed, float rotationSpeed)
{
	position = XMLoadFloat3(&pos);
	forward = XMVectorZero();
	rotation = rot;
	speed = moveSpeed;
	rotSpeed = rotationSpeed;

	//Intialize View Matrix
	//Direct X uses XMVectors to represent Quaternions
	XMVECTOR viewQuaternion = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //calculates rotation quaternion based off rotation

	XMFLOAT3 unitForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMVECTOR defaultForward = XMLoadFloat3(&unitForward);
	forward = XMVector3Rotate(defaultForward, viewQuaternion);

	//Create temp Vectors for look to method
	XMFLOAT3 up = XMFLOAT3(0, 1.0f, 0);
	XMVECTOR upVector = XMLoadFloat3(&up);
	XMMATRIX viewMat = XMMatrixLookToLH(position, forward, upVector);

	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(viewMat)); //stores matrix in to 4x4 XMFLOAT version
}

Camera::~Camera()
{
}

/*Updates the camera's View Matrix based on Current rotation
*/
void Camera::Update(float deltaTime)
{
	//Direct X uses XMVectors to represent Quaternions
	XMVECTOR viewQuaternion = XMQuaternionRotationRollPitchYaw(rotation.x,rotation.y, rotation.z); //calculates rotation quaternion based off rotation
	
	XMFLOAT3 unitForward = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMVECTOR defaultForward = XMLoadFloat3(&unitForward);
	forward = XMVector3Rotate(defaultForward, viewQuaternion);

	//Create temp Vectors for look to method
	XMFLOAT3 up = XMFLOAT3(0, 1.0f, 0);
	XMVECTOR upVector = XMLoadFloat3(&up);
	XMMATRIX viewMat = XMMatrixLookToLH(position, forward, upVector);

	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(viewMat)); //stores matrix in to 4x4 XMFLOAT version

	//KEYBOARD INPUT
	XMVECTOR normForward = XMVector3Normalize(forward);	//Normalize forward vector for movement
	if(GetAsyncKeyState('W')& 0x8000) //The 0x8000 is necessacry because the function contains muliple pieces of info in a short value
	{
		//Move Forwards
		
		position += (normForward*speed)*deltaTime;
	}
	else if (GetAsyncKeyState('S') & 0x8000) 
	{
		//Move Backwards
		position += (-normForward*speed)*deltaTime;
	}
	if (GetAsyncKeyState('A') & 0x8000) 
	{
		//Move Left
		XMVECTOR left = XMVector3Cross(forward, upVector);
		left = XMVector3Normalize(left);
		position += (left*speed)*deltaTime;
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		//Move Left
		XMVECTOR right = XMVector3Cross(upVector, forward);
		right = XMVector3Normalize(right);
		position += (right*speed)*deltaTime;
	}
}

void Camera::CalcProjection(float width, float height)
{
	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

void Camera::RotateCamera(float xAmount, float yAmount)
{
	float xScaled = xAmount / 200;
	float yScaled = yAmount / 200;
	rotation.x += xScaled * rotSpeed;
	rotation.y += yScaled * rotSpeed ;

	if (rotation.x > 360) 
	{
		rotation.x = 360.0f;
	}
	else if (rotation.x < 0) {
		rotation.x = 0.0f;
	}

	if (rotation.y > 360)
	{
		rotation.y = 360.0f;
	}
	else if (rotation.y < 0) {
		rotation.y = 0.0f;
	}
}

void Camera::GetPosition(XMFLOAT3 * posStore)
{
	XMStoreFloat3(posStore, position);
}

void Camera::GetForward(XMFLOAT3 * forStore)
{
}

DirectX::XMFLOAT4X4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix()
{
	return projMatrix;
}

XMFLOAT3 Camera::GetRotation()
{
	return XMFLOAT3();
}

void Camera::SetPosition(XMFLOAT3 * newPos)
{
	position = XMLoadFloat3(newPos);
}

void Camera::SetRotation(float x, float y, float z)
{
	rotation = XMFLOAT3(x, y, z);
}

void Camera::SetRotation(DirectX::XMFLOAT3 newRot)
{
	rotation = newRot;
}

