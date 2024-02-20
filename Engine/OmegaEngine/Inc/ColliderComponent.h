#pragma once

#include "Component.h"

namespace Omega
{
	class TransformComponent;

	class ColliderComponent final : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void EnableDebugUI(bool isActivated) noexcept { mIsDebugActivated = isActivated; }

		void SetAABB(const Math::AABB& aabb) { mAABB = aabb; }

		const Math::AABB& GetAABB() const;
		Math::OBB GetOBB() const;
		Math::Sphere GetSphere() const;

		Math::Vector3 center = Math::Vector3::Zero;
		Math::Vector3 extend = Math::Vector3::One;
	private:
		Math::AABB mAABB;
		const TransformComponent* mTransformComponent = nullptr;
		bool mIsDebugActivated = false;
		char mPadding[3]{};
	};
}