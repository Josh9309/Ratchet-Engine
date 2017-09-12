#include "GameObject.h"

// For the DirectX Math library
using namespace DirectX;

//Only used to intitialize array needs to be replaced to have a new mesh
GameObject::GameObject()
{
	transform = new Transform(); //creates the transform component for object

	//intializes the world matrix as a default identity matrix
	XMMATRIX identity = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, identity);

	objMesh = nullptr; //sets obj Mesh null
}

GameObject::GameObject(Mesh * mesh)
{
	
	transform = new Transform();	//creates the transform component for object
	
	//intializes the world matrix as a default identity matrix
	XMMATRIX identity = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, identity);


	//set gameobject's mesh
	objMesh = mesh;
}

GameObject::~GameObject()
{
	//Clean up game object memory
	//if(transform)
		delete transform;
		transform = nullptr;
}

DirectX::XMFLOAT4X4 GameObject::GetWorldMatrix()
{
	return worldMatrix;
}

Mesh * GameObject::GetMesh()
{
	return objMesh;
}

void GameObject::SetWorldMatrix(DirectX::XMFLOAT4X4 matrix)
{
	worldMatrix = matrix;
}

void GameObject::Move(XMFLOAT3 moveAmount)
{
	transform->SetPosition(transform->position.x + moveAmount.x, transform->position.y + moveAmount.y, transform->position.z + moveAmount.z);
	CalcWorldMatrix();
}

void GameObject::Rotate(XMFLOAT3 rotateAmount)
{
	transform->SetRotation(transform->rotation.x + rotateAmount.x, transform->rotation.y + rotateAmount.y, transform->rotation.z + rotateAmount.z);
	CalcWorldMatrix();
}

void GameObject::Scale(XMFLOAT3 scaleAmount)
{
	transform->SetScale(transform->scale.x + scaleAmount.x, transform->scale.y + scaleAmount.y, transform->scale.z + scaleAmount.z);
	CalcWorldMatrix();
}

void GameObject::Render(ID3D11DeviceContext * drawContext)
{
	///Create Vertex Buffer
	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT objStride = sizeof(Vertex);
	UINT objOffset = 0;
	ID3D11Buffer* objVBuffer = objMesh->GetVertexBuffer(); //get vertex buffer address from mesh
	drawContext->IASetVertexBuffers(0, 1, &objVBuffer, &objStride, &objOffset);
	drawContext->IASetIndexBuffer(objMesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	///Render Game Object
	// Finally do the actual drawing
	//  - Do this ONCE PER OBJECT you intend to draw
	//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
	//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
	//     vertices in the currently set VERTEX BUFFER
	drawContext->DrawIndexed(
		objMesh->GetIndexCount(),	 // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices
}

void GameObject::CalcWorldMatrix()
{
	XMMATRIX trans = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
	//XMMATRIX rot = XMMatrixIdentity();
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(transform->rotation.x, transform->rotation.y, transform->rotation.z);
	XMMATRIX scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);

	XMMATRIX world = scale* rot * trans;
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(world));
}
