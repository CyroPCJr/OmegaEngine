// Description: Post processing shader

Texture2D textureMap : register(t0);
SamplerState textureSampler : register(s0);

struct VSInput
{
	float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};


struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};


VSOutput VS(VSInput input)
{
	VSOutput output;
    output.position = float4(input.position, 1.0f);
	output.texCoord = input.texCoord;
    return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

float4 PS(VSOutput input) : SV_Target
{
	return textureMap.Sample(textureSampler, input.texCoord);
}