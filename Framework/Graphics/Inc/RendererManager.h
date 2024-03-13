#pragma once
#include "Colors.h"
#include "TextureTypes.h"
#include "FontRenderer.h"
#include "SpriteRenderer.h"

namespace Omega::Graphics
{
	class RendererManager
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static std::optional<std::reference_wrapper<RendererManager>> Get();
	public:
		void Initialize();

		void Render();

		void DrawScreenText(std::wstring_view str, const Math::Vector2& position, float fontSize, const Color& color);
		void DrawScreenText(FontRenderer::TextCommand&& textCommandsArgs);

		void DrawSprite(TextureId textureId, const Math::Vector2& position, float rotation = 0.0f, Pivot pivot = Pivot::Center, Flip flip = Flip::None);
		void DrawSprite(SpriteRenderer::SpriteCommand&& spriteCommandsArgs);

		TextureId LoadTexture(const std::filesystem::path& fileName);

		void ClearAllTextures() noexcept;
	private:
		std::unique_ptr<SpriteRenderer> mSpriteRenderer;
		std::unique_ptr<FontRenderer> mFontRenderer;
	};

}