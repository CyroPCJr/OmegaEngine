#pragma once

#include "Service.h"

namespace Omega
{

	class CameraService final: public Service
	{
	public:
		META_CLASS_DECLARE;

		void Initialize() override;

		Graphics::Camera* AddCamera(std::string_view name);
		Graphics::Camera* FindCamera(std::string_view name);

		void SetActiveCamera(std::string_view name);

		Graphics::Camera& GetActiveCamera();
		const Graphics::Camera& GetActiveCamera() const;

	private:
		using CameraMap = std::map<std::string_view, Graphics::Camera>;
		CameraMap mCameraMap;
		Graphics::Camera* mActiveCamera = nullptr;
	};
}