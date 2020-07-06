#pragma once

#include "State.h"
#include <string>
#include <unordered_map>

namespace AI
{
	template<class AgentType>
	class StateMachine
	{
	public:
		using StateType = State<AgentType>;

		explicit StateMachine(AgentType& agent) 
			: mAgent(agent) 
		{}

		
		template<class NewStateType>
		void AddState(std::string name)
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

		void ChangeState(std::string stateName)
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
		using StateMap = std::unordered_map<std::string, std::unique_ptr<StateType>>;

		AgentType& mAgent;
		StateType* mCurrentState = nullptr;
		StateMap mStates;
	};
}