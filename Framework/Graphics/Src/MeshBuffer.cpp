#include "Precompiled.h"
#include "MeshBuffer.h"

#include "D3DUtil.h"

using namespace Omega;
using namespace Omega::Graphics;

void MeshBuffer::Initialize(Vertex* vertices, UINT vertexCount, uint32_t* indices, UINT indexCount)
{
	mIndiceCount = indexCount;
	D3D11_BUFFER_DESC bufferDesc{};
	// size in memory bytes
	bufferDesc.ByteWidth = vertexCount * sizeof(Vertex);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = vertices;
	//initData.pSysMem = mVertices.data();

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

void MeshBuffer::Draw()
{
	auto context = GetContext();
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(mIndiceCount, 0, 0);
}
