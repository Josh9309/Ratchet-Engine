
// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
};

/*This struct represents the data epected in a directional light
*/
struct DirectionalLight
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 direction;
};

cbuffer lightData : register(b0)
{
	DirectionalLight light;
};


// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	//Calculate the normalized direction to light by normalizing the opposite of the light direction
	float3 dirToLight = normalize(-light.direction); //Normalized direction to the light

	//Calculate the light amount using N dot L
	float lightAmount = saturate(dot(input.normal, dirToLight));
	input.normal = normalize(input.normal);

	//Return final surface color based on light amount, diffuse color and ambient color
	float4 surfaceColor = (light.diffuseColor * lightAmount) + light.ambientColor;
	return surfaceColor;
}