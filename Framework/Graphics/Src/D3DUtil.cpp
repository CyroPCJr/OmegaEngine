#include "Precompiled.h"
#include "D3DUtil.h"
#include "GraphicsSystem.h"

ID3D11Device* Omega::Graphics::GetDevice()
{
	// Video Memory Management
	if (auto device = GraphicsSystem::Get()) 
	{
		return device->get().mD3DDevice;
	}
	return nullptr;
}

ID3D11DeviceContext* Omega::Graphics::GetContext()
{
	// Context Pointer: issue draw commands
	if (auto device = GraphicsSystem::Get())
	{
		return device->get().mImmediateContext;
	}
	return nullptr;
}