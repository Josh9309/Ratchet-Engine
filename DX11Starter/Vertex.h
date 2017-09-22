#pragma once

#include <DirectXMath.h>

// --------------------------------------------------------
// A custom vertex definition
// STRUCTURE LAYOUT:
// float3 position(x,y,z)
// float2 uv
// float3 normal
// --------------------------------------------------------
struct Vertex
{
	DirectX::XMFLOAT3 Position;	    // The position of the vertex
	DirectX::XMFLOAT2 Uv;			// The uv of the vertex
	DirectX::XMFLOAT3 Normals;		// The normals of the vertex
};