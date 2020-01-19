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

	mMesh.vertices.emplace_back(VertexPC{ Vector3{  0.0f,  0.5f,  -0.5f }, Color{Colors::Orange} });
	mMesh.vertices.emplace_back(VertexPC{ Vector3{  0.5f,  0.0f,  -0.5f }, Color{Colors::Cornsilk} });
	mMesh.vertices.emplace_back(VertexPC{ Vector3{ -0.5f, -0.0f,  -0.5f }, Color{Colors::DarkBlue} });
	mMesh.vertices.emplace_back(VertexPC{ Vector3{  0.0f, -0.5f, -0.5f }, Color{Colors::SlateBlue} });

	mMesh.vertices.emplace_back(VertexPC{ Vector3{  0.0f,  0.5f, 0.5f }, Color{Colors::Orange} });
	mMesh.vertices.emplace_back(VertexPC{ Vector3{  0.5f,  0.0f, 0.5f }, Color{Colors::Cornsilk} });
	mMesh.vertices.emplace_back(VertexPC{ Vector3{ -0.5f, -0.0f, 0.5f }, Color{Colors::DarkBlue} });
	mMesh.vertices.emplace_back(VertexPC{ Vector3{  0.0f, -0.5f, 0.5f }, Color{Colors::SlateBlue} });

	// Front
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(1);
	mMesh.indices.push_back(2);
	mMesh.indices.push_back(1);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(2);
	// Right
	mMesh.indices.push_back(4);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(7);
	mMesh.indices.push_back(5);
	// Back
	mMesh.indices.push_back(4);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(1);
	// Left
	mMesh.indices.push_back(2);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(7);
	// Top
	mMesh.indices.push_back(4);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(6);
	mMesh.indices.push_back(0);
	mMesh.indices.push_back(2);
	// Botton
	mMesh.indices.push_back(1);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(3);
	mMesh.indices.push_back(5);
	mMesh.indices.push_back(7);

	mMeshBuffer.Initialize(mMesh);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	// Compile and create vertex shader
	mVertexShader.Initialize("../Assets/Shaders/DoTransform.fx", VertexPC::Format);
	// Compile and create pixel shader
	mPixelShader.Initialize("../Assets/Shaders/DoTransform.fx");
}

void GameState::Terminate()
{
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
}

void GameState::Update(float deltaTime)
{
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
	auto matWorld1 = Matrix4::RotationX(mRotation);
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();

	mConstantBuffer.BindVS();
	mVertexShader.Bind();
	mPixelShader.Bind();
	for (float i = 0; i < 10; ++i)
	{
		auto matTrans = Matrix4::Translation(Vector3(i, i, i));
		auto matScale = Matrix4::Scaling(i*0.25f);
		auto matWVP = Transpose(matScale* matTrans * matWorld * matWorld1 * matView * matProj);

		mConstantBuffer.Update(&matWVP);
		mMeshBuffer.Draw();
	}
}