#include "Interceptor.h"
#include "UnitType.h"

#include <ImGui/Inc/imgui.h>

using namespace Steering;

Interceptor::Interceptor(AI::AIWorld& world)
	: Agent(world, UnitType::Interceptor)
{
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
}

void Steering::Interceptor::Load()
{
	
	// Load textures
	for (size_t i = 0; i < mTexturesIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "interceptor_%02zu.png", i + 1);
		mTexturesIds[i] = X::LoadTexture(name);
	}
	auto worldSize = world.GetSettings();
		
	// Initial settings
	mWidth = worldSize.worldSize.x;
	mHeight = worldSize.worldSize.y;

	//mSteeringModule->AddBehavior<AI::SeparationBehaviour>("Separation")->SetActive(true);
	//mSteeringModule->AddBehavior<AI::AlignmentBehaviour>("Separation")->SetActive(true);
	mSteeringModule->AddBehavior<AI::HideBehaviour>("Hide")->SetActive(true);
	mSteeringModule->AddBehavior<AI::CohesionBehaviour>("Cohesion")->SetActive(true);
	

	maxSpeed = 200.0f;
}

void Steering::Interceptor::Unload()
{
	mSteeringModule.reset();
}

void Steering::Interceptor::Update(float deltaTime)
{
	neighbors = world.GetNeighborhood({ position, 100.0f }, UnitType::Interceptor);
	std::remove_if(neighbors.begin(), neighbors.end(),
		[this](auto neighbor)
	{
		return this == neighbor;
	});

	auto force = mSteeringModule->Calculate();
	auto acceleration = (force / mass);
	velocity += acceleration * deltaTime;
	auto speed = X::Math::Magnitude(velocity);
	if (speed > maxSpeed)
	{
		position += velocity / speed * maxSpeed;
	}
	position += velocity * deltaTime;
	if (speed > 0.0f)
	{
		heading = X::Math::Normalize(velocity);
	}

	if (position.x < 0.0f)
	{
		position.x += mWidth;
	}
	if (position.x > mWidth)
	{
		position.x -= mWidth;
	}
	if (position.y < mHeight)
	{
		position.y += mHeight;
	}
	if (position.y > mHeight)
	{
		position.y -= mHeight;
	}

}

void Steering::Interceptor::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const size_t numFrames = mTexturesIds.size();
	size_t index = static_cast<size_t>(angle / X::Math::kTwoPi * numFrames);
	X::DrawSprite(mTexturesIds[index], position);
}
