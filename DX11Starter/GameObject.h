#pragma once
#include <d3d11.h>		//included to gain access to direct X Variables
#include <DirectXMath.h>
#include "Transform.h" 
#include "Mesh.h"
#include "Material.h"

class GameObject
{
public:
	GameObject();
	GameObject(Mesh* mesh, Material* mat);
	~GameObject();

	//Properties for worldMatrix
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	void SetWorldMatrix(DirectX::XMFLOAT4X4 matrix);

	Mesh* GetMesh();
	Material* GetMaterial();
	Transform* GetTransform();

	//Transform Methods
	void Move(DirectX::XMFLOAT3 moveAmount);
	void Rotate(DirectX::XMFLOAT3 rotateAmount);
	void Scale(DirectX::XMFLOAT3 scaleAmount);

	//Render
	void Render(ID3D11DeviceContext* drawContext);

	void CalcWorldMatrix();

	void SetupMaterial(DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projMatrix);

private:
	Transform* transform; //transform class component that holds the contains the position, rotation, scale
	DirectX::XMFLOAT4X4 worldMatrix;
	Mesh* objMesh; //holds the Gameobjects mesh
	Material* material;
};

