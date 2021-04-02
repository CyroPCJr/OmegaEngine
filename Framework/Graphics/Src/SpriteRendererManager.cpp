#include "Precompiled.h"
#include "SpriteRendererManager.h"
#include "SpriteRenderer.h"
#include "Font.h"
#include "TextureManager.h"

using namespace Omega;
using namespace Omega::Graphics;

namespace
{

	struct SpriteCommand
	{
		SpriteCommand(TextureId inTextureId, const Math::Vector2& inPosiiton, float inRotation)
			: textureId(inTextureId)
			, sourceRect({ 0.0f, 0.0f, 0.0f, 0.0f })
			, position(inPosiiton)
			, rotation(inRotation)
		{}

		SpriteCommand(TextureId inTextureId, const Math::Vector2& inPosiiton, float inRotation, Pivot pivot, Flip flip)
			: textureId(inTextureId)
			, sourceRect({ 0.0f, 0.0f, 0.0f, 0.0f })
			, position(inPosiiton)
			, rotation(inRotation)
			, pivot(pivot)
			, flip(flip)
		{}

		SpriteCommand(TextureId inTextureId, const Math::Rect& inSourceRect, const Math::Vector2& inPosiiton, float inRotation)
			: textureId(inTextureId)
			, sourceRect(inSourceRect)
			, position(inPosiiton)
			, rotation(inRotation)
		{}

		TextureId textureId = 0;
		Math::Rect sourceRect{};
		Math::Vector2 position = Math::Vector2::Zero;
		Pivot pivot = Pivot::Center;
		Flip flip = Flip::None;
		float rotation = 0.0f;
	};

	struct TextCommand
	{
		TextCommand(std::wstring inStr, float inSize, float inX, float inY, const Color& inColor)
			: str(std::move(inStr))
			, size(inSize)
			, x(inX)
			, y(inY)
			, color(inColor)
		{}

		std::wstring str;
		Color color;
		float size = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
	};

	static std::unique_ptr<SpriteRendererManager> sSpriteRendererManager;

	Font mFont;

	std::vector<SpriteCommand> SpriteCommands;
	std::vector<TextCommand> TextCommands;
}

void SpriteRendererManager::StaticInitialize()
{
	OMEGAASSERT(sSpriteRendererManager == nullptr, "[SpriteRendererManager] Sprite Renderer Manager is already initialized.");
	sSpriteRendererManager = std::make_unique<SpriteRendererManager>();
	sSpriteRendererManager->Initialize();
}

void SpriteRendererManager::StaticTerminate()
{
	if (sSpriteRendererManager != nullptr)
	{
		sSpriteRendererManager->Terminate();
		sSpriteRendererManager.reset();
	}
}

SpriteRendererManager* SpriteRendererManager::Get()
{
	OMEGAASSERT(sSpriteRendererManager != nullptr, "[SpriteRendererManager] Sprite Renderer Manager is not initialized.");
	return sSpriteRendererManager.get();
}

void SpriteRendererManager::Initialize()
{
	mFont.Initialize();
}

void SpriteRendererManager::Terminate()
{
	mFont.Terminate();
}

void SpriteRendererManager::Render()
{
	TextureId id = 0;
	Texture* texture = nullptr;

	SpriteRenderer::Get()->BeginRender();
	for (const auto& command : SpriteCommands)
	{
		if (id != command.textureId)
		{
			texture = TextureManager::Get()->GetTexture(command.textureId);
			id = command.textureId;
		}

		if (texture)
		{
			if (IsEmpty(command.sourceRect))
			{
				SpriteRenderer::Get()->Draw(*texture, command.position, command.rotation, command.pivot, command.flip);
			}
			else
			{
				SpriteRenderer::Get()->Draw(*texture, command.sourceRect, command.position, command.rotation, command.pivot, command.flip);
			}
		}
	}
	SpriteCommands.clear();
	SpriteRenderer::Get()->EndRender();

	// Text
	for (const auto& command : TextCommands)
	{
		mFont.Draw(command.str.c_str(), command.x, command.y, command.size, command.color);
	}
	TextCommands.clear();
}

void SpriteRendererManager::DrawScreenText(const char* str, float x, float y, float size, const Color& color)
{
	int strLenght = static_cast<int>(strlen(str));
	int convertResult = MultiByteToWideChar(CP_UTF8, 0, str, strLenght, NULL, 0);
	std::wstring wideString(convertResult, 0);
	MultiByteToWideChar(CP_UTF8, 0, str, strLenght, &wideString[0], convertResult);
	TextCommands.emplace_back(std::move(wideString), size, x, y, color);
}

void SpriteRendererManager::DrawSprite(TextureId textureId, const Math::Vector2& position, Pivot pivot, Flip flip)
{
	SpriteCommands.emplace_back(textureId, position, 0.0f, pivot, flip);
}

void SpriteRendererManager::DrawSprite(TextureId textureId, const Math::Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteCommands.emplace_back(textureId, position, rotation, pivot, flip);
}

void SpriteRendererManager::DrawSprite(TextureId textureId, const Math::Rect& sourceRect, const Math::Vector2& position)
{
	SpriteCommands.emplace_back(textureId, sourceRect, position, 0.0f);
}
