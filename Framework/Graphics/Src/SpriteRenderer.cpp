#include "Precompiled.h"
#include "SpriteRenderer.h"
#include "Texture.h"

#include "D3DUtil.h"
#include <DirectXTK/Inc/SpriteBatch.h>
#include <DirectXTK/Inc/CommonStates.h>

using namespace Omega::Graphics;

namespace
{
	std::unique_ptr<SpriteRenderer> sSpriteRenderer = nullptr;

	DirectX::XMFLOAT2 GetOrigin(uint32_t width, uint32_t height, Pivot pivot)
	{
		auto index = static_cast<std::underlying_type_t<Pivot>>(pivot);
		constexpr DirectX::XMFLOAT2 offsets[] =
		{
			{ 0.0f, 0.0f }, // TopLeft
			{ 0.5f, 0.0f }, // Top
			{ 1.0f, 0.0f }, // TopRight
			{ 0.0f, 0.5f }, // Left
			{ 0.5f, 0.5f }, // Center
			{ 1.0f, 0.5f }, // Right
			{ 0.0f, 1.0f }, // BottomLeft
			{ 0.5f, 1.0f }, // Bottom
			{ 1.0f, 1.0f }, // BottomRight
		};
		return { width * offsets[index].x, height * offsets[index].y };
	}

	DirectX::SpriteEffects GetSpriteEffects(Flip flip)
	{
		switch (flip)
		{
		case Flip::Horizontal:
			return DirectX::SpriteEffects_FlipHorizontally;
		case Flip::Vertical:
			return DirectX::SpriteEffects_FlipVertically;
		case Flip::Both:
			return DirectX::SpriteEffects_FlipBoth;
		default:
			break;
		}
		return DirectX::SpriteEffects_None;
	}

	DirectX::XMFLOAT2 ToXMFLOAT2(const Omega::Math::Vector2& v)
	{
		return { v.x, v.y };
	}
}

void SpriteRenderer::StaticInitialize()
{
	OMEGAASSERT(sSpriteRenderer == nullptr, "[SpriteRenderer] System already initialized!");
	sSpriteRenderer = std::make_unique<SpriteRenderer>();
	sSpriteRenderer->Initialize();
}

void Omega::Graphics::SpriteRenderer::StaticTerminate()
{
	if (sSpriteRenderer != nullptr)
	{
		sSpriteRenderer->Terminate();
		sSpriteRenderer.reset();
	}
}

SpriteRenderer* Omega::Graphics::SpriteRenderer::Get()
{
	OMEGAASSERT(sSpriteRenderer != nullptr, "[SpriteRenderer] No instance registered.");
	return sSpriteRenderer.get();
}

Omega::Graphics::SpriteRenderer::~SpriteRenderer()
{
	OMEGAASSERT(mSpriteBatch == nullptr, "[SpriteRenderer] Renderer not freed.");
}

void Omega::Graphics::SpriteRenderer::Initialize()
{
	OMEGAASSERT(mSpriteBatch == nullptr, "[SpriteRenderer] Already initialized.");
	mCommonStates = std::make_unique<DirectX::CommonStates>(GetDevice());
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(GetContext());
}

void Omega::Graphics::SpriteRenderer::Terminate()
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Already terminated!");
	mSpriteBatch.reset();
}

void SpriteRenderer::BeginRender()
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mSpriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		mCommonStates->NonPremultiplied(),
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		DirectX::XMMATRIX(
			mTransform._11, mTransform._12, mTransform._13, mTransform._14,
			mTransform._21, mTransform._22, mTransform._23, mTransform._24,
			mTransform._31, mTransform._32, mTransform._33, mTransform._34,
			mTransform._41, mTransform._42, mTransform._43, mTransform._44
		));
}

void SpriteRenderer::EndRender()
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mSpriteBatch->End();

	// Restore state objects
	auto blendState = mCommonStates->Opaque();
	auto depthStencilState = mCommonStates->DepthDefault();
	auto rasterizerState = mCommonStates->CullCounterClockwise();

	ID3D11DeviceContext* context = GetContext();
	context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(depthStencilState, 0);
	context->RSSetState(rasterizerState);
}

void SpriteRenderer::Draw(const Texture& texture, const Math::Vector2& pos, float rotation, Pivot pivot, Flip flip)
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	DirectX::XMFLOAT2 origin = GetOrigin(texture.GetWidth(), texture.GetHeight(), pivot);
	DirectX::SpriteEffects effects = GetSpriteEffects(flip);
	mSpriteBatch->Draw(texture.mShaderResourceView, ToXMFLOAT2(pos), nullptr, DirectX::Colors::White, rotation, origin, 1.0f, effects);
}

void SpriteRenderer::Draw(const Texture& texture, const Math::Rect& sourceRect, const Math::Vector2& pos, float rotation, Pivot pivot, Flip flip)
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	RECT rect{};
	rect.left = static_cast<LONG>(sourceRect.left);
	rect.top = static_cast<LONG>(sourceRect.top);
	rect.right = static_cast<LONG>(sourceRect.right);
	rect.bottom = static_cast<LONG>(sourceRect.bottom);
	DirectX::XMFLOAT2 origin = GetOrigin(rect.right - rect.left, rect.bottom - rect.top, pivot);
	DirectX::SpriteEffects effects = GetSpriteEffects(flip);
	mSpriteBatch->Draw(texture.mShaderResourceView, ToXMFLOAT2(pos), &rect, DirectX::Colors::White, rotation, origin, 1.0f, effects);
}
