#pragma once

#include "Component.h"

namespace Omega
{
	class TransformComponent final : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void EnableDebugUI(bool isActivated) { mIsDebugActivated = isActivated; }

		Math::Matrix4 GetTransform() const;

		Math::Vector3 position = Math::Vector3::Zero;
		Math::Vector3 scale = Math::Vector3::Zero;
		Math::Quaternion rotation = Math::Quaternion::Zero;

		bool mIsDebugActivated = false;
	};

}
