#pragma once
#include "Colors.h"

interface IFW1Factory;
interface IFW1FontWrapper;

namespace Omega::Graphics
{
	class Font
	{
	public:
		void Initialize();
		void Terminate();

		void Draw(const wchar_t* str, float x, float y, float size, const Color& color);
		void Draw(const wchar_t* str, const Math::Vector2& position, float size, const Color& color);

	private:
		IFW1Factory* mFW1Factory = nullptr;
		IFW1FontWrapper* mFontWrapper = nullptr;
	};
}