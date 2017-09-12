#pragma once
#include <d3d11.h>		//included to gain access to direct X Variables
#include <DirectXMath.h>

class Transform
{
public:
	Transform();
	~Transform();

	//Holds vect3 of the position, rotation, and scale for game object
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	//Properties Methods for Transform attributes
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();
	void SetPosition(float x, float y, float z);
	void SetPosition(DirectX::XMFLOAT3 newPos);
	void SetRotation(float x, float y, float z);
	void SetRotation(DirectX::XMFLOAT3 newRot);
	void SetScale(float x, float y, float z);
	void SetScale(DirectX::XMFLOAT3 newScale);

private: 
	
};

