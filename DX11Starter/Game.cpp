#include "Game.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Release any (and all!) DirectX objects
	// we've made in the Game class

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff

	//delete Meshes
	delete triangle;
	delete square;
	delete pentagon;
	delete cone;
	delete cube;
	delete cylinder;
	delete helix;
	delete sphere;
	delete torus;

	//delete Materials
	delete genericMat;

	//delete Gameobjects
	for (int i = 0; i < 8; i++) {
		delete objArray[i];
	}
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();
	
	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create Material 
	genericMat = new Material(vertexShader, pixelShader);
	CreateModels();
	//Create Gameobjects
	//CreateBasicGameObjects();

	//Creates game Camera
	gameCamera = Camera(XMFLOAT3(0,0, -5.0f),XMFLOAT3(0,0,0), 1.5, 0.5);
	gameCamera.CalcProjection(width, height);	//Makes sure projection matrix is calculated

	//Create directional Light
	directLight = { XMFLOAT4(0.1,0.1,0.1,1.0), XMFLOAT4(0,0,1,1), XMFLOAT3(1,-1,0) };

}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

void Game::CreateBasicGameObjects()
{

	//make Triangle Game Objects
	for (int i = 0; i < 3; i++) {
		objArray[i] = new GameObject(triangle, genericMat);
		objArray[i]->GetTransform()->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		objArray[i]->GetTransform()->SetPosition(XMFLOAT3(-2.5f, 0.0f, 0.0f));
		//GameObject tri(triangle);
		//memcpy(objArray + i, &tri, sizeof(GameObject));
	}

	////Make Square GameObjects
	for (int i = 3; i < 6; i++) {
		objArray[i] = new GameObject(square, genericMat);
		objArray[i]->GetTransform()->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		objArray[i]->GetTransform()->SetPosition(XMFLOAT3(+2.7f, 0.0f, 0.0f));
	}

	////Make Pentagon GameObjects
	for (int i = 6; i < 8; i++) {
		objArray[i] = new GameObject(pentagon, genericMat);
	}

}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 purple = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 yellow = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	//Set up Triangle Mesh
	//Set up vertices for Triangle
	Vertex triangleVertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },  //position(float3), uv(float2), normal(float3)
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
	};

	//Set up Indices for Triangle
	unsigned int triangleIndices[] = { 0, 1, 2 };

	triangle = new Mesh(triangleVertices, 3, triangleIndices, 3, device);

	//Set up Square mesh
	//Setup vertices for square
	Vertex squareVertices[] =
	{
		{XMFLOAT3(-1.0f, +1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(+1.0f, +1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(+1.0f, -1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(-1.0f, -1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
	};

	//setup indices for square
	unsigned int squareIndices[] = { 0,1,2,0,2,3 };

	square = new Mesh(squareVertices, 4, squareIndices, 6, device);

	//Setup Pentagon Mesh
	//Setup Pentagon Vertices
	Vertex pentagonVertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.5f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(+1.5f, +0.5f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(+1.0f, -1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(-1.0f, -1.0f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
		{ XMFLOAT3(-1.5f, +0.5f, +0.0f), XMFLOAT2(0,0), XMFLOAT3(0,0,-1) },
	};

	//Setup Indices for Pentagon
	unsigned int pentaIndices[] = {
		4,0,1,
		4,1,2,
		4,2,3,
	};

	pentagon = new Mesh(pentagonVertices, 5, pentaIndices, 9, device);
}

void Game::CreateModels()
{
	cone = new Mesh("../../DX11Starter/Assets/Models/cone.obj", device);
	cube = new Mesh("../../DX11Starter/Assets/Models/cube.obj", device);
	cylinder = new Mesh("../../DX11Starter/Assets/Models/cylinder.obj", device);
	helix = new Mesh("../../DX11Starter/Assets/Models/helix.obj", device);
	sphere = new Mesh("../../DX11Starter/Assets/Models/sphere.obj", device);
	torus = new Mesh("../../DX11Starter/Assets/Models/torus.obj", device);

	for (int i = 0; i < 8; i++) {
		objArray[i] = new GameObject(torus, genericMat);
	}

}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	gameCamera.CalcProjection(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	gameCamera.Update(deltaTime);
	//objArray[2]->GetTransform()->SetPosition(XMFLOAT3(-2.0f, 0, 0));
	objArray[0]->Move(XMFLOAT3(0, -.1f*deltaTime, 0));
	objArray[1]->Move(XMFLOAT3(0, .1f*deltaTime, 0));
	objArray[2]->Rotate(XMFLOAT3(0, 0, .5f*deltaTime));
	objArray[3]->Move(XMFLOAT3(0, -0.1f*deltaTime, 0));
	objArray[4]->Move(XMFLOAT3(0, 0.1f*deltaTime, 0));
	objArray[5]->Rotate(XMFLOAT3(0, 0, -0.5f*deltaTime));
	objArray[7]->Scale(XMFLOAT3(.01f*deltaTime, 0.01f*deltaTime, 0.01f*deltaTime));
	objArray[6]->Rotate(XMFLOAT3(0.50f*deltaTime, .50f*deltaTime, 0.0f*deltaTime)); //rotates pentagon Hopefully
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	for (int i = 0; i < 8; i++) {
		
		
		objArray[i]->SetupMaterial(gameCamera.GetViewMatrix(), gameCamera.GetProjectionMatrix()); //sets up matrices in vshader and sets shaders to active
		objArray[i]->GetMaterial()->GetPShader()->SetData(
			"light",	//Name of variable in shader
			&directLight,
			sizeof(DirectionalLight));
		objArray[i]->Render(context); //renders object
	}

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	freeLookEnabled = true; //allows camera rotation with mouse

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	freeLookEnabled = false;

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	if (freeLookEnabled) //if free cam mode is turned on
	{
		float xDiff = (float)(x - prevMousePos.x);
		float yDiff = (float)(y - prevMousePos.y);
		gameCamera.RotateCamera(yDiff, xDiff); //camera rotates based on mouse movements
	}

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion