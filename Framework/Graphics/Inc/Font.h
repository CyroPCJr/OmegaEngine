#pragma once
#include "Colors.h"

interface IFW1Factory;
interface IFW1FontWrapper;

namespace Omega::Graphics
{
	enum class FontType
	{
		Arial,
		CourierNew,
		Consolas,
	};

	class Font final
	{
	public:

		explicit Font(const FontType& font = FontType::Consolas) noexcept(false);
		~Font() noexcept(false);

		//copy constructor
		Font(const Font&) = delete;
		//copy assignment
		Font& operator=(const Font&) = delete;
		//move constructor
		Font(Font&&) = delete;
		//move assigment
		Font& operator=(Font&&) = delete;

		void Draw(const wchar_t* str, float x, float y, float size, const Color& color);
		void Draw(const wchar_t* str, const Math::Vector2& position, float size, const Color& color);
		void Draw(std::wstring_view str, const Math::Vector2& position, float size, const Color& color);

	private:
		IFW1Factory* mFW1Factory{ nullptr };
		IFW1FontWrapper* mFontWrapper{ nullptr };
	};
}