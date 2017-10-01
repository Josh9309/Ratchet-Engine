#include "Material.h"



Material::Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
}

Material::Material(SimpleVertexShader* vShader, SimplePixelShader* pShader, ID3D11ShaderResourceView* text, ID3D11SamplerState* sampler)
{
	vertexShader = vShader;
	pixelShader = pShader;
	texture = text;
	samplerState = sampler;
}


Material::~Material()
{
	vertexShader;
	pixelShader;
}

SimpleVertexShader* Material::GetVShader()
{
	return vertexShader;
}

SimplePixelShader* Material::GetPShader()
{
	return pixelShader;
}

ID3D11ShaderResourceView * Material::GetTexture()
{
	return texture;
}

ID3D11SamplerState * Material::GetSampler()
{
	return samplerState;
}
