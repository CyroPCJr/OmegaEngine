#include "Precompiled.h"
#include "Font.h"

#include "D3DUtil.h"
#include <FW1FontWrapper_1_1\FW1FontWrapper.h>

using namespace Omega::Graphics;
using namespace Omega::Math;

namespace
{
	inline uint32_t ToColor(const Color& color)
	{
		uint8_t r = static_cast<uint8_t>(color.x * 255);
		uint8_t g = static_cast<uint8_t>(color.y * 255);
		uint8_t b = static_cast<uint8_t>(color.z * 255);
		return 0xff000000 | (b << 16) | (g << 8) | r;
	}
}

void Font::Initialize()
{
	ID3D11Device* device = GetDevice();
	FW1CreateFactory(FW1_VERSION, &mFW1Factory);
	auto hr = mFW1Factory->CreateFontWrapper(device, L"Consolas", &mFontWrapper);
	OMEGAASSERT(SUCCEEDED(hr), "[Font] Failed to initialize FW1FontWrapper. Error = %x", hr);
}

void Font::Terminate()
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
