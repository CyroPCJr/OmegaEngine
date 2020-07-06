#pragma once

#include "Goal.h"

namespace AI
{
	template <class AgentType>
	class GoalComposite : public Goal<AgentType>
	{
	public:
		using Status = Goal<AgentType>::Status;

		GoalComposite(AgentType& agent)
			: Goal<AgentType>(agent)
		{}

		virtual ~GoalComposite()
		{
			RemoveAllSubgoals();
		}

	protected:
		template <class GoalType, class = std::void_t<std::is_base_of<Goal<AgentType>, GoalType>>>
		void AddSubgoal()
		{
			mSubgoals.push_front(std::make_unique<GoalType>());
		}

		void RemoveAllSubgoals()
		{
			for (auto goal : mSubgoals)
				goal->Terminate();
			mSubgoals.clear();
		}

		Status ProcessSubgoals()
		{
			// Remove all completed goals
			while (!mSubgoals.empty())
			{
				auto goal = mSubgoals.front();
				if (goal->mStatus != Status::Completed && goal->mStatus != Status::Failed)
					break;

				goal->Terminate();
				mSubgoals.pop_front();
			}

			// If any Goals remain, continue to process
			if (!mSubgoals.empty())
			{
				Status status = mSubgoals.front()->Process();
				if (status == Status::Completed && mSubgoals.size() > 1)
					return Status::Active;
				else
					return status;
			}
			return Status::Completed;
		}

		std::list<std::unique_ptr<Goal<AgentType>>> mSubgoals;
	};
}