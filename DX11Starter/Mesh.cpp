#include "Mesh.h"


Mesh::Mesh(Vertex * vertices, int numVertices, unsigned int * indicies, int numIndices, ID3D11Device * drawDevice)
{
	//Create DX11 Vertex Buffer

	D3D11_BUFFER_DESC vbd;	//Vertex Buffer Description (Only needed when we create buffer)
	vbd.Usage = D3D11_USAGE_IMMUTABLE;	//Tells DirectX that we will not change data stored in buffer
	vbd.ByteWidth = sizeof(Vertex) * numVertices;	//tells DX how many Vertices will be stored in buffer so it can allocate the neccesary memory required
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//Tells DX that this is a Vertex Buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA ivd; // creates Struct to put inital vertex data into buffer
	ivd.pSysMem = vertices; 

	drawDevice->CreateBuffer(&vbd, &ivd, &vertexBufferPtr);
	
	vertexCount = numVertices; //update the vertex count

	//Create DX11 Index Buffer
	D3D11_BUFFER_DESC ibd;	//Index Buffer Description (Only needed when we create buffer)
	ibd.Usage = D3D11_USAGE_IMMUTABLE;	//Tells DirectX that we will not change data stored in buffer
	ibd.ByteWidth = sizeof(int) * numIndices; //tells DX how many Indices will be stored in buffer so it can allocate the neccesary memory required
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; //Tells DX that this is a Index Buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData; //creates struct to put initial index data into Buffer
	initialIndexData.pSysMem = indicies;

	drawDevice->CreateBuffer(&ibd, &initialIndexData, &indexBufferPtr);

	indexCount = numIndices; //update index count
}

Mesh::~Mesh()
{
	//Call Release on Buffers To clean up memory when Mesh is done
	vertexBufferPtr->Release();
	indexBufferPtr->Release();
}

ID3D11Buffer * Mesh::GetVertexBuffer()
{
	return vertexBufferPtr;
}

ID3D11Buffer * Mesh::GetIndexBuffer()
{
	return indexBufferPtr;
}

int Mesh::GetVerticesCount()
{
	return vertexCount;
}

int Mesh::GetIndexCount()
{
	return indexCount;
}
