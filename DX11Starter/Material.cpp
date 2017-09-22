#include "Material.h"



Material::Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
}

Material::Material(SimpleVertexShader* vShader, SimplePixelShader* pShader)
{
	vertexShader = vShader;
	pixelShader = pShader;
}


Material::~Material()
{
	delete vertexShader;
	delete pixelShader;
}

SimpleVertexShader * Material::GetVShader()
{
	return vertexShader;
}

SimplePixelShader * Material::GetPShader()
{
	return pixelShader;
}
