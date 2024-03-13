#include "Precompiled.h"
#include "Font.h"
#include "D3DUtil.h"

#include <FW1FontWrapper_1_1\FW1FontWrapper.h>

using namespace Omega::Graphics;
using namespace Omega::Math;

namespace
{

	inline uint32_t ToColor(const Color& color) noexcept
	{
		const uint8_t red = static_cast<uint8_t>(color.x * 0xFF);
		const uint8_t green = static_cast<uint8_t>(color.y * 0xFF);
		const uint8_t blue = static_cast<uint8_t>(color.z * 0xFF);

		//// Combine the RGB components into a 32-bit color value
		return 0xff000000 | (blue << 16) | (green << 8) | red;
	}
}

Font::Font(const FontType& font) noexcept(false)
{
	const std::wstring fontType = [&font]()
		{
			if (font == FontType::Arial) {
				return L"Arial";
			}
			else if (font == FontType::CourierNew) {
				return L"Courier New";
			}
			else if (font == FontType::Consolas) {
				return L"Consolas";
			}
			else
			{
				return L"Arial";
			}
		}();

		ID3D11Device* device = GetDevice();
		FW1CreateFactory(FW1_VERSION, &mFW1Factory);
		const auto hr = mFW1Factory->CreateFontWrapper(device, fontType.c_str(), &mFontWrapper);
		OMEGAASSERT(SUCCEEDED(hr), "[Font] Failed to initialize FW1FontWrapper. Error = %x", hr);
}

Font::~Font() noexcept(false)
{
	SafeRelease(mFontWrapper);
	SafeRelease(mFW1Factory);
}

void Font::Draw(const wchar_t* str, float x, float y, float size, const Color& color)
{
	ID3D11DeviceContext* context = GetContext();
	mFontWrapper->DrawString(context, str, size, x, y, ToColor(color), FW1_RESTORESTATE);
}

void Font::Draw(const wchar_t* str, const Vector2& position, float size, const Color& color)
{
	Draw(str, position.x, position.y, size, color);
}

void Font::Draw(std::wstring_view str, const Math::Vector2& position, float size, const Color& color)
{
	Draw(std::wstring(str).c_str(), position.x, position.y, size, color);
}
