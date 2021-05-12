#pragma once

#include <OmegaEngine/Inc/Omega.h>

class GameState : public Omega::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
private:
	void InitializeParticles(int maxParticles);

	void UseRawParticles(int count);
	void UseStickParticles(int count);
	void UseTetrahedronParticles(int count);
	void UseCubeParticles(int count);
	void UseBallAndChains(int count);

	Omega::Graphics::Camera mCamera;
	Omega::Physics::PhysicsWorld mPhysicsWorld;

	std::vector<Omega::Physics::Particle*> mParticles;

	Omega::Graphics::MeshPX mMeshPlane;
	Omega::Graphics::MeshBuffer mMeshBuffer;
	Omega::Graphics::VertexShader mVertexShader;
	Omega::Graphics::PixelShader mPixelShader;
	Omega::Graphics::Texture mTexture;
	Omega::Graphics::Sampler mSampler;
	Omega::Graphics::ConstantBuffer mConstantBuffer;

	Omega::Cloth mClothBrazilFlag;
	Omega::Cloth mClothCanadaFlag;

	// ImGui
	std::vector<float> mVecFrames;
	const size_t mMaxFrameSize = 100;
};