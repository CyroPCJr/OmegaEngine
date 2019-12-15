#include "Precompiled.h"
#include "MeshBuffer.h"

#include "D3DUtil.h"

using namespace Omega;
using namespace Omega::Graphics;

void MeshBuffer::Initialize(const void* vertices, int vertexSize, int vertexCount, const uint32_t* indices, int indexCount)
{
	mIndiceCount = indexCount;
	mVertexSize = vertexSize;

	// size in memory bytes
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = vertexCount * mVertexSize;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = vertices;

	auto device = GetDevice();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	OMEGAASSERT(SUCCEEDED(hr), "Fail to create vertex buffer.");

	// Create index buffer
	bufferDesc.ByteWidth = indexCount * sizeof(uint32_t);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	initData.pSysMem = indices;

	hr = device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
	OMEGAASSERT(SUCCEEDED(hr), "Fail to create index buffer.");
}

void MeshBuffer::Terminate()
{
	SafeRelease(mIndexBuffer);
	SafeRelease(mVertexBuffer);
}

void MeshBuffer::Draw() const
{
	auto context = GetContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = mVertexSize;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(mIndiceCount, 0, 0);
}
