#include "Skydome.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Math;

void Skydome::Initialize(const std::filesystem::path& texturePath)
{
	MeshPX mMeshSkyDome = MeshBuilder::CreateSpherePX(1500.0f, 200, 200, false);
	mMeshBufferSkyDome.Initialize(mMeshSkyDome);

	std::filesystem::path doTexturingShader = "../../Assets/Shaders/DoTexturing.fx";
	mVSSkyDome.Initialize(doTexturingShader, VertexPX::Format);
	mPSSkyDome.Initialize(doTexturingShader);

	std::filesystem::path rootImages = "../../Assets/Textures";
	mSamplers.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mSkyDomeTexture.Initialize(rootImages / texturePath);
	mConstantBufferSkyDome.Initialize(sizeof(Matrix4));

}

void Skydome::Render(const Camera& camera)
{
	auto matView = camera.GetViewMatrix();
	auto matProj = camera.GetPerspectiveMatrix();

	auto skyDomePos = Matrix4::Translation(mSkyDomePos);
	auto transposeSkyDome = Transpose(skyDomePos * matView * matProj);;

	mConstantBufferSkyDome.BindVS();
	mConstantBufferSkyDome.BindPS();
	mVSSkyDome.Bind();
	mPSSkyDome.Bind();
	mSkyDomeTexture.BindPS();
	mSamplers.BindPS();

	mConstantBufferSkyDome.Update(&transposeSkyDome);
	mMeshBufferSkyDome.Draw();
}

void Skydome::Update(const Camera& camera)
{
	mSkyDomePos = camera.GetPosition();
}

void Skydome::Terminate()
{
	mConstantBufferSkyDome.Terminate();
	mSkyDomeTexture.Terminate();
	mSamplers.Terminate();
	mPSSkyDome.Terminate();
	mVSSkyDome.Terminate();
	mMeshBufferSkyDome.Terminate();
}
