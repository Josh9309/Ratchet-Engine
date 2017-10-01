#pragma once
#include "AssetManager.h"
#include "DXCore.h"
#include "SimpleShader.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Camera.h"
#include <DirectXMath.h>
#include "Material.h"
#include "Light.h"
#include <memory>

class Game 	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateMatrices();
	void CreateBasicGameObjects();
	void CreateBasicGeometry();
	void CreateModels();

	// Wrappers for DirectX shaders to provide simplified functionality
	//std::shared_ptr<SimpleVertexShader> vertexShader;
	//std::shared_ptr<SimplePixelShader> pixelShader;

	// The matrices to go from model space to screen space
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	//Asset Manager
	AssetManager assetManager;

	GameObject* objArray[2];

	Camera gameCamera;

	DirectionalLight directLight;
	DirectionalLight redLight;

	bool freeLookEnabled = false;	//tells whether freelook is enabled 
};

