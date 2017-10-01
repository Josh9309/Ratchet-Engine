#include "AssetManager.h"



AssetManager::AssetManager()
{
	materialLibrary = std::unordered_map<char*, Material*>();
}


AssetManager::~AssetManager()
{
	//Loop through vertex Shader Library and release Vertex Shader DX Resources
	for (auto i = vertexShaderLibrary.begin(); i != vertexShaderLibrary.end(); i++) {
		delete i->second;
	}

	//Loop through pixel Shader Library and release Pixel Shader DX Resources
	for (auto i = pixelShaderLibrary.begin(); i != pixelShaderLibrary.end(); i++) {
		delete i->second;
	}

	//Loop through Texture Library and release Texture DX Resources
	for (auto i = textureLibrary.begin(); i != textureLibrary.end(); i++) {
		i->second->Release();
	}
	//Loop through Texture Sampler Library and release Sampler DX Resources
	for (auto i = textureSamplerLibrary.begin(); i != textureSamplerLibrary.end(); i++) {
		i->second->Release();
	}
	//Loops through material library and deletes all material Pointers
	for (auto i = materialLibrary.begin(); i != materialLibrary.end(); i++) {
		Material* mat;
		mat = i->second;
		delete mat;
	}

	//Loop through Mesh Library and delete all mesh Pointers
	for (auto i = meshLibrary.begin(); i != meshLibrary.end(); i++) {
		Mesh* mesh;
		mesh = i->second;
		delete mesh;
	}
}

void AssetManager::ImportVShader(char * vShaderName, SimpleVertexShader * vShader)
{
	vertexShaderLibrary[vShaderName] = vShader;
}

void AssetManager::ImportPShader(char * pShaderName, SimplePixelShader * pShader)
{
	pixelShaderLibrary[pShaderName] = pShader;
}

void AssetManager::ImportTexture(char * textureName, ID3D11ShaderResourceView * texture)
{
	textureLibrary[textureName] = texture;
}

void AssetManager::ImportSampler(char * textSamplerName, ID3D11SamplerState * sampler)
{
	textureSamplerLibrary[textSamplerName] = sampler;
}

void AssetManager::ImportMaterial(char* matName, Material* materialPtr)
{
	materialLibrary[matName] = materialPtr;
}

void AssetManager::ImportMesh(char * meshName, Mesh * meshPtr)
{
	meshLibrary[meshName] = meshPtr;
}

SimpleVertexShader * AssetManager::GetVShader(char * vShaderName)
{
	return vertexShaderLibrary[vShaderName];
}

SimplePixelShader * AssetManager::GetPShader(char * pShaderName)
{
	return pixelShaderLibrary[pShaderName];
}

ID3D11ShaderResourceView * AssetManager::GetTexture(char * textureName)
{
	return textureLibrary[textureName];
}

ID3D11SamplerState * AssetManager::GetSampler(char * samplerName)
{
	return textureSamplerLibrary[samplerName];
}

Material * AssetManager::GetMaterial(char * materialName)
{
	return materialLibrary[materialName];
}

Mesh * AssetManager::GetMesh(char * meshName)
{
	return meshLibrary[meshName];
}

