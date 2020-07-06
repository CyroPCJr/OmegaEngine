#pragma once

#include "Goal.h"
#include "GoalComposite.h"
#include "Strategy.h"

namespace AI
{
	template <class AgentType>
	class DecisionModule
	{
	public:
		using GoalType = Goal<AgentType>;
		using StrategyType = Strategy<AgentType>;

		DecisionModule(AgentType& agent)
			: mAgent(agent)
		{}

		template <class NewStrategyType, class = std::void_t<std::is_base_of<StrategyType, NewStrategyType>>>
		void AddStrategy()
		{
			mStrategies.push_back(std::make_unique<NewStrategyType>);
		}

		void Update()
		{
			// Evaluate our priorities
			Arbitrate();

			// Update the current action
			if (mCurrentGoal)
				mCurrentGoal->Process();
		}

	private:
		void Arbitrate()
		{
			StrategyType* bestStrategy = nullptr;
			float mostDesirable = 0.0f;

			// Find the most desirable strategy
			for (auto strategy : mStrategies)
			{
				float desirability = strategy->CalculateDesirability();
				if (desirability > mostDesirable)
				{
					mostDesirable = desirability;
					bestStrategy = strategy;
				}
			}

			// Check if our strategy has changed
			if (mCurrentStrategy != bestStrategy)
			{
				// Set new strategy
				mCurrentStrategy = bestStrategy;

				// Exit the current goal
				if (mCurrentGoal)
					mCurrentGoal->Terminate();

				// Set new goal
				if (mCurrentStrategy)
					mCurrentGoal = mCurrentStrategy->CreateGoal();
			}
		}

		AgentType& mAgent;
		std::vector<std::unique_ptr<StrategyType>> mStrategies;
		StrategyType* mCurrentStrategy = nullptr;
		std::unique_ptr<GoalType> mCurrentGoal = nullptr;
	};
}