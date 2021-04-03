#pragma once

#include <OmegaEngine/Inc/Omega.h>

namespace FSM
{
	class Cat
	{
	public:
		void Load();
		void UnLoad();

		void Update(float deltaTime);

		void Idle();
		void Walk();

		void SetMessageCat(const char* message) { mMessage = message; }
		const char* GetMessageCat() const { return mMessage.c_str(); }

	private:
		std::string mMessage;
		std::unique_ptr<AI::StateMachine<Cat>> mStateMachine;
	};

	class IdleState : public AI::State<Cat>
	{
	public:
		void Enter(Cat& agent) override;
		void Update(Cat& agent, float deltaTime) override;
		void Exit(Cat& agent) override;
	private:
		float currentTime = 0.0f;
	};

	class WalkState : public AI::State<Cat>
	{
	public:
		void Enter(Cat& agent) override;
		void Update(Cat& agent, float deltaTime) override;
		void Exit(Cat& agent) override;
	private:
		float currentTime = 0.0f;
	};

}