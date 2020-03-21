// Description: Standard shader for Ocean.

cbuffer TransformBuffer : register(b0)
{
    matrix World;
    matrix WVP;
    float3 ViewPosition;
    float3 LightDirection;
    float4 LightAmbient;
    float4 LightDiffuse;
    float4 LightSpecular;
}

cbuffer SettingsBuffer : register(b1)
{
    
    float DeltaTime : packoffset(c0.x);
}

SamplerState textureSampler : register(s0);
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
//Texture2D bumpMap : register(t2);

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float3 worldNormal : NORMAL;
    float3 worldTangent : TEXCOORD0;
    float3 dirToView : TEXCOORD1;
    float2 texCoord : TEXCOORD2;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    input.position.z += sin((DeltaTime * 16.0f) + (input.position.y / 1.0f)) / 16.0f;
	
    output.position = mul(float4(input.position, 1.0f), WVP);
    output.worldNormal = mul(input.normal, (float3x3) World);
    output.worldTangent = mul(input.tangent, (float3x3) World);;
    output.dirToView = normalize(ViewPosition - mul(input.position.xyz, (float3x3) World));
	
    output.texCoord = input.texCoord;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    input.texCoord.x *= 20.0f + sin(DeltaTime * 3.0f + 10.0f) / 256.0f;
    input.texCoord.y *= 20.0f;
	
    float4 colorMap = diffuseMap.Sample(textureSampler, input.texCoord);
	
    input.texCoord.y += (sin(DeltaTime * 3.0f + 10.0f) / 256.0f) + (DeltaTime / 16.0f);
    float3 normalColor = (2.0f * normalMap.Sample(textureSampler, input.texCoord)) - 1.0f;
	
    input.texCoord.y -= ((sin(DeltaTime * 3.0f + 10.0f) / 256.0f) + (DeltaTime / 16.0f)) * 2.0f;
    float3 normalColor2 = (2.0f * normalMap.Sample(textureSampler, input.texCoord)) - 1.0f;
	
    normalColor = (normalColor + normalColor2) * 0.5f;
	
    normalColor = normalize(mul(normalColor, input.worldTangent));
    float4 normal = float4(normalColor, 1.0f);
	
    float4 diffuse = saturate(dot(-LightDirection, (float3) normal));
    float4 reflect = normalize(2.0f * diffuse * normal - float4(LightDirection, 1.0f));
    float4 specular = pow(saturate(dot(reflect, LightSpecular)), 28.0f);
	
    float4 finalColor = colorMap * LightAmbient +
			colorMap * LightDiffuse * diffuse +
			specular * 256.0f;
	
    finalColor.a = 0.3f;
	return finalColor;
   // return (float4) (input.texCoord.xy, 0.0f, 0.0f);
}