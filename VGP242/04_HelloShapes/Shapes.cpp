#include "Shapes.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

void Shapes::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::LightGray);
	// Normalize vector mean vector lenght turn 1
	//NDC - Normalize Device Coordinate

	/*mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 0.3f, 0.0f }, Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.3f, -0.3f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.3f, -0.3f, 0.0f }, Color{Colors::Red} });*/

	auto device = GraphicsSystem::Get()->GetDevice();

#pragma region Create vertex buffer

	D3D11_BUFFER_DESC bufferDesc{};
	// size in memory bytes
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size()) * sizeof(Vertex);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = mVertices.data();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	OMEGAASSERT(SUCCEEDED(hr), "Fail to create vertex buffer.");

#pragma endregion

	// Compile and create vertex shader
	DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		L"../../Assets/Shaders/SimpleDoNothing.fx",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlag, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	OMEGAASSERT(SUCCEEDED(hr), "Failed to compile vertex shader.");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to create vertex shader.");

	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });
	// Add color to shaders
	vertexLayout.push_back({ "COLOR",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		D3D11_APPEND_ALIGNED_ELEMENT,
		D3D11_INPUT_PER_VERTEX_DATA,
		0 });

	// Create input layout
	hr = device->CreateInputLayout(
		vertexLayout.data(),
		(UINT)vertexLayout.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to create input layout.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	hr = D3DCompileFromFile(
		L"../../Assets/Shaders/SimpleDoNothing.fx",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlag, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	OMEGAASSERT(SUCCEEDED(hr), "Failed to compile pixel shader.");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	OMEGAASSERT(SUCCEEDED(hr), "Failed to create pixel shader.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void Shapes::Terminate()
{	
	SafeRelease(mVertexBuffer);
	SafeRelease(mVertexShader);
	SafeRelease(mInputLayout);
	SafeRelease(mPixelShader);
}

void Shapes::Update(float deltaTime)
{
}

void Shapes::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->IASetInputLayout(mInputLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	context->VSSetShader(mVertexShader, nullptr, 0);
	context->PSSetShader(mPixelShader, nullptr, 0);

	context->Draw(static_cast<UINT>(mVertices.size()), 0);
}
