#include "Precompiled.h"
#include "PixelShader.h"

#include "D3DUtil.h"

using namespace Omega;
using namespace Omega::Graphics;

void PixelShader::Initialize(const std::filesystem::path& filePath, const char* shaderName)
{
	DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		filePath.wstring().c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		shaderName, "ps_5_0",
		shaderFlag, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	OMEGAASSERT(SUCCEEDED(hr), "Failed to compile pixel shader.");

	auto device = GetDevice();

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to create pixel shader.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void PixelShader::Terminate()
{
	SafeRelease(mPixelShader);
}

void PixelShader::Bind() const
{
	auto context = GetContext();
	context->PSSetShader(mPixelShader, nullptr, 0);
}
