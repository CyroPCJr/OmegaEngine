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

cbuffer SettingsBuffer: register(b3)
{
	float specularMapWeight : packoffset(c0.x);
	float bumpMapWeight : packoffset(c0.y);
	float normalMapWeight : packoffset(c0.z);
}

Texture2D textureMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D displacementMap : register(t2);
Texture2D normalMap : register(t3);
Texture2D cloudMap : register(t4);
Texture2D nightLightMap : register(t5);

SamplerState textureSampler : register(s0);

struct VSInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD0;
};

struct VSOutput
{
	float4 position : SV_Position;
	float3 worldNormal : NORMAL;
	float3 worldTangent : TEXCOORD0;
	float3 dirToLight : TEXCOORD1;
	float3 dirToView : TEXCOORD2;
	float2 texCoord : TEXCOORD3;
};


struct VSCloudOutPut
{
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD;
};


VSOutput VSEarth(VSInput input)
{
	VSOutput output;

	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
	float3 localPosition = input.position + (input.normal * displacement * bumpMapWeight);

	float3 worldPosition = mul(float4(localPosition, 1.0f), World).xyz;
	float3 worldNormal = mul(input.normal, (float3x3)World);
	float3 worldTangent = mul(input.tangent, (float3x3)World);

	output.position = mul(float4(localPosition, 1.0f), WVP);
	output.worldNormal = worldNormal;
	output.worldTangent = worldTangent;
	output.dirToLight = -LightDirection;
	output.dirToView = normalize(ViewPosition - worldPosition);
	output.texCoord = input.texCoord;

	return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

float4 PSEarth(VSOutput input) : SV_Target
{
	// Renormalize normals from vertex shader
	float3 worldNormal = normalize(input.worldNormal);
	float3 worldTangent = normalize(input.worldTangent);

	float3 worldBinormal = normalize(cross(worldNormal, worldTangent));

	float3 dirToLight = normalize(input.dirToLight);
	float3 dirToView = normalize(input.dirToView);

	float3 normal = worldNormal;
	if (normalMapWeight != 0.0f)
	{
		float3x3 TBNW = { worldTangent, worldBinormal, worldNormal };
		float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
		float3 normalSampled = (normalColor.xyz * 2.0f) - 1.0f;
		normal = mul(normalSampled, TBNW);
	}

	float4 ambient = LightAmbient * MaterialAmbient;

	float diffuseIntensity = saturate(dot(dirToLight, normal));
	float4 diffuse = diffuseIntensity * LightDiffuse * MaterialDiffuse;

	float3 halfAngle = normalize(dirToLight + dirToView);
	float specularBase = saturate(dot(halfAngle, normal));
	float specularIntensity = pow(specularBase, MaterialPower);
	float4 specular = specularIntensity * LightSpecular * MaterialSpecular;

	float4 textureColor = textureMap.Sample(textureSampler, input.texCoord);
	float specularFactor = specularMap.Sample(textureSampler, input.texCoord).r;

	float4 nightLight = nightLightMap.Sample(textureSampler, input.texCoord);
	float diffuseRaw = dot(dirToLight,normal);
	float nightInsensity = saturate(-diffuseRaw);
	float nightBlend = (diffuseRaw + 1.0f) * 0.5f;

	float4 color = nightBlend * (ambient + diffuse) * textureColor + (nightInsensity * nightLight) + specular * (specularMapWeight != 0.0f ? specularFactor : 1.0f);
	return color;
}


//--------------- Clouds ----------------------------------------------//
VSCloudOutPut VSCloud(VSInput input)
{
	VSCloudOutPut output;
	float3 localPosition = input.position + (input.normal * (0.05f + bumpMapWeight));

	output.position = mul(float4(localPosition, 1.0f), WVP);
	output.texCoord = input.texCoord;

	return output;
}

//	|
//	V
// Rasterizer
//	|
//	V

float4 PSCloud(VSCloudOutPut input) : SV_Target
{
	float4 color = cloudMap.Sample(textureSampler, input.texCoord);
	color.a = 0.2;
	return color;
}
