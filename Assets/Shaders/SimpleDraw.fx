//====================================================================================================
// SIEGE - Super Innovative Exciting Game Engine
// Copyright (c) 2019 Peter Chan. All rights reserved.
//
// Description: Shader for simple geometry.
//====================================================================================================

cbuffer ConstantBuffer : register(b0)
{
	matrix wvp;
}

struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = mul(float4(input.position, 1.0f), wvp);
	output.color = input.color;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color;
}
