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

Carrier::Carrier(AIWorld& world) noexcept
	: Agent(world, UnitType::Carrier)
{
	mSteeringModule = std::make_unique<SteeringModule>(*this);
}

void Carrier::Load()
{
	// Load images
	for (size_t i = 0; i < mTexturesIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "Sprites/carrier_%02zu.png", i + 1);
		mTexturesIds[i] = SpriteRendererManager::Get()->LoadTexture(name);
	}

	// Initial settings
	auto worldSize = world.GetSettings();
	width = worldSize.worldSize.x;
	height = worldSize.worldSize.y;
	position = { width * 0.5f, height * 0.5f };
	maxSpeed = 200.0f;

	// Steerin Behaviours
	mSteeringModule->AddBehavior<SeekBehaviour>("Seek")->SetActive(true);
	mSteeringModule->AddBehavior<ArriveBehaviour>("Arrive")->SetActive(false);
	mSteeringModule->AddBehavior<ObstacleAvoidance>("AvoidanceObstacle")->SetActive(false);
}

void Carrier::Unload()
{
	mTexturesIds = { 0 };
	mSteeringModule.reset();
}

void Carrier::Update(float deltaTime)
{
	destination = { static_cast<float>(InputSystem::Get()->GetMouseScreenX()),
				   static_cast<float>(InputSystem::Get()->GetMouseScreenY()) };

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

void Carrier::Render()
{
	const float angle = atan2(-heading.x, heading.y) + Constants::Pi;
	const size_t numFrames = mTexturesIds.size();
	size_t index = static_cast<size_t>(angle / Constants::TwoPi * numFrames);
	SpriteRendererManager::Get()->DrawSprite(mTexturesIds[index], position);
}

void Carrier::SwitchBehaviour(const Behaviours& behaviours, bool active) const
{
	switch (behaviours)
	{
	case Carrier::Behaviours::Seek:
		mSteeringModule->GetBehavior<SeekBehaviour>("Seek")->SetActive(active);
		break;
	case Carrier::Behaviours::Arrive:
		mSteeringModule->GetBehavior<ArriveBehaviour>("Arrive")->SetActive(active);
		mSteeringModule->GetBehavior<ArriveBehaviour>("Arrive")->SetSlowRadius(mSlowRadius);
		break;
	case Carrier::Behaviours::ObstacleAvoidance:
		mSteeringModule->GetBehavior<ObstacleAvoidance>("AvoidanceObstacle")->SetActive(active);
		break;
	default:
		mSteeringModule->GetBehavior<ArriveBehaviour>("Arrive")->SetActive(active);
		break;
	}

}