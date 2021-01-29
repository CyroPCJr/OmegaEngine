#pragma once

#include <OmegaEngine/Inc/Omega.h>
namespace Omega
{
	class Cloth
	{
	public:

		Cloth() = default;
		~Cloth() = default;

		void Initialize(const std::filesystem::path& texturePath, uint32_t size = 20);
		void Render(const Omega::Graphics::Camera& camera);

		void ShowParticles();

		void Update();
		void Terminate();

	private:

		uint32_t mSize = 0;

		Omega::Graphics::MeshPX mMeshPlane;
		Omega::Graphics::MeshBuffer mMeshBuffer;
		Omega::Graphics::VertexShader mVertexShader;
		Omega::Graphics::PixelShader mPixelShader;
		Omega::Graphics::Texture mTexture;
		Omega::Graphics::Sampler mSampler;
		Omega::Graphics::ConstantBuffer mConstantBuffer;

		Omega::Physics::PhysicsWorld mPhysicsWorld;
		std::vector<Omega::Physics::Particle*> mParticles;
	};

}