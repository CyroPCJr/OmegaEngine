#pragma once

#include "Component.h"

namespace Omega
{
	class ColliderComponent final: public Component
	{
	public:
		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void EnableDebugUI(bool isActivated) { mIsDebugActivated = isActivated; }

		void SetAABB(const Math::AABB& aabb) { mAABB = aabb; }
		const Math::AABB& GetAABB() const { return mAABB; }

	private:
		Math::AABB mAABB;
		bool mIsDebugActivated = false;
	};
}