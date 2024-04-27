#include "Precompiled.h"

#include "RendererManager.h"

#include "SpriteRenderer.h"
#include "TextureManager.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Math;

namespace
{
	static std::unique_ptr<RendererManager> sRendererManager;
}

void RendererManager::StaticInitialize()
{
	OMEGAASSERT(sRendererManager == nullptr, "[SpriteRendererManager] Sprite Renderer Manager is already initialized.");
	sRendererManager = std::make_unique<RendererManager>();
	sRendererManager->Initialize();
}

void RendererManager::StaticTerminate()
{
	if (sRendererManager != nullptr)
	{
		sRendererManager.reset();
	}
}

std::optional<std::reference_wrapper<RendererManager>> RendererManager::Get()
{
	OMEGAASSERT(sRendererManager != nullptr, "[SpriteRendererManager] Sprite Renderer Manager is not initialized.");
	if (sRendererManager)
	{
		return std::reference_wrapper<RendererManager>(*sRendererManager).get();
	}
	return std::nullopt;
}

void RendererManager::Initialize()
{
	mSpriteRenderer = std::make_unique<SpriteRenderer>();
	mFontRenderer = std::make_unique<FontRenderer>();
}

void RendererManager::Render()
{
	mSpriteRenderer->Render();
	mFontRenderer->Render();
}

#pragma region Draw text

void RendererManager::DrawScreenText(std::wstring_view str, const Math::Vector2& position, float fontSize, const Color& color)
{
	DrawScreenText({ str, fontSize, position, color });
}

void RendererManager::DrawScreenText(FontRenderer::TextCommand&& textCommandsArgs)
{
	mFontRenderer->DrawScreenText(std::forward<FontRenderer::TextCommand>(textCommandsArgs));
}

#pragma endregion

#pragma region Draw sprite

void RendererManager::DrawSprite(TextureId textureId, const Math::Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	DrawSprite({ textureId, position, rotation, pivot, flip });
}

void RendererManager::DrawSprite(SpriteRenderer::SpriteCommand&& spriteCommandsArgs)
{
	mSpriteRenderer->DrawSprite(std::forward<SpriteRenderer::SpriteCommand>(spriteCommandsArgs));
}

#pragma endregion

TextureId RendererManager::LoadTexture(const std::filesystem::path& fileName)
{
	return mSpriteRenderer->LoadTexture(fileName);
}

void RendererManager::ClearAllTextures() noexcept
{
	mSpriteRenderer->ClearAllTextures();
}
