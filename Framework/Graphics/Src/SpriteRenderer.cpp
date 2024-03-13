#include "Precompiled.h"
#include "SpriteRenderer.h"
#include "D3DUtil.h"
#include "Texture.h"

using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace std::literals;

namespace
{
	constexpr std::string_view PATH_ROOT = "../../Assets/Images"sv;
}

SpriteRenderer::SpriteRenderer() noexcept(false)
{
	//OMEGAASSERT(mSpriteBatch == nullptr, "[SpriteRenderer] Already initialized.");
	mTextureManager = std::make_unique<TextureManager>(PATH_ROOT);
	mCommonStates = std::make_unique<DirectX::CommonStates>(GetDevice());
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(GetContext());
}

SpriteRenderer::~SpriteRenderer() noexcept
{
	mSpriteBatch.reset();
	mCommonStates.reset();
	mTextureManager.reset();
	//OMEGAASSERT(mSpriteBatch == nullptr, "[SpriteRenderer] Renderer not freed.");
}

void SpriteRenderer::BeginRender()
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	const Matrix4 matrixIdentity = Matrix4::Identity;
	mSpriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		mCommonStates->NonPremultiplied(),
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		DirectX::XMMATRIX(
			matrixIdentity._11, matrixIdentity._12, matrixIdentity._13, matrixIdentity._14,
			matrixIdentity._21, matrixIdentity._22, matrixIdentity._23, matrixIdentity._24,
			matrixIdentity._31, matrixIdentity._32, matrixIdentity._33, matrixIdentity._34,
			matrixIdentity._41, matrixIdentity._42, matrixIdentity._43, matrixIdentity._44
		));
}

void SpriteRenderer::Render()
{
	TextureId id{ 0u };
	BeginRender();
	for (const auto& command : mSpriteCommands)
	{
		Texture* texture = nullptr;
		if (!texture || id != command.textureId)
		{
			texture = mTextureManager->GetTexture(command.textureId);
			id = command.textureId;
		}

		if (texture)
		{
			Draw(*texture, { command.textureId , command.position, command.rotation, command.sourceRect });
		}
	}
	mSpriteCommands.clear();
	EndRender();
}

void SpriteRenderer::EndRender()
{
	OMEGAASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mSpriteBatch->End();

	// Restore state objects
	const auto blendState = mCommonStates->Opaque();
	const auto depthStencilState = mCommonStates->DepthDefault();
	const auto rasterizerState = mCommonStates->CullCounterClockwise();

	if (ID3D11DeviceContext* context = GetContext())
	{
		context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
		context->OMSetDepthStencilState(depthStencilState, 0u);
		context->RSSetState(rasterizerState);
	}
}

void SpriteRenderer::DrawSprite(SpriteCommand&& spriteCommandsArgs)
{
	mSpriteCommands.emplace_back(std::forward<SpriteCommand>(spriteCommandsArgs));
}

TextureId SpriteRenderer::LoadTexture(const std::filesystem::path& fileName)
{
	return mTextureManager->Load(fileName);
}

void SpriteRenderer::ClearAllTextures() noexcept
{
	mTextureManager->Clear();
}

void SpriteRenderer::Draw(const Texture& texture, SpriteCommand&& spriteCommandsArgs)
{
	auto& [rectangle, position, textureId, pivot, flip, rotation] = spriteCommandsArgs;
	const bool emptyRect = IsEmpty(rectangle);
	RECT rect{};
	DirectX::XMFLOAT2 origin;
	if (!emptyRect) {
		rect.left = static_cast<LONG>(rectangle.left);
		rect.top = static_cast<LONG>(rectangle.top);
		rect.right = static_cast<LONG>(rectangle.right);
		rect.bottom = static_cast<LONG>(rectangle.bottom);
		origin = GetOrigin((rect.right - rect.left), (rect.bottom - rect.top), pivot);
	}
	else
	{
		origin = GetOrigin(texture.GetWidth(), texture.GetHeight(), pivot);
	}
	const DirectX::SpriteEffects effects = GetSpriteEffects(flip);
	mSpriteBatch->Draw(texture.GetShaderResourceView(), ToXMFLOAT2(position), !emptyRect ? &rect : nullptr, DirectX::Colors::White, rotation, origin, 1.0f, effects);
}


DirectX::XMFLOAT2 SpriteRenderer::GetOrigin(uint32_t width, uint32_t height, Pivot pivot)
{
	static constexpr std::array<DirectX::XMFLOAT2, 9> offsets =
	{
		{ { 0.0f, 0.0f },    // TopLeft
		  { 0.5f, 0.0f },    // Top
		  { 1.0f, 0.0f },    // TopRight
		  { 0.0f, 0.5f },    // Left
		  { 0.5f, 0.5f },    // Center
		  { 1.0f, 0.5f },    // Right
		  { 0.0f, 1.0f },    // BottomLeft
		  { 0.5f, 1.0f },    // Bottom
		  { 1.0f, 1.0f } }   // BottomRight
	};
	const DirectX::XMFLOAT2 offsetPos = offsets.at(static_cast<std::underlying_type_t<Pivot>>(pivot));
	return { static_cast<float>(width) * offsetPos.x, static_cast<float>(height) * offsetPos.y };
}

constexpr DirectX::SpriteEffects SpriteRenderer::GetSpriteEffects(Flip flip) noexcept
{
	// Convert Flip enum to integer values
	const size_t horizontal = (flip == Flip::Horizontal);
	const size_t vertical = (flip == Flip::Vertical);
	const size_t both = (flip == Flip::Both);

	// Calculate the combined value using bitwise OR operations
	const size_t combined = (horizontal * DirectX::SpriteEffects_FlipHorizontally) |
		(vertical * DirectX::SpriteEffects_FlipVertically) |
		(both * DirectX::SpriteEffects_FlipBoth);

	// Return the final result
	return static_cast<DirectX::SpriteEffects>(combined);
}

constexpr DirectX::XMFLOAT2 SpriteRenderer::ToXMFLOAT2(const Vector2& v)
{
	return { v.x, v.y };
}
