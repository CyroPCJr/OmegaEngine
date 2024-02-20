#pragma once
#include <OmegaEngine/Inc/Omega.h>

namespace Omega
{
	class Skydome final
	{
	public:

		void Initialize(const std::filesystem::path& texturePath);
		void SetSize(float radius, int rings, int slices);
		void Render(const Omega::Graphics::Camera& camera);

		void Update(const Omega::Graphics::Camera& camera);

		void Terminate();

	private:

		Omega::Graphics::MeshBuffer mMeshBufferSkyDome;

		Omega::Graphics::Texture mSkyDomeTexture;
		Omega::Graphics::Sampler mSamplers;

		Omega::Graphics::ConstantBuffer mConstantBufferSkyDome;

		Omega::Graphics::VertexShader mVSSkyDome;
		Omega::Graphics::PixelShader mPSSkyDome;

		Omega::Math::Vector3 mSkyDomePos = Omega::Math::Vector3::Zero;
	};

}