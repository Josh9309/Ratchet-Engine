#pragma once
#include <d3d11.h>
#include "SimpleShader.h"

class Material
{
public:
	Material();
	Material(SimpleVertexShader* vShader, SimplePixelShader* pShader);
	~Material();

	//Get Methods
	SimpleVertexShader* GetVShader();
	SimplePixelShader* GetPShader();

private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};

