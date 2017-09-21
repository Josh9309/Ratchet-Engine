#include "Transform.h"

// For the DirectX Math library
using namespace DirectX;

Transform::Transform()
{
	//set transform values to default
	position = XMFLOAT3(0,0,0);
	rotation = XMFLOAT3(0,0,0);
	scale = XMFLOAT3(1,1,1);
}


Transform::~Transform()
{
}

DirectX::XMFLOAT3 Transform::GetPosition()
{
	return position;
}

DirectX::XMFLOAT3 Transform::GetRotation()
{
	return rotation;
}

DirectX::XMFLOAT3 Transform::GetScale()
{
	return scale;
}

void Transform::SetPosition(float x, float y, float z)
{
	position = XMFLOAT3(x, y, z);
}

void Transform::SetPosition(DirectX::XMFLOAT3 newPos)
{
	position = newPos;
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation = XMFLOAT3(x, y, z);
}

void Transform::SetRotation(DirectX::XMFLOAT3 newRot)
{
	rotation = newRot;
}

void Transform::SetScale(float x, float y, float z)
{
	scale = XMFLOAT3(x, y, z);
}

void Transform::SetScale(DirectX::XMFLOAT3 newScale)
{
	scale = newScale;
}
