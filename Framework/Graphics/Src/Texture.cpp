#include "Precompiled.h"
#include "Texture.h"

#include "D3DUtil.h"
#include <DirectXTK/Inc/WICTextureLoader.h>

using namespace PCEngine::Graphics;

void Texture::Initialize(const std::filesystem::path& fileName)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(GetDevice(), GetContext(), fileName.c_str(), nullptr, &mShaderResourceView);
	ASSERT(SUCCEEDED(hr), "Failed to load texture %ls.", fileName.c_str());
}

void Texture::Terminate()
{
	SafeRelease(mShaderResourceView);
}

void Texture::Bind() const
{
	GetContext()->PSSetShaderResources(0, 1, &mShaderResourceView);
}
