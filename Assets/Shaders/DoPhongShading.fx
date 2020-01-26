// Description: Simple shader that applies transform and lighting.

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

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 worldNormal : NORMAL;
	float3 dirToLight : TEXCOORD0;
	float3 dirToView : TEXCOORD1;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	float3 worldPosition = mul(float4(input.position, 1.0f), World).xyz;
	float3 worldNormal = mul(input.normal, (float3x3)World);

	output.position = mul(float4(input.position, 1.0f), WVP);
	output.worldNormal = worldNormal;
	output.dirToLight = -LightDirection;
	output.dirToView = ViewPosition - worldPosition;

	return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

float4 PS(VS_OUTPUT input) : SV_Target
{
	// Renormalize normals from vertex shader
	float3 worldNormal = normalize(input.worldNormal);
	float3 dirToLight = normalize(input.dirToLight);
	float3 dirToView = normalize(input.dirToView);

	float4 ambient = LightAmbient * MaterialAmbient;
	
	float diffuseIntensity = saturate(dot(dirToLight, worldNormal));
	float4 diffuse = diffuseIntensity * LightDiffuse * MaterialDiffuse;
	
	float3 halfAngle = normalize(dirToLight + dirToView);
	float specularBase = saturate(dot(halfAngle, worldNormal));
	float specularIntensity = pow(specularBase, MaterialPower);
	float4 specular = specularIntensity * LightSpecular * MaterialSpecular;

	float4 color = ambient + diffuse + specular;
	return color;
}