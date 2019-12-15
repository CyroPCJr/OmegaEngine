#pragma once

namespace PCEngine::Graphics {

class Sampler
{
public:
	enum class Filter { Point, Linear, Anisotropic };
	enum class AddressMode { Border, Clamp, Mirror, Wrap };

	void Initialize(Filter filter, AddressMode addressMode);
	void Terminate();

	void Bind() const;

private:
	ID3D11SamplerState* mSampler = nullptr;
};

} // namespace PCEngine::Graphics