#pragma once
#include "Colors.h"
#include "TextureTypes.h"

namespace Omega::Graphics
{
	class SpriteRendererManager
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static SpriteRendererManager* Get();
	public:
		void Initialize();
		void Terminate();

		void Render();

		void DrawScreenText(const char* str, float x, float y, float size, const Color& color);
		void DrawSprite(TextureId textureId, const Math::Vector2& position, Pivot pivot = Pivot::Center, Flip flip = Flip::None);
		void DrawSprite(TextureId textureId, const Math::Vector2& position, float rotation, Pivot pivot = Pivot::Center, Flip flip = Flip::None);
		void DrawSprite(TextureId textureId, const Math::Rect& sourceRect, const Math::Vector2& position);
	};

}