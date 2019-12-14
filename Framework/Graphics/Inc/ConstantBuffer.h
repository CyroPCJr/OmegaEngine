#pragma once

namespace Omega::Graphics
{
	class ConstantBuffer
	{
	public:
		void Initialize(UINT size);
		void Terminate();
		void Bind();
		void Set(void* data);
	private:
		ID3D11Buffer* mConstantBuffer = nullptr;
	};
}