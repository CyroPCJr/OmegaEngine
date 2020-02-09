#pragma once

namespace Omega::Graphics
{
	class BlendState
	{
	public:
		
		static void ClearState();

	public:

		enum class Mode
		{
			Opaque,
			AlphaBlending,
			AlphaPremultipled,
			Additive
		};

		BlendState() = default;
		~BlendState();

		BlendState(const BlendState&) = delete;
		BlendState& operator=(const BlendState&) = delete;

		void Initialize(Mode mode);
		void Terminate();

		void Bind() const;

	private:
		ID3D11BlendState* mBlendState = nullptr;
	};
}