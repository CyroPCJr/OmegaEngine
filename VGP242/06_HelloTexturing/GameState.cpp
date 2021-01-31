#include "GameState.h"

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);
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
		for (int theta = 0; theta < TwoPi; theta +=rings / twopi)
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

	/*mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f,  0.5f,  -0.5f }, 0.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.5f,  0.0f,  -0.5f }, 0.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{ -0.5f,  0.0f,  -0.5f }, 1.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f, -0.5f,  -0.5f }, 1.0f, 0.0f });

	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f,  0.5f,  0.5f }, 1.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.5f,  0.0f,  0.5f }, 0.0f, 0.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{ -0.5f,  0.0f,  0.5f }, 1.0f, 1.0f });
	mMesh.vertices.emplace_back(VertexPX{ Vector3{  0.0f, -0.5f,  0.5f }, 1.0f, 0.0f });*/

	//mMesh = MeshBuilder::CreateSpherePX(100.0f, 30, 30, false);
	mMesh = MeshBuilder::CreatePlanePX(20,15);
	mMeshBuffer.Initialize(mMesh);
	mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path doTexturingShader = "../../Assets/Shaders/DoTexturing.fx";
	// Compile and create vertex shader
	mVertexShader.Initialize(doTexturingShader, VertexPX::Format);
	// Compile and create pixel shader
	mPixelShader.Initialize(doTexturingShader);

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mTexture.Initialize("../../Assets/Textures/Brazil_flag.png");//beer.png");
}

void GameState::Terminate()
{
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mSampler.Terminate();
	mTexture.Terminate();
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
	auto context = GraphicsSystem::Get()->GetContext();

	auto matRot = Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetPerspectiveMatrix();
	mConstantBuffer.BindVS();

	mVertexShader.Bind();
	mPixelShader.Bind();

	mSampler.BindPS();
	mTexture.BindPS();
	
	const float spacing = 1.8f;
	/*for (int y = -1; y <= 1; ++y)
	{
		for (float x = -1; x <= 1; ++x)
		{
			
		}
	}*/
	//auto matTrans = Matrix4::Translation({ x * spacing, y * spacing, 0.0f });
	//auto matTrans = Matrix4::Translation({ x * spacing, y * spacing, 0.0f });
	auto matWVP = Transpose(matRot * matView * matProj);
	mConstantBuffer.Update(&matWVP);
	mMeshBuffer.Draw();
}