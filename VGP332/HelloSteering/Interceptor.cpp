#include "Interceptor.h"
#include "UnitType.h"

#include <ImGui\Inc\imgui.h>

using namespace Steering;
using namespace Omega;
using namespace Omega::Graphics;
using namespace AI;

Interceptor::Interceptor(AIWorld& world)
	: Agent(world, UnitType::Interceptor)
{
	mSteeringModule = std::make_unique<SteeringModule>(*this);
}

void Interceptor::Load()
{
	// Load textures
	auto spriteRenderer = SpriteRendererManager::Get();
	for (size_t i = 0; i < mTexturesIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "Sprites/interceptor_%02zu.png", i + 1);
		mTexturesIds[i] = spriteRenderer->LoadTexture(name);
	}
	auto worldSize = world.GetSettings();

	// Initial settings
	mWidth = worldSize.worldSize.x;
	mHeight = worldSize.worldSize.y;

	mSteeringModule->AddBehavior<AI::PursuitBehaviour>("Pursuit")->SetActive(false);
	mSteeringModule->AddBehavior<AI::EvadeBehaviour>("Evade")->SetActive(false);
	mSteeringModule->AddBehavior<AI::AlignmentBehaviour>("Alignment")->SetActive(false);
	mSteeringModule->AddBehavior<AI::CohesionBehaviour>("Cohesion")->SetActive(false);
	mSteeringModule->AddBehavior<AI::SeparationBehaviour>("Separation")->SetActive(false);
	mSteeringModule->AddBehavior<AI::ObstacleAvoidance>("Avoidance")->SetActive(false);
	mSteeringModule->AddBehavior<AI::HideBehaviour>("Hide")->SetActive(false);
	mSteeringModule->AddBehavior<AI::WanderBehaviour>("Wandering")->SetActive(true);

	//mSteeringModule->AddBehavior<AI::SeparationBehaviour>("Separation")->SetActive(true);
	//mSteeringModule->AddBehavior<AI::AlignmentBehaviour>("Separation")->SetActive(true);
	/*mSteeringModule->AddBehavior<AI::HideBehaviour>("Hide")->SetActive(true);
	mSteeringModule->AddBehavior<AI::CohesionBehaviour>("Cohesion")->SetActive(true);*/


	maxSpeed = 200.0f;
}

void Interceptor::Unload()
{
	mSteeringModule.reset();
}

void Interceptor::Update(float deltaTime)
{
	neighbors = world.GetNeighborhood({ position, 100.0f }, UnitType::Interceptor);
	std::remove_if(neighbors.begin(), neighbors.end(),
		[this](auto neighbor)
	{
		return this == neighbor;
	});

	//destination = threat->position;
	auto force = mSteeringModule->Calculate();
	auto acceleration = (force / mass);
	velocity += acceleration * deltaTime;
	auto speed = Math::Magnitude(velocity);
	if (speed > maxSpeed)
	{
		velocity = velocity / speed * maxSpeed;
	}
	position += velocity * deltaTime;
	if (speed > 0.0f)
	{
		heading = Math::Normalize(velocity);
	}

	// show debug draw
	if (isDebugShowDraw)
	{
		mSteeringModule->ShowDebugDraw();
	}

	if (position.x < 0.0f) // left border
	{
		position.x += mWidth;
	}
	if (position.x >= mWidth) // right border
	{
		position.x -= mWidth;
	}
	if (position.y < 0.0f) // botton border
	{
		position.y += mHeight;
	}
	if (position.y >= mHeight) // top border
	{
		position.y -= mHeight;
	}
}

void Interceptor::Render()
{
	const float angle = atan2(-heading.x, heading.y) + Math::Constants::Pi;
	const size_t numFrames = mTexturesIds.size();
	size_t index = static_cast<size_t>(angle / Math::Constants::TwoPi * numFrames);
	SpriteRendererManager::Get()->DrawSprite(mTexturesIds[index], position);
}

void Interceptor::DebugUI()
{
	//TODO: Continuar daqui
	std::string asd = "ASD";
	const size_t size = sizeof(asd.length());
	std::array<bool, size> teste{};

}
