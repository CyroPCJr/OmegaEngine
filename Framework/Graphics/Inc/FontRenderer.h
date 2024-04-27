#pragma once

#include "Colors.h"
#include "Font.h"

namespace Omega::Graphics
{
	class FontRenderer final
	{
	public:

		struct TextCommand
		{
			TextCommand(std::wstring inStr, float inSize, float inX, float inY, const Color& inColor) noexcept
				: str(std::move(inStr)), color(inColor), size(inSize), x(inX), y(inY)
			{}

			TextCommand(std::wstring_view inStr, float inSize, const Math::Vector2& inPosition, const Color& inColor)
				: TextCommand(std::wstring(inStr).c_str(), inSize, inPosition.x, inPosition.y, inColor) {}

			std::wstring str;
			Color color;
			float size{ 0.0f };
			float x{ 0.0f };
			float y{ 0.0f };
		};

		explicit FontRenderer() noexcept(false);
		~FontRenderer() noexcept = default;

		FontRenderer(const FontRenderer&) = delete;
		FontRenderer& operator=(const FontRenderer&) = delete;

		FontRenderer(FontRenderer&&) = delete;
		FontRenderer& operator=(FontRenderer&&) = delete;

		void Render();

		void DrawScreenText(std::wstring_view str, const Math::Vector2& position, float fontSize, const Color& color);
		void DrawScreenText(TextCommand&& textCommandArgs);

	private:
		std::vector<TextCommand> TextCommands;
		std::unique_ptr<Font> mFont;
	};
}