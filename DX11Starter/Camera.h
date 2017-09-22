#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	Camera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, float moveSpeed, float rotationSpeed );
	~Camera();
	void Update(float deltaTime);
	void CalcProjection(unsigned int width, unsigned int height);
	void RotateCamera(float xAmount, float yAmount);
	//Getters
	void GetPosition(DirectX::XMFLOAT3 * posStore);
	void GetForward(DirectX::XMFLOAT3 * forStore);
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetRotation();

	void SetPosition(DirectX::XMFLOAT3 * newPos);
	void SetRotation(float x, float y, float z);
	void SetRotation(DirectX::XMFLOAT3 newRot);

private:
	DirectX::XMVECTOR position;
	DirectX::XMVECTOR forward;			//indicate direction the camera is pointed
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projMatrix;
	float speed;
	float rotSpeed; //Camera rotation speed
};