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

		void EnableDebugUI(bool isActivated) { mIsDebugActivated = isActivated; }

		void SetAABB(const Math::AABB& aabb) { mAABB = aabb; }

		Math::AABB GetAABB() const;
		Math::OBB GetOBB() const;
		Math::Sphere GetSphere() const;


		Math::Vector3 extend = Math::Vector3::One;
		Math::Vector3 center = Math::Vector3::Zero;
		Math::AABB mAABB;
	private:
		const TransformComponent* mTransformComponent = nullptr;
		bool mIsDebugActivated = false;
	};
}