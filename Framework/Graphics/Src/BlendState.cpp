#include "Precompiled.h"
#include "BlendState.h"

#include "D3DUtil.h"

using namespace Omega::Graphics;

namespace
{
	std::pair<D3D11_BLEND, D3D11_BLEND> GetBlendParam(BlendState::Mode mode)
	{
		switch (mode)
		{
		case BlendState::Mode::Opaque:
			return { D3D11_BLEND_ONE, D3D11_BLEND_ZERO };
		case BlendState::Mode::AlphaBlending:
			return { D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA };
		case BlendState::Mode::AlphaPremultipled:
			return { D3D11_BLEND_ONE, D3D11_BLEND_INV_SRC_ALPHA };
		case BlendState::Mode::Additive:
			return {D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE};
		default:
			return {D3D11_BLEND_ONE, D3D11_BLEND_ZERO};
		}
	}
}

void BlendState::ClearState()
{
	GetContext()->OMSetBlendState(nullptr, nullptr, UINT_MAX);
}

BlendState::~BlendState()
{
	OMEGAASSERT(mBlendState == nullptr, "[BlendState] Blend state not released!");
}

void BlendState::Initialize(Mode mode)
{
	auto[srcBlend, destBlend] = GetBlendParam(mode);
	
	D3D11_BLEND_DESC desc{};
	desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE)  || (destBlend != D3D11_BLEND_ZERO);
	desc.RenderTarget[0].SrcBlend = desc.RenderTarget[0].SrcBlendAlpha = srcBlend;
	desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
	desc.RenderTarget[0].BlendOp = desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	const HRESULT hr = GetDevice()->CreateBlendState(&desc, &mBlendState);
	OMEGAASSERT(SUCCEEDED(hr), "[BlendState] Failed to createa blend state.");
}

void BlendState::Terminate()
{
	SafeRelease(mBlendState);
}

void BlendState::Bind() const
{
	GetContext()->OMSetBlendState(mBlendState, nullptr, UINT_MAX);
}
