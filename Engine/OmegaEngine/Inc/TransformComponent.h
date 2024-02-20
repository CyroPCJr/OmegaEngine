#pragma once

#include "Component.h"

namespace Omega
{
	class TransformComponent final : public Component
	{
	public:
		META_CLASS_DECLARE

			// TODO : Ver como eh q usa isso nos videos do Peter
			//SET_COMPONENT_ID(1)

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void EnableDebugUI(bool isActivated) noexcept { mIsDebugActivated = isActivated; }

		Math::Vector3 position = Math::Vector3::Zero;
		Math::Quaternion rotation = Math::Quaternion::Zero;
		Math::Vector3 scale = Math::Vector3::Zero;

	private:
		bool mIsDebugActivated = false;
		char mPadding[3]{};
	};

}
