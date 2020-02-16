#pragma once

namespace Omega::Graphics {

	class Sampler
	{
	public:
		enum class Filter { Point, Linear, Anisotropic };
		enum class AddressMode { Border, Clamp, Mirror, Wrap };

		Sampler() = default;
		~Sampler();

		Sampler(const Sampler&) = delete;
		Sampler& operator=(const Sampler&) = delete;

		void Initialize(Filter filter, AddressMode addressMode);
		void Terminate();

		void BindPS(uint32_t slot = 0) const;
		void BindVS(uint32_t slot = 0) const;

	private:
		ID3D11SamplerState* mSampler = nullptr;
	};

}