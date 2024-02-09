#include "Carrier.h"
#include "UnitType.h"

using namespace Steering;
using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::Input;
using namespace Omega::AI;
namespace
{
	float width = 0.0f;
	float height = 0.0f;
}

Carrier::Carrier(AIWorld& world)
	: Agent(world, UnitType::Carrier)
{
	mSteeringModule = std::make_unique<SteeringModule>(*this);
}

void Carrier::Load()
{
	// Load images
	{
		const size_t total = mTexturesIds.size();
		for (size_t i = 0; i < total; ++i)
		{
			char name[128];
			sprintf_s(name, "Sprites/carrier_%02zu.png", i + 1u);
			mTexturesIds.at(i) = SpriteRendererManager::Get()->LoadTexture(name);
		}
	}
	
	// Initial settings
	const auto& worldSize = world.GetSettings();
	width = worldSize.worldSize.x;
	height = worldSize.worldSize.y;
	position = { width * 0.5f, height * 0.5f };
	maxSpeed = 200.0f;
	boundingRadius = 64.f;

	// Steerin Behaviours
	mSteeringModule->AddBehavior<SeekBehaviour>("Seek")->SetActive(false);
	mSteeringModule->AddBehavior<ArriveBehaviour>("Arrive");
	mSteeringModule->AddBehavior<ObstacleAvoidance>("AvoidanceObstacle");
	mSteeringModule->AddBehavior<WallAvoidanceBehaviour>("WallAvoidance"); 
	mSteeringModule->AddBehavior<PathFollowingBehaviour>("PathFollowing");
}

void Carrier::Unload() noexcept
{
	mTexturesIds = { 0 };
	mSteeringModule.reset();
}

void Carrier::Update(float deltaTime)
{
	/*destination = { static_cast<float>(InputSystem::Get()->GetMouseScreenX()),
				   static_cast<float>(InputSystem::Get()->GetMouseScreenY()) };*/

	const auto force = mSteeringModule->Calculate();
	const auto acceleration = (force / mass);
	velocity += acceleration * deltaTime;
	velocity = Truncate(velocity, maxSpeed);
	position += velocity * deltaTime;
	if (Magnitude(velocity) > 0.0f)
	{
		heading = Normalize(velocity);
	}

	world.WrapAround(position);
	
	// show debug draw
	if (isDebugShowDraw)
	{
		mSteeringModule->ShowDebugDraw();
		SimpleDraw::AddScreenCircle({ position , boundingRadius }, Colors::Aquamarine);
	}	
}

void Carrier::Render()
{
	const float angle = atan2(-heading.x, heading.y) + Constants::Pi;
	const size_t numFrames = mTexturesIds.size();
	const size_t index = static_cast<int>(angle / Constants::TwoPi * numFrames) % numFrames;
	SpriteRendererManager::Get()->DrawSprite(mTexturesIds.at(index), position);
}

void Carrier::SwitchBehaviour(const Behaviours& behaviours, bool active) const
{
	switch (behaviours)
	{
	case Carrier::Behaviours::Seek:
		mSteeringModule->GetBehavior<SeekBehaviour>("Seek")->SetActive(active);
		break;
	case Carrier::Behaviours::Arrive:
		if (const auto& behaviour = mSteeringModule->GetBehavior<ArriveBehaviour>("Arrive"))
		{
			behaviour->SetActive(active);
			behaviour->SetSlowRadius(Entity::radius);
		}
		break;
	case Carrier::Behaviours::ObstacleAvoidance:
		mSteeringModule->GetBehavior<ObstacleAvoidance>("AvoidanceObstacle")->SetActive(active);
		break;
	case Carrier::Behaviours::WallAvoidance:
		mSteeringModule->GetBehavior<ObstacleAvoidance>("WallAvoidance")->SetActive(active);
		break;
	case Carrier::Behaviours::PathFollowing:
		if (const auto& behaviour = mSteeringModule->GetBehavior<PathFollowingBehaviour>("PathFollowing"))
		{
			behaviour->SetActive(active);
			behaviour->SetPaths(world.GetPaths());
		}		
		break;
	default:
		mSteeringModule->GetBehavior<ArriveBehaviour>("Arrive")->SetActive(active);
		break;
	}

}