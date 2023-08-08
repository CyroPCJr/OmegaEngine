#pragma once

namespace Omega::AI
{
	template <class AgentType>
	class Goal
	{
	public:
		enum class Status { Inactive, Active, Completed, Failed };

		Goal(const AgentType& agent) noexcept
			: mAgent(agent) 
		{}

		virtual ~Goal() = default;
		
		virtual Status Process() = 0;

	protected:
		virtual void Activate() = 0;
		virtual void Terminate() = 0;
		
		void ActivateIfInactive()
		{
			if (mStatus == Status::Inactive)
				Activate();
		}

		AgentType& mAgent;
		Status mStatus = Status::Inactive;
	};
}