#include "Precompiled.h"
#include "ConstantBuffer.h"

#include "D3DUtil.h"

using namespace Omega;
using namespace Omega::Graphics;

void ConstantBuffer::Initialize(UINT size)
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

void ConstantBuffer::Bind()
{
	auto context = GetContext();
	context->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ConstantBuffer::Set(void* data)
{
	auto context = GetContext();
	context->UpdateSubresource(mConstantBuffer, 0, nullptr, data, 0, 0);
}
