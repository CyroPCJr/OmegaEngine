#include "Carrier.h"
#include "UnitTypes.h"

using namespace Omega::Graphics;
using namespace Omega::Math;
using namespace Omega::Input;
using namespace Omega::AI;

using namespace HelloPerception;

namespace
{
	float width = 0.0f;
	float height = 0.0f;
}

Carrier::Carrier(AIWorld& world)
	: Agent(world, UnitTypes::Carrier)
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
	// Carrier max speed
	maxSpeed = 200.0f;

	// Steerin Behaviours
	mSteeringModule->AddBehavior<SeekBehaviour>("Seek")->SetActive(true);
	mSteeringModule->AddBehavior<ArriveBehaviour>("Arrive")->SetActive(false);
	mSteeringModule->AddBehavior<ObstacleAvoidance>("AvoidanceObstacle")->SetActive(false);

	auto Calculator = [this](const Agent& agent, MemoryRecord& m)
	{
		float dist = 0.0f;
		for (size_t i = 0; i < m.properties.size(); ++i)
		{
			const Vector2 pos = std::get<Vector2>(m.properties["lastSeenPosition"]);
			dist += Distance(agent.position, pos);
		}
		if (m.importance == 0.0f)
		{
			m.importance = dist;
		}
		else
		{
			if (m.importance > dist)
			{
				m.importance -= dist;
			}
			else
			{
				m.importance += dist;
			}
		}
		return m.importance;
	};

	mPerceptionModule = std::make_unique<PerceptionModule>(*this, Calculator);
	mVisualSensor = mPerceptionModule->AddSensor<VisualSensor>("VisualSensor");
}

void Carrier::Unload()
{

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
	if (mDebugShowDraw)
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
	size_t index = static_cast<size_t>(angle / Constants::TwoPi * mTexturesIds.size());
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