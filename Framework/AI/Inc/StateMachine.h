#pragma once

#include "State.h"
#include <string>
#include <unordered_map>

namespace Omega::AI
{
	template<class AgentType>
	class StateMachine
	{
	public:
		using StateType = State<AgentType>;

		explicit StateMachine(const AgentType& agent) noexcept
			: mAgent(agent) 
		{}

		
		template<class NewStateType>
		void AddState(std::string_view name)
		{
			// SFINAE
			/*
				Substitution Failure Is Not An Error
			*/
			// type traits
			static_assert(std::is_base_of<StateType, NewStateType>::value, "[StateMachie] Can only add state for AgentType");
			auto [iter, success] =  mStates.emplace(std::move(name), std::make_unique<NewStateType>());
			if (success && !mCurrentState)
			{
				mCurrentState = iter->second.get();
			}
		}

		void Update(float deltaTime)
		{
			mCurrentState->Update(mAgent, deltaTime);
		}

		void ChangeState(std::string_view stateName)
		{
			auto iter = mStates.find(stateName);
			if (iter == mStates.end())
			{
				return;
			}

			mCurrentState->Exit(mAgent);
			mCurrentState = iter->second.get();
			mCurrentState->Enter(mAgent);
		}


	private:
		using StateMap = std::unordered_map<std::string_view, std::unique_ptr<StateType>>;

		AgentType& mAgent;
		StateType* mCurrentState = nullptr;
		StateMap mStates;
	};
}