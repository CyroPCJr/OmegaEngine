#include "Precompiled.h"
#include "Texture.h"

#include "D3DUtil.h"
#include <DirectXTK/Inc/WICTextureLoader.h>

using namespace Omega::Graphics;

Texture::~Texture()
{
	OMEGAASSERT(mShaderResourceView == nullptr, "[Texture] Texture not released.");
}

void Texture::Initialize(const std::filesystem::path& fileName)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(GetDevice(), GetContext(), fileName.c_str(), nullptr, &mShaderResourceView);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to load texture %ls.", fileName.c_str());

	
}

void Texture::Terminate()
{
	SafeRelease(mShaderResourceView);
}

void Texture::BindPS(uint32_t slot) const
{
	GetContext()->PSSetShaderResources(slot, 1, &mShaderResourceView);
}

void Texture::BindVS(uint32_t slot) const
{
	GetContext()->VSSetShaderResources(slot, 1, &mShaderResourceView);
}
