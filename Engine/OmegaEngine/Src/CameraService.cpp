#include "Precompiled.h"
#include "CameraService.h"

using namespace Omega;

META_DERIVED_BEGIN(CameraService, Service)
	META_NO_FIELD
META_CLASS_END

void CameraService::Initialize()
{
	mActiveCamera = AddCamera("Default");
}

Graphics::Camera* CameraService::AddCamera(std::string_view name)
{
	return &mCameraMap[name];
}

Graphics::Camera* CameraService::FindCamera(std::string_view name)
{
	auto iter = mCameraMap.find(name);
	return (iter == mCameraMap.end()) ? nullptr : &(iter->second);
}

void CameraService::SetActiveCamera(std::string_view name)
{
	if (auto camera = FindCamera(name); camera)
	{
		mActiveCamera = camera;
	}
}

Graphics::Camera& CameraService::GetActiveCamera()
{
	OMEGAASSERT(mActiveCamera, "[CameraService] --- No active camera.");
	return *mActiveCamera;
}

const Graphics::Camera& CameraService::GetActiveCamera() const
{
	OMEGAASSERT(mActiveCamera, "[CameraService] --- No active camera.");
	return *mActiveCamera;
}
