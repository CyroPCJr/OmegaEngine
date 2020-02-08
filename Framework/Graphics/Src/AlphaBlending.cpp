#include "Precompiled.h"
#include "AlphaBlending.h"

#include "D3DUtil.h"

using namespace Omega::Graphics;

void AlphaBlending::Initialize()
{
	D3D11_BLEND_DESC blendState;
	
	ZeroMemory(&blendState, sizeof(D3D11_BLEND_DESC));
	blendState.RenderTarget[0].BlendEnable = true;
	blendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	auto device = GetDevice();
	HRESULT hr = device->CreateBlendState(&blendState, &mAlphaBlending);
	
	OMEGAASSERT(SUCCEEDED(hr), "Failed to blend texture.");
}

void AlphaBlending::Terminate()
{
	SafeRelease(mAlphaBlending);
}

void AlphaBlending::Bind() const
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT sampleMask = 0xffffffff;
	GetContext()->OMSetBlendState(mAlphaBlending, blendFactor, sampleMask);
}