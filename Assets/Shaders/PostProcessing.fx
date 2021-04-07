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

float4 PSNoProcessing(VSOutput input) : SV_Target
{
    return textureMap.Sample(textureSampler, input.texCoord);;
}


float4 PSSepiaTone(VSOutput input) : SV_Target
{
	// TODO : Need more work in this part here
//	float2 offSet = {
//
//}
    float4 colorTexture = textureMap.Sample(textureSampler, input.texCoord);
    float4 outputColor = colorTexture;
	//sepia tone
    outputColor.r = (colorTexture.r * 0.393) + (colorTexture.g * 0.769) + (colorTexture.b * 0.189);
    outputColor.g = (colorTexture.r * 0.349) + (colorTexture.g * 0.686) + (colorTexture.b * 0.168);
    outputColor.b = (colorTexture.r * 0.272) + (colorTexture.g * 0.534) + (colorTexture.b * 0.131);
    return outputColor;
}

float4 PSGreyScale(VSOutput input) : SV_Target
{
    float4 colorTexture = textureMap.Sample(textureSampler, input.texCoord);
    float greyColor = (colorTexture.r + colorTexture.g + colorTexture.b) * 0.5f;
    float4 outputColor = float4(greyColor, greyColor, greyColor, colorTexture.a);
	
    return outputColor;
}


float4 PSInverseColor(VSOutput input) : SV_Target
{
    float4 colorTexture = textureMap.Sample(textureSampler, input.texCoord);
    return float4(1 - colorTexture.rgb, colorTexture.a);
}


float4 PSRadialBlur(VSOutput input) : SV_Target
{
    float2 Center = float2(0.5f, 0.5f);
    float BlurStart = 1.0f;
    float BlurWidth = -0.14f;
    float samples = 16;
    float4 color = 0.0f;
    for (int i = 0; i < samples; ++i)
    {
        float scale = BlurStart + BlurWidth * (i / (samples - 1.0f));
        color += textureMap.Sample(textureSampler, (input.texCoord - 0.5f) * scale + Center);
    }

    color /= samples;

    return color;
}

//float4 PSDistortionColor(VSOutput input) : SV_Target
//{
//    float4 colorTexture = textureMap.Sample(textureSampler, input.texCoord);
//    colorTexture.x += sin(colorTexture.y * 2 * 4 * 3.14);
    
//   // float4 outputColor = textureMap.Sample(textureSampler, displacement * displacement);
    
//    return colorTexture;
//}

