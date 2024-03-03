#include "Precompiled.h"
#include "D3DUtil.h"

#include "GraphicsSystem.h"

ID3D11Device* Omega::Graphics::GetDevice()
{
	// Video Memory Management
	return GraphicsSystem::Get()->get().mD3DDevice;
}

ID3D11DeviceContext* Omega::Graphics::GetContext()
{
	// Context Pointer: issue draw commands
	return GraphicsSystem::Get()->get().mImmediateContext;
}