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
	material = nullptr;
}

GameObject::GameObject(Mesh * mesh, Material* mat)
{
	
	transform = new Transform();	//creates the transform component for object
	
	//intializes the world matrix as a default identity matrix
	XMMATRIX identity = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, identity);


	//set gameobject's mesh
	objMesh = mesh;
	material = mat;
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

Material * GameObject::GetMaterial()
{
	return material;
}

Transform * GameObject::GetTransform()
{
	return transform;
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
	CalcWorldMatrix();

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

/*sets up world, view, and projection matrices and sends data to buffer. 
* Then sets the vertexShader and pixelshader to active
*/
void GameObject::SetupMaterial(DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projMatrix)
{
	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	//Pass World Matrix to shader
	material->GetVShader().lock()->SetMatrix4x4("world", worldMatrix);
	material->GetVShader().lock()->SetMatrix4x4("view", viewMatrix);
	material->GetVShader().lock()->SetMatrix4x4("projection", projMatrix);
	material->GetPShader().lock()->SetShaderResourceView("diffuseTexture", material->GetTexture());
	material->GetPShader().lock()->SetSamplerState("basicSampler", material->GetSampler());

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	//Copy all Vertex shader data
	material->GetVShader().lock()->CopyAllBufferData();
	material->GetPShader().lock()->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	material->GetVShader().lock()->SetShader();
	material->GetPShader().lock()->SetShader();
}
