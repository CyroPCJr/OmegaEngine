// Description: Standard shader for Ocean.

cbuffer TransformBuffer : register(b0)
{
	matrix World;
	matrix WVP;
	float3 ViewPosition;
}

cbuffer LightBuffer : register(b1)
{
	float3 LightDirection;
	float4 LightAmbient;
	float4 LightDiffuse;
	float4 LightSpecular;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 MaterialAmbient;
	float4 MaterialDiffuse;
	float4 MaterialSpecular;
	float MaterialPower;
}


struct VertexShaderInput
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 Normal : NORMAL0;
	float3 Binormal : BINORMAL0;
	float3 Tangent : TANGENT0;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord	: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 worldNormal : NORMAL;
	float3 worldTangent : TEXCOORD0;
	float3 dirToLight : TEXCOORD1;
	float3 dirToView : TEXCOORD2;
	float2 texCoord	: TEXCOORD3;
	float4 positionNDC : TEXCOORD4;


	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 View : TEXCOORD1;
	float3x3 WorldToTangentSpace : TEXCOORD2;
};

// Matrix
//float4x4 World;
//float4x4 View;
//float4x4 Projection;

// Light related
float4 AmbientColor;
float AmbientIntensity;

float3 LightDirection;
float4 DiffuseColor;
float DiffuseIntensity;

float4 SpecularColor;
float3 EyePosition;

float TotalTime;

texture2D ColorMap;
sampler2D ColorMapSampler = sampler_state
{
	Texture = <ColorMap>;
	MinFilter = linear;
	MagFilter = linear;
	MipFilter = linear;
};

texture2D NormalMap;
sampler2D NormalMapSampler = sampler_state
{
	Texture = <NormalMap>;
	MinFilter = linear;
	MagFilter = linear;
	MipFilter = linear;
};

// The input for the VertexShader




// The VertexShader.
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	input.Position.z += sin((TotalTime * 16) + (input.Position.y / 1)) / 16;

	float4 worldPosition = mul(input.Position, World);
	float4 viewPosition = mul(worldPosition, View);
	output.Position = mul(viewPosition, Projection);
	output.TexCoord = input.TexCoord;

	output.WorldToTangentSpace[0] = mul(normalize(input.Tangent), World);
	output.WorldToTangentSpace[1] = mul(normalize(input.Binormal), World);
	output.WorldToTangentSpace[2] = mul(normalize(input.Normal), World);

	output.View = normalize(float4(EyePosition, 1.0) - worldPosition);

	return output;
}

// The Pixel Shader
float4 PS(VS_OUTPUT input) : SV_Target
{
	input.TexCoord.x = input.TexCoord.x*20.0f + sin(TotalTime * 3 + 10) / 256;
	input.TexCoord.y = input.TexCoord.y*20.0f;

	float4 color = tex2D(ColorMapSampler, input.TexCoord);

	input.TexCoord.y += (sin(TotalTime * 3 + 10) / 256) + (TotalTime / 16);
	float3 normalMap = 2.0 *(tex2D(NormalMapSampler, input.TexCoord)) - 1.0;

	input.TexCoord.y -= ((sin(TotalTime * 3 + 10) / 256) + (TotalTime / 16)) * 2;
	float3 normalMap2 = (2 * (tex2D(NormalMapSampler, input.TexCoord))) - 1.0;

	normalMap = (normalMap + normalMap2) / 2;

	normalMap = normalize(mul(normalMap, input.WorldToTangentSpace));
	float4 normal = float4(normalMap,1.0);

	float4 diffuse = saturate(dot(-LightDirection,normal));
	float4 reflect = normalize(2.0f * diffuse*normal - float4(LightDirection,1.0));
	float4 specular = pow(saturate(dot(reflect,input.View)),28.0f);

	float4 finalColor = color * AmbientIntensity +
			color * DiffuseIntensity * diffuse +
			specular * 250.0f;

	finalColor.a = 0.3f;
	return finalColor;
}