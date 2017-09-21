#pragma once
#include <d3d11.h>		//included to gain access to direct X Variables
#include "Vertex.h"		//include to gain access to vertex struct

class Mesh
{
public:
	Mesh(
		Vertex* vertices,			//holds a array of Vertex objects that are used for mesh
		int numVertices,			//Tells Mesh how many Vertex objects are in mesh's vertices array
		unsigned int* indicies,		//Holds array of indices for telling the order to draw vertices in
		int numIndices,				//Tells Mesh how many indices are in Index Array
		ID3D11Device* drawDevice);		//Reference to directX 11 Device need to create buffers
	~Mesh(); //Releases DirectX Buffers

	//Getters for private variables
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetVerticesCount();
	int GetIndexCount();

private:
	ID3D11Buffer* vertexBufferPtr;
	ID3D11Buffer* indexBufferPtr;
	int vertexCount;
	int indexCount;
};

