#include "Precompiled.h"
#include "FontRenderer.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

FontRenderer::FontRenderer() noexcept(false)
{
	mFont = std::make_unique<Font>();
}

void FontRenderer::Render()
{
	for (const auto& command : TextCommands)
	{
		mFont->Draw(command.str.c_str(), command.x, command.y, command.size, command.color);
	}
	TextCommands.clear();
}

void FontRenderer::DrawScreenText(std::wstring_view str, const Math::Vector2& position, float fontSize, const Color& color)
{
	DrawScreenText({ std::wstring(str), fontSize, position, color});
}

void Omega::Graphics::FontRenderer::DrawScreenText(TextCommand&& textCommandArgs)
{
	auto& [text, color, fontSize, x, y] = textCommandArgs;
	const size_t length = text.size();
	std::string strCopy;
	std::transform(text.begin(), text.end(), std::back_inserter(strCopy), [](wchar_t c) 
		{
			return static_cast<char>(c);
		});
	const int convertResult = MultiByteToWideChar(CP_UTF8, 0, strCopy.c_str(), length, nullptr, 0);
	std::wstring wideString(convertResult, 0);
	MultiByteToWideChar(CP_UTF8, 0ul, strCopy.c_str(), length, &wideString.at(0), convertResult);
	TextCommands.emplace_back(std::move(wideString), fontSize, x, y, color);
}
