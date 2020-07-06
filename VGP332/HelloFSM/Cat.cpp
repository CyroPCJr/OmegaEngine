#include "Cat.h"

using namespace FSM;

void Cat::Load()
{
	mStateMachine = std::make_unique <AI::StateMachine<Cat>>(*this);
	mStateMachine->AddState<IdleState>("Idle");
	mStateMachine->AddState<WalkState>("Walk");
}

void Cat::UnLoad()
{
	mStateMachine.reset();
}

void Cat::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::A))
	{
		mStateMachine->ChangeState("Idle");
	}

	if (X::IsKeyPressed(X::Keys::D))
	{
		mStateMachine->ChangeState("Walk");
	}
	mStateMachine->Update(deltaTime);
}

void Cat::Idle()
{
	SetMessageCat("[Cat] Idle State");
}

void Cat::Walk()
{
	SetMessageCat("[Cat] Walk State");
}


// ------------------ Idle State-------------------------- - //
void IdleState::Enter(Cat& agent)
{
	agent.Idle();
}

void IdleState::Update(Cat& agent, float deltaTime)
{
	X::DrawScreenText(agent.GetMessageCat(), 100.f, 100.f, 20.f, X::Colors::Blue);
	currentTime += deltaTime;
	std::string msg = "[Idle] time idle = " + std::to_string(currentTime);
	X::DrawScreenText(msg.c_str(), 100.0f, 120.0f, 25.f, X::Colors::Red);
}

void IdleState::Exit(Cat& agent)
{
	currentTime = 0.0f;
}


//------------------ Walk State --------------------------- //
void WalkState::Enter(Cat& agent)
{
	agent.Walk();
}

void WalkState::Update(Cat& agent, float deltaTime)
{
	X::DrawScreenText(agent.GetMessageCat(), 100.f, 100.f, 20.f, X::Colors::Blue);
	currentTime += deltaTime;
	std::string msg = "[Walk] time Walking = " + std::to_string(currentTime);
	X::DrawScreenText(msg.c_str(), 100.0f, 120.0f, 25.f, X::Colors::Red);
}

void WalkState::Exit(Cat& agent)
{
	currentTime = 0.0f;
}
