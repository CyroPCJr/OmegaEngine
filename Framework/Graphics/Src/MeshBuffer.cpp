#include "Precompiled.h"
#include "MeshBuffer.h"

#include "D3DUtil.h"

using namespace Omega;
using namespace Omega::Graphics;

void MeshBuffer::Initialize(const void* vertices, int vertexSize, int vertexCount, const uint32_t* indices, int indexCount, bool dynamic)
{
	mIndiceCount = indexCount;
	mVertexSize = vertexSize;

	// size in memory bytes
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = vertexCount * mVertexSize;
	bufferDesc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0; // Use CPU
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = vertices;

	auto device = GetDevice();

	HRESULT hr = device->CreateBuffer(&bufferDesc, vertices ? &initData : nullptr, &mVertexBuffer);
	OMEGAASSERT(SUCCEEDED(hr), "Fail to create vertex buffer.");

	// Create index buffer
	bufferDesc.ByteWidth = indexCount * sizeof(uint32_t);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	initData.pSysMem = indices;

	hr = device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
	OMEGAASSERT(SUCCEEDED(hr), "Fail to create index buffer.");

	// Create index buffer
	if (indices && indexCount > 0)
	{
		bufferDesc.ByteWidth = indexCount * sizeof(uint32_t);
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		initData.pSysMem = indices;
		hr = device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
		OMEGAASSERT(SUCCEEDED(hr), "Failed to create index buffer");
	}
}

void MeshBuffer::SetTopology(Topology topology)
{
	if (topology == Topology::Lines)
	{
		mTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	}
	else
	{
		mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
}

void MeshBuffer::Update(const void* vertexData, uint32_t numVertices)
{
	mVertexCount = numVertices;
	auto context = GetContext();
	D3D11_MAPPED_SUBRESOURCE resource;
	context->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, vertexData, numVertices * mVertexSize);
	context->Unmap(mVertexBuffer, 0);
}

void MeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mIndexBuffer);
}

void MeshBuffer::Draw() const
{
	auto context = GetContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = mVertexSize;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	if (mIndexBuffer)
	{
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(mIndiceCount, 0, 0);
	}
	else
	{
		context->Draw(mVertexCount, 0);
	}
}
