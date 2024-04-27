#include "Precompiled.h"
#include "Texture.h"
#include "D3DUtil.h"
#include <DirectXTK/Inc/WICTextureLoader.h>

using namespace Microsoft::WRL;
using namespace Omega::Graphics;

Texture::Texture(const std::filesystem::path& fileName)
{
	const HRESULT hr = DirectX::CreateWICTextureFromFile(GetDevice(), GetContext(), fileName.c_str(), nullptr, &*mShaderResourceView.GetAddressOf());
	OMEGAASSERT(SUCCEEDED(hr), "Failed to load texture %ls.", fileName.c_str());

	// Cache the texture dimensions
	ComPtr<ID3D11Resource> resource;
	mShaderResourceView->GetResource(resource.GetAddressOf());

	ComPtr<ID3D11Texture2D> texture;
	resource.As(&texture);
	D3D11_TEXTURE2D_DESC desc{};
	texture->GetDesc(&desc);

	mWidth = desc.Width;
	mHeight = desc.Height;
}

void Texture::BindPS(uint32_t slot) const
{
	GetContext()->PSSetShaderResources(slot, 1u, mShaderResourceView.GetAddressOf());
}

void Texture::BindVS(uint32_t slot) const
{
	GetContext()->VSSetShaderResources(slot, 1u, mShaderResourceView.GetAddressOf());
}
