#pragma once

namespace Omega::Graphics
{
	class ConstantBuffer
	{
	public:
		void Initialize(uint32_t size);
		void Terminate();
		void Bind() const;
		void Set(void* data);
	private:
		ID3D11Buffer* mConstantBuffer = nullptr;
	};
}