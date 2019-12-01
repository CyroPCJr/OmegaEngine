// Description: Simple Shader applies transformation.

cbuffer TransformBuffer : register(b0)
{
	matrix WVP;
}

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

// Vertex shaders
VS_OUTPUT VS(float3 position : POSITION, float4 color : COLOR)
{
	VS_OUTPUT output;
	output.position = mul(float4(position, 1.0f), WVP);
	output.color = color;
	return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

// Pixels shaders
float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color; // Yellow
}