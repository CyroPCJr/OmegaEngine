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
	float4 color : COLOR;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	float3 worldPosition = mul(float4(input.position, 1.0f), World).xyz;
	float3 worldNormal = mul(input.normal, (float3x3)World);

	float4 ambient = LightAmbient * MaterialAmbient;

	float3 dirToLight = -LightDirection;
	float diffuseIntensity = saturate(dot(dirToLight, worldNormal));
	float4 diffuse = diffuseIntensity * LightDiffuse * MaterialDiffuse;

	float3 dirToView = normalize(ViewPosition - worldPosition);
	float3 halfAngle = normalize(dirToLight + dirToView);
	float specularBase = saturate(dot(halfAngle, worldNormal));
	float specularIntensity = pow(specularBase, MaterialPower);
	float4 specular = specularIntensity * LightSpecular * MaterialSpecular;

	float4 color = ambient + diffuse + specular;

	output.position = mul(float4(input.position, 1.0f), WVP);
	output.color = color;

	return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color;
}