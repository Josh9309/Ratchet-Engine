#pragma once
#include <d3d11.h>
#include <map>
#include "Mesh.h"
#include "Material.h"
#include "SimpleShader.h"

/* Summary: The Ratchet Asset Manager is responsible for holding all materials, textures, sounds,etc ...
* 
*/

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	//Create Methods

	//Add Methods
	void ImportVShader(char* vShaderName, SimpleVertexShader* vShader);
	void ImportPShader(char* pShaderName, SimplePixelShader* pShader);
	void ImportTexture(char* textureName, ID3D11ShaderResourceView* texture);
	void ImportSampler(char* textSamplerName, ID3D11SamplerState* sampler);
	void ImportMaterial(char * matName, Material * materialPtr);
	void ImportMesh(char* meshName, Mesh* meshPtr);

	//Get Methods
	SimpleVertexShader* GetVShader(char* vShaderName);
	SimplePixelShader* GetPShader(char* pShaderName);
	ID3D11ShaderResourceView* GetTexture(char* textureName);
	ID3D11SamplerState* GetSampler(char* samplerName);
	Material* GetMaterial(char* materialName);
	Mesh* GetMesh(char* meshName);

private:
	std::unordered_map<char*, SimpleVertexShader*> vertexShaderLibrary;
	std::unordered_map<char*, SimplePixelShader*> pixelShaderLibrary;
	std::unordered_map<char*, ID3D11ShaderResourceView*> textureLibrary;
	std::unordered_map<char*, ID3D11SamplerState*> textureSamplerLibrary;
	std::unordered_map<char*, Material*> materialLibrary;
	std::unordered_map<char*, Mesh*> meshLibrary;
	
};

