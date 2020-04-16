#include "GameState.h"

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::LightGray);
	// Normalize vector mean vector lenght turn 1
	//NDC - Normalize Device Coordinate

	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });


	// Testing triangle using previous class
	/*mVertices.emplace_back(Vertex{ Vector3{ 0.0f, 0.5f, 0.0f },   Color{Colors::Aqua} });
	mVertices.emplace_back(Vertex{ Vector3{ 0.5f, -0.5f, 0.0f }, Color{Colors::Green} });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.5f, 0.0f }, Color{Colors::Red} });*/
	//mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.5f, 0.0f }, Color{Colors::Black} });

	/* FINAL HOMEWORK

	Update HelloTexturing to use a MeshPX data to draw texture mapped cubes
	You will need to add Sampler and Texture classes provided
	You will need to use DoTexturing fx Shaders
	Andd a new class called Graphics::MeshBuilder with the following functions:

	namespace Omega::Graphics
	{
		class MeshBuilder
		{
		public:
			static MeshPX CreatePlanePX();
			static MeshPX CreateCylinderPX();
			static MeshPX CreateSpherePX(float radius, int rings = 16, int slices = 16);
		}
	}

	 This will alllow you do create a mesh easilly by doing:

	 auto mesh = MeshBuilder::CreateSpherePX(...);

	 Add HelloEarth to test a texture mapped sphere using Earth texture

	 A plane:
	 for ( int y = 0; y < height; ++y)
	 {
		for (int x=0; x< width; ++x)
		{
			vertices.push_back({x,y,0.0f}, static_cast<float>(1/x), static_cast<float>(1/y));
		}
	 }

	 A cylinder: // radius
	 for ( int y = 0; y < height; ++y)
	 {
		for (int theta = 0; theta <= TwoPi; theta +=twopi / rows)
		{
			vertices.push_back({ sin(theta)*radius, y ,cos(theta)*radius}....);
		}
	 }

	 A Sphere:
	 for (int phi = 0; phi < PI; phi+= rings/Pi)
	 {
		for (int theta = 0; theta < TwoPi; theta += silce/twopi)
		{
			vertices.push_back({ sin(theta)*r, cos(theta) *r}....);
		}
	 }

	*/

	//mMeshBuffer.Initialize(MeshBuilder::CreateCubePX());
	//mMeshBuffer.Initialize(MeshBuilder::CreatePlanePX(2, 2));
	mMeshBuffer.Initialize(MeshBuilder::CreateCylinderPX(2.0f,2,90));

	mConstantBuffer.Initialize(sizeof(Matrix4));

	// Compile and create vertex shader
	mVertexShader.Initialize("../../Assets/Shaders/DoTexturing.fx", VertexPX::Format);
	// Compile and create pixel shader
	mGouraudShadingPixelShader.Initialize("../../Assets/Shaders/DoTexturing.fx");

	mSamplers.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Clamp);
	mTexture.Initialize("beer.png");
}

void GameState::Terminate()
{
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mGouraudShadingPixelShader.Terminate();

	mTexture.Terminate();
	mSamplers.Terminate();
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
	//auto matWorld1 = Matrix4::RotationX(mRotation);
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();

	mTexture.BindVS();
	mSamplers.BindVS();
	mConstantBuffer.BindVS();
	mVertexShader.Bind();
	mGouraudShadingPixelShader.Bind();

	/*auto matTrans = Matrix4::Translation(Vector3(i, i, i));
	auto matScale = Matrix4::Scaling(i*0.25f);*/
	auto matTrans = Matrix4::Identity;
	auto matWVP = Transpose(matWorld * matTrans*  matView * matProj);

	mConstantBuffer.Update(&matWVP);
	mMeshBuffer.Draw();

	//for (float i = 0; i < 10; ++i)
	//{
	//	auto matTrans = Matrix4::Translation(Vector3(i, i, i));
	//	auto matScale = Matrix4::Scaling(i*0.25f);
	//	auto matWVP = Transpose(matScale* matTrans * matWorld * matWorld1 * matView * matProj);

	//	mConstantBuffer.Set(&matWVP);
	//	mMeshBuffer.Draw();
	//}
}