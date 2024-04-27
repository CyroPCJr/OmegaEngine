#pragma once
#include <OmegaEngine/Inc/Omega.h>

namespace Omega
{
	class Cloth final
	{
	public:

		struct Settings
		{
			std::filesystem::path path{};
			Omega::Math::Vector3 startPosition = Omega::Math::Vector3::Zero;
			size_t width{ 20 };
			size_t height{ 20 };
		};

		void Initialize(const Settings& settings);

		void Render(const Omega::Graphics::Camera& camera);

		//void SetPosition(const Omega::Math::Vector3& position);

		void Update(float deltaTime);
		void Terminate();

		void SetShowCloth(bool show) noexcept { mShowCloth = show; }
		void SetShowTextureCloth(bool showTexture) noexcept { mShowTexture = showTexture; }

	private:
		void InitializeParticles();

		constexpr int GetIndex(int x, int y, int column) noexcept { return (y * column) + x; }

		Settings mSettings;

		Omega::Graphics::MeshPX mMeshPlane;
		Omega::Graphics::MeshBuffer mMeshBuffer;
		Omega::Graphics::VertexShader mVertexShader;
		Omega::Graphics::PixelShader mPixelShader;
		Omega::Graphics::Texture mTexture;
		Omega::Graphics::Sampler mSampler;
		Omega::Graphics::ConstantBuffer mConstantBuffer;

		Omega::Graphics::RasterizerState mRasterizer;

		Omega::Physics::PhysicsWorld mPhysicsWorld;
		//std::vector<std::unique_ptr<Omega::Physics::Particle>> mParticles;

		bool mShowCloth = false;
		bool mShowTexture = false;
	};

}