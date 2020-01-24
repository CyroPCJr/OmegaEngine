#include "Precompiled.h"
#include "ConstantBuffer.h"

#include "D3DUtil.h"

using namespace Omega;
using namespace Omega::Graphics;

void ConstantBuffer::Initialize(uint32_t size)
{
	auto device = GetDevice();

	// Create constant buffer
	D3D11_BUFFER_DESC constantBuffer{};
	constantBuffer.ByteWidth = size;
	constantBuffer.Usage = D3D11_USAGE_DEFAULT;
	constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = device->CreateBuffer(&constantBuffer, nullptr, &mConstantBuffer);
	OMEGAASSERT(SUCCEEDED(hr), "Fail to create constant buffer.");
}

void ConstantBuffer::Terminate()
{
	SafeRelease(mConstantBuffer);
}

void ConstantBuffer::BindVS(uint32_t slot) const
{
	GetContext()->VSSetConstantBuffers(slot, 1, &mConstantBuffer);
}

void ConstantBuffer::BindPS(uint32_t slot) const
{
	GetContext()->PSSetConstantBuffers(slot, 1, &mConstantBuffer);
}

void ConstantBuffer::Update(void* data)
{
	GetContext()->UpdateSubresource(mConstantBuffer, 0, nullptr, data, 0, 0);
}