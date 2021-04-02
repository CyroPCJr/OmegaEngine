#include "Cat.h"

using namespace FSM;
using namespace Omega::Input;
using namespace Omega::Graphics;

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
	auto input = InputSystem::Get();

	if (input->IsKeyDown(KeyCode::A))
	{
		mStateMachine->ChangeState("Idle");
	}

	if (input->IsKeyDown(KeyCode::D))
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
	SpriteRendererManager::Get()->DrawScreenText(agent.GetMessageCat(), 100.f, 100.f, 20.f, Colors::Blue);
	currentTime += deltaTime;
	std::string msg = "[Idle] time idle = " + std::to_string(currentTime);
	SpriteRendererManager::Get()->DrawScreenText(msg.c_str(), 100.0f, 120.0f, 25.f, Colors::Red);
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
	SpriteRendererManager::Get()->DrawScreenText(agent.GetMessageCat(), 100.f, 100.f, 20.f, Colors::Blue);
	currentTime += deltaTime;
	std::string msg = "[Walk] time Walking = " + std::to_string(currentTime);
	SpriteRendererManager::Get()->DrawScreenText(msg.c_str(), 100.0f, 120.0f, 25.f, Colors::Red);
}

void WalkState::Exit(Cat& agent)
{
	currentTime = 0.0f;
}
