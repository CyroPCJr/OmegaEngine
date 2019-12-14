#include "GameState.h"

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::LightGray);

	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });

	// Normalize vector mean vector lenght turn 1
	//NDC - Normalize Device Coordinate

	// Testing triangle using previous class
	/*mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 0.5f, 0.0f },   Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, -0.5f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.5f, 0.0f }, Color{Colors::Red} });*/
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.5f, 0.0f }, Color{Colors::Black} });

	mMesh.mVertices.emplace_back(Vertex{ Vector3{  0.0f,  0.5f,  0.0f }, Color{Colors::Orange} });
	mMesh.mVertices.emplace_back(Vertex{ Vector3{  0.5f,  0.0f,  0.0f }, Color{Colors::Cornsilk} });
	mMesh.mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.0f,  0.0f }, Color{Colors::DarkBlue} });
	mMesh.mVertices.emplace_back(Vertex{ Vector3{  0.0f, -0.5f, 0.0f }, Color{Colors::SlateBlue} });

	mMesh.mIndices.push_back(0);
	mMesh.mIndices.push_back(1);
	mMesh.mIndices.push_back(2);

	mMesh.mIndices.push_back(1);
	mMesh.mIndices.push_back(3);
	mMesh.mIndices.push_back(2);

	// CUBEEE
	//Front
	/*mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f,-0.5f }, Color{Colors::Blue} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,-0.5f }, Color{Colors::Red} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,-0.5f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,-0.5f }, Color{Colors::Orange} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,-0.5f }, Color{Colors::Black} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, -0.5f,-0.5f }, Color{Colors::Yellow} });*/
	//left
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f, -0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f, 0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f, 0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f, -0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f, -0.5f }, Color{Colors::Green} });
	////Back
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,0.5f }, Color{Colors::Red} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,0.5f }, Color{Colors::Red} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f,0.5f }, Color{Colors::Red} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f, -0.5f,0.5f }, Color{Colors::Red} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,0.5f }, Color{Colors::Red} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,0.5f }, Color{Colors::Red} });
	////Right
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,-0.5f }, Color{Colors::Pink} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,-0.5f,0.5f }, Color{Colors::Pink} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,-0.5f,-0.5f }, Color{Colors::Pink} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f, -0.5f }, Color{Colors::Pink} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f, 0.5f }, Color{Colors::Pink} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,-0.5f, 0.5f }, Color{Colors::Pink} });
	////Top
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,-0.5f }, Color{Colors::Black} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f,-0.5f }, Color{Colors::Black} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f, 0.5f }, Color{Colors::Black} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f,0.5f }, Color{Colors::Black} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,0.5f,0.5f }, Color{Colors::Black} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,0.5f, -0.5f }, Color{Colors::Black} });
	////Bottom
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,-0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,-0.5f,-0.5f }, Color{Colors::Red} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,-0.5f, 0.5f }, Color{Colors::Blue} });
	//mVertices.emplace_back(Vertex{ Vector3{ 0.5f,-0.5f,0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f,0.5f }, Color{Colors::Green} });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f,-0.5f, -0.5f }, Color{Colors::Green} });

	//auto device = GraphicsSystem::Get()->GetDevice();

	//// Create constant buffer
	//D3D11_BUFFER_DESC constantBuffer{};
	//constantBuffer.ByteWidth = sizeof(Matrix4);
	//constantBuffer.Usage = D3D11_USAGE_DEFAULT;
	//constantBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	//HRESULT hr = device->CreateBuffer(&constantBuffer, nullptr, &mConstantBuffer);
	//OMEGAASSERT(SUCCEEDED(hr), "Fail to create constant buffer.");

#pragma region Create vertex buffer

	//D3D11_BUFFER_DESC bufferDesc{};
	//// size in memory bytes
	//bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size()) * sizeof(Vertex);
	//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bufferDesc.CPUAccessFlags = 0;
	//bufferDesc.MiscFlags = 0;
	//bufferDesc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA initData{};
	//initData.pSysMem = mVertices.data();

	//hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	//OMEGAASSERT(SUCCEEDED(hr), "Fail to create vertex buffer.");

	//// Create index buffer
	//bufferDesc.ByteWidth = static_cast<UINT>(mIndices.size()) * sizeof(uint32_t);
	//bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	//initData.pSysMem = mIndices.data();

	//hr = device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
	//OMEGAASSERT(SUCCEEDED(hr), "Fail to create index buffer.");
#pragma endregion
	
	// TODO: #1 testar aqui
	mConstantBuffer.Initialize(sizeof(Matrix4));
	
	mMeshBuffer.Initialize(mMesh.mVertices.data(), static_cast<UINT>(mMesh.mVertices.size()),
			mMesh.mIndices.data(), static_cast<UINT>(mMesh.mIndices.size()));

	// Compile and create vertex shader
	mVertexShader.Initialize();
	// Compile and create pixel shader
	mPixelShader.Initialize();
}

void GameState::Terminate()
{
	mVertexShader.Terminate();
	/*SafeRelease(mConstantBuffer);
	SafeRelease(mIndexBuffer);
	SafeRelease(mVertexBuffer);*/
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
}

void GameState::Update(float deltaTime)
{
	//TODO fill this function using mouse movements

	const float kMoveSpeed = 7.5f;
	const float kTurnSpeed = 0.5f;
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-kMoveSpeed * deltaTime);
	}
	mCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mRotation += deltaTime;
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mRotation -= deltaTime;
	}
}

void GameState::Render()
{

	auto matWorld = Matrix4::RotationY(mRotation);
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();
	auto matWVP = Transpose(matWorld * matView * matProj);

	mConstantBuffer.Set(&matWVP);
	mConstantBuffer.Bind();

	//auto context = GraphicsSystem::Get()->GetContext();
	//context->UpdateSubresource(mConstantBuffer, 0, nullptr, &matWVP, 0, 0);
	//context->VSSetConstantBuffers(0, 1, &mConstantBuffer);


	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);*/

	mVertexShader.Bind();
	mPixelShader.Bind();
	//TODO: #2 Testar aqui tb
	mMeshBuffer.Draw();
	//context->Draw(mVertices.size(), 0); <-- This is for when we don't have an index buffer
	//context->DrawIndexed((UINT)mIndices.size(), 0, 0);
}