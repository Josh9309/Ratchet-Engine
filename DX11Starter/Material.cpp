#include "Material.h"



Material::Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
}

Material::Material(std::weak_ptr<SimpleVertexShader> vShader, std::weak_ptr<SimplePixelShader> pShader, ID3D11ShaderResourceView* text, ID3D11SamplerState* sampler)
{
	vertexShader = vShader.lock();
	pixelShader = pShader.lock();
	texture = text;
	samplerState = sampler;
}


Material::~Material()
{
	vertexShader.reset();
	pixelShader.reset();
	texture->Release();
	samplerState->Release();
}

std::weak_ptr<SimpleVertexShader> Material::GetVShader()
{
	std::weak_ptr<SimpleVertexShader> vShader = vertexShader;
	return vShader;
}

std::weak_ptr<SimplePixelShader> Material::GetPShader()
{
	std::weak_ptr<SimplePixelShader> pShader = pixelShader;
	return pShader;
}

ID3D11ShaderResourceView * Material::GetTexture()
{
	return texture;
}

ID3D11SamplerState * Material::GetSampler()
{
	return samplerState;
}
