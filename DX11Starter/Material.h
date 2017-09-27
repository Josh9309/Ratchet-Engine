#pragma once
#include <d3d11.h>
#include "SimpleShader.h"

class Material
{
public:
	Material();
	Material(SimpleVertexShader* vShader, SimplePixelShader* pShader, ID3D11ShaderResourceView* text, ID3D11SamplerState* sampler);
	~Material();

	//Get Methods
	SimpleVertexShader* GetVShader();
	SimplePixelShader* GetPShader();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11SamplerState* GetSampler();

private:
	ID3D11ShaderResourceView* texture;
	ID3D11SamplerState* samplerState;
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};

