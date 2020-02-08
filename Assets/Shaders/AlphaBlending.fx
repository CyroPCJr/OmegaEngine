cbuffer AlphaBlendingBuffer : register(b0)
{
	matrix WVP;
}

cbuffer TransparentBuffer
{
	float blendAmount;
}

Texture2D shaderTexture;
SamplerState SampleType;

//////////////
// TYPEDEFS //
//////////////
struct VS_INPUT
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD0;
};


VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = mul(float4(input.position, 1.0f), WVP);
	output.texCoord = input.texCoord;
	return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 color;
	// Sample the texture pixel at this location.
	color = shaderTexture.Sample(SampleType, input.texCoord);
	//Here we use the blendAmount variable to set the transparency of the texture.
	//We set the alpha value of the pixel to the blend amount and when rendered it 
	//will use the alpha value with the blend state we setup to create the transparency effect.
	// Set the alpha value of this pixel to the blending amount to create the alpha blending effect.
	color.a = blendAmount;

	return color;
}