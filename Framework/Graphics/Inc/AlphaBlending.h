#pragma once

namespace Omega::Graphics {

	class AlphaBlending
	{
	public:
		void Initialize();
		void Terminate();

		void Bind() const;

	private:
		ID3D11BlendState* mAlphaBlending = nullptr;
	};

} // namespace Omega::Graphics