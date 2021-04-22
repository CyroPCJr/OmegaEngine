#include "Interceptor.h"
#include "UnitType.h"

using namespace Steering;
using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::AI;

namespace
{
	float width = 0.0f;
	float height = 0.0f;
}

Interceptor::Interceptor(AIWorld& world) noexcept
	: Agent(world, UnitType::Interceptor)
{
	mSteeringModule = std::make_unique<SteeringModule>(*this);
}

void Interceptor::Load()
{
	// Load images
	for (size_t i = 0; i < mTexturesIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "Sprites/interceptor_%02zu.png", i + 1);
		mTexturesIds[i] = SpriteRendererManager::Get()->LoadTexture(name);
	}
	// Initial settings
	auto worldSize = world.GetSettings();
	width = worldSize.worldSize.x;
	height = worldSize.worldSize.y;
	maxSpeed = 200.0f;

	// Group Behaviours
	mSteeringModule->AddBehavior<AI::AlignmentBehaviour>("Alignment");
	mSteeringModule->AddBehavior<AI::CohesionBehaviour>("Cohesion");
	mSteeringModule->AddBehavior<AI::SeparationBehaviour>("Separation");

	// Steerin Behaviours
	mSteeringModule->AddBehavior<AI::ArriveBehaviour>("Arrive");
	mSteeringModule->AddBehavior<AI::EvadeBehaviour>("Evade");
	mSteeringModule->AddBehavior<AI::FleeBehaviour>("Flee");
	mSteeringModule->AddBehavior<AI::HideBehaviour>("Hide");
	mSteeringModule->AddBehavior<AI::ObstacleAvoidance>("Avoidance");
	mSteeringModule->AddBehavior<AI::PursuitBehaviour>("Pursuit");
	mSteeringModule->AddBehavior<AI::WanderBehaviour>("Wandering");
	mSteeringModule->AddBehavior<AI::Interpose>("Interpose");

	// Initial steering 
	mSteeringModule->GetBehavior<AI::WanderBehaviour>("Wandering")->SetActive(true);
}

void Interceptor::Unload()
{
	mSteeringModule.reset();
}

void Interceptor::Update(float deltaTime)
{
	neighbors = world.GetNeighborhood({ position, 100.0f }, UnitType::Interceptor);
	// To avoid warning in compilation, I used [[maybe_unused]]. 
	// The reason that std::remove_if return type is flagged with [[no_discard]]
	[[maybe_unused]] auto notUsed = std::remove_if(neighbors.begin(), neighbors.end(),
		[this](auto neighbor)
	{
		return this == neighbor;
	});

	destination = threat->position;
	auto force = mSteeringModule->Calculate();
	auto acceleration = (force / mass);
	velocity += acceleration * deltaTime;
	velocity = Truncate(velocity, maxSpeed);
	position += velocity * deltaTime;
	if (Magnitude(velocity) > 0.0f)
	{
		heading = Normalize(velocity);
	}

	// show debug draw
	if (isDebugShowDraw)
	{
		mSteeringModule->ShowDebugDraw();
	}

	if (position.x < 0.0f) // left border
	{
		position.x += width;
	}
	if (position.x >= width) // right border
	{
		position.x -= width;
	}
	if (position.y < 0.0f) // botton border
	{
		position.y += height;
	}
	if (position.y >= height) // top border
	{
		position.y -= height;
	}
}

void Interceptor::Render()
{
	const float angle = atan2(-heading.x, heading.y) + Math::Constants::Pi;
	const size_t numFrames = mTexturesIds.size();
	size_t index = static_cast<size_t>(angle / Math::Constants::TwoPi * numFrames);
	SpriteRendererManager::Get()->DrawSprite(mTexturesIds[index], position);
}

void Interceptor::SwitchBehaviour(const Behaviours& behaviours, bool active) const
{
	switch (behaviours)
	{
	case Interceptor::Behaviours::Alignment:
		mSteeringModule->GetBehavior<AI::AlignmentBehaviour>("Alignment")->SetActive(active);
		break;
	case Interceptor::Behaviours::Cohesion:
		mSteeringModule->GetBehavior<AI::CohesionBehaviour>("Cohesion")->SetActive(active);
		break;
	case Interceptor::Behaviours::Separation:
		mSteeringModule->GetBehavior<AI::SeparationBehaviour>("Separation")->SetActive(active);
		break;
	case Interceptor::Behaviours::Evade:
		mSteeringModule->GetBehavior<AI::EvadeBehaviour>("Evade")->SetActive(active);
		break;
	case Interceptor::Behaviours::Flee:
		mSteeringModule->GetBehavior<AI::FleeBehaviour>("Cohesion")->SetActive(active);
		break;
	case Interceptor::Behaviours::Hide:
		mSteeringModule->GetBehavior<AI::HideBehaviour>("Hide")->SetActive(active);
		break;
	case Interceptor::Behaviours::ObstacleAvoidance:
		mSteeringModule->GetBehavior<AI::ObstacleAvoidance>("Avoidance")->SetActive(active);
		break;
	case Interceptor::Behaviours::Pursuit:
		mSteeringModule->GetBehavior<AI::PursuitBehaviour>("Pursuit")->SetActive(active);
		break;
	case Interceptor::Behaviours::Wandering:
		mSteeringModule->GetBehavior<AI::WanderBehaviour>("Wandering")->SetActive(active);
		break;
	case Interceptor::Behaviours::Interpose:
		mSteeringModule->GetBehavior<AI::Interpose>("Interpose")->SetActive(active);
		break;
	default:
		mSteeringModule->GetBehavior<AI::WanderBehaviour>("Wandering")->SetActive(active);
		break;
	}
}
