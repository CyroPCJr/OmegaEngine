#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{
	class SteeringModule
	{
	public:
		explicit SteeringModule(Agent& agent);

		template <class BehaviorType>
		BehaviorType* AddBehavior(const std::string_view name)
		{
			auto[iter, success] = mBehaviors.try_emplace(std::move(name), std::make_unique<BehaviorType>());
			return success ? static_cast<BehaviorType*>(iter->second.get()) : nullptr;
		}

		template <class BehaviorType>
		BehaviorType* GetBehavior(const std::string_view name)
		{
			auto iter = mBehaviors.find(name);
			return iter != mBehaviors.end() ? static_cast<BehaviorType*>(iter->second.get()) : nullptr;
		}

		Omega::Math::Vector2 Calculate();
		void ShowDebugDraw() const;

	private:
		using BehaviorMap = std::unordered_map<std::string_view, std::unique_ptr<SteeringBehavior>>;

		Agent& mAgent;
		BehaviorMap mBehaviors;
	};
}