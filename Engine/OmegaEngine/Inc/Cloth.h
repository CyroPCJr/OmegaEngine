#pragma once
#include <OmegaEngine/Inc/Omega.h>

namespace Omega
{
	class Cloth
	{
	public:

		Cloth() = default;
		~Cloth() = default;

		void Initialize(const std::filesystem::path& texturePath, uint32_t width = 20, uint32_t height = 20);
		void Render(const Omega::Graphics::Camera& camera);

		void ShowCloth(const Omega::Math::Vector3& position);

		void Update(float deltaTime);
		void Terminate();

		void IsUseCloth(bool use) { mIsUseCloth = use; }

	private:

		int GetIndex(int x, int y, int column) { return (y * column) + x; }

		uint32_t mWidth = 0;
		uint32_t mHeight = 0;
		bool mIsUseCloth = false;

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