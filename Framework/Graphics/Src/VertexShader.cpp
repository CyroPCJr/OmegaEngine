#include "Precompiled.h"
#include "VertexShader.h"

#include "D3DUtil.h"
#include "VertexTypes.h"

using namespace Omega;
using namespace Omega::Graphics;

namespace
{

	auto GetVertexLayout(uint32_t vertexFormat)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;

		if (vertexFormat & VE_Position)
		{
			vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		if (vertexFormat & VE_Color)
		{
			vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		if (vertexFormat & VE_Normal)
		{
			vertexLayout.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_Tangent)
		{
			vertexLayout.push_back({ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_TextCoord)
		{
			vertexLayout.push_back({ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}

		return vertexLayout;
	}
}

void VertexShader::Initialize(const std::filesystem::path& filePath, uint32_t vertexFormat)
{
	DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		filePath.wstring().c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlag, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	OMEGAASSERT(SUCCEEDED(hr), "Failed to compile vertex shader.");

	const auto device = GetDevice();

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to create vertex shader.");

	auto vertexLayout = GetVertexLayout(vertexFormat);
	
	// Create input layout
	hr = device->CreateInputLayout(
		vertexLayout.data(),
		static_cast<int>(vertexLayout.size()),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to create input layout.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void VertexShader::Terminate()
{
	SafeRelease(mInputLayout);
	SafeRelease(mVertexShader);
}

void VertexShader::Bind()
{
	auto context = GetContext();
	context->IASetInputLayout(mInputLayout); // Input Assembler
	context->VSSetShader(mVertexShader, nullptr, 0); // Vertex Shader
}