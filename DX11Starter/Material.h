#pragma once
#include <d3d11.h>
#include "SimpleShader.h"
#include <memory>

class Material
{
public:
	Material();
	Material(std::weak_ptr<SimpleVertexShader> vShader, std::weak_ptr<SimplePixelShader> pShader, ID3D11ShaderResourceView* text, ID3D11SamplerState* sampler);
	~Material();

	//Get Methods
	std::weak_ptr<SimpleVertexShader> GetVShader();
	std::weak_ptr<SimplePixelShader> GetPShader();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11SamplerState* GetSampler();

private:
	ID3D11ShaderResourceView* texture;
	ID3D11SamplerState* samplerState;
	std::shared_ptr<SimpleVertexShader> vertexShader;
	std::shared_ptr<SimplePixelShader> pixelShader;
};

