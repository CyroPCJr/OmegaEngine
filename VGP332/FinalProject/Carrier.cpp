#include "Carrier.h"
#include "UnitType.h"

#include <ImGui/Inc/imgui.h>

using namespace FinalProject;

Carrier::Carrier(AI::AIWorld& world)
	: Agent(world, UnitType::Carrier)
{
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
}

void Carrier::Load()
{
	// Load textures
	for (size_t i = 0; i < mTexturesIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "carrier_%02zu.png", i + 1);
		mTexturesIds[i] = X::LoadTexture(name);
	}

	// Initial settings
	auto worldSize = world.GetSettings();
	mWidth = worldSize.worldSize.x;
	mHeight = worldSize.worldSize.y;

	/*auto test = mSteeringModule->AddBehavior<AI::WanderBehaviour>("Wander");
	test->SetActive(true);
	AI::WanderBehaviour::Settings settings;
	settings.distance = 100.0f;
	settings.jitter = 20.0f;
	test->SetSettings(settings);*/
	mSteeringModule->AddBehavior<AI::SeekBehaviour>("Seek")->SetActive(true);
	
	//mSteeringModule->AddBehavior<AI::ObstacleAvoidance>("Avoidance")->SetActive(true);

	position = { mWidth * 0.5f, mHeight* 0.5f };

	maxSpeed = 200.0f;
}

void Carrier::Unload()
{
	mSteeringModule.reset();
}

void Carrier::Update(float deltaTime)
{
	destination = { static_cast<float>(X::GetMouseScreenX()),
				   static_cast<float>(X::GetMouseScreenY()) };

	auto force = mSteeringModule->Calculate();
	auto acceleration = (force / mass);
	velocity += acceleration * deltaTime;
	auto speed = X::Math::Magnitude(velocity);
	if (speed > maxSpeed)
	{
		position += (velocity / speed) * maxSpeed;
	}
	position += velocity * deltaTime;
	if (speed > 0.0f)
	{
		heading = X::Math::Normalize(velocity);
	}

	if (position.x < 0.0f) // left border
	{
		position.x += mWidth;
	}
	if (position.x > mWidth) // right border
	{
		position.x -= mWidth;
	}
	if (position.y < mHeight) // botton border
	{
		position.y += mHeight;
	}
	if (position.y > mHeight) // top border
	{
		position.y -= mHeight;
	}

	DebugUI();
}

void Carrier::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const size_t numFrames = mTexturesIds.size();
	size_t index = static_cast<size_t>(angle / X::Math::kTwoPi * numFrames);
	X::DrawSprite(mTexturesIds[index], position);
}

void Carrier::DebugUI()
{
	/*ImGui::Begin("Steering Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::RadioButton("Seek", &mActive, 0);
	ImGui::RadioButton("Flee", &mActive, 1);
	ImGui::RadioButton("Arrive", &mActive, 2);
	ImGui::Separator();
	if (ImGui::Button("Active Behaviours"))
	{
		mSeekType->SetActive((mActive == 0));
		mFleeType->SetActive((mActive == 1));
	}

	ImGui::End();*/
}


/*
static inline Vector3 Truncate(Vector3& v, float magnitude)
{
	v.Normalize();
	v *= magnitude;
	return v;
}

*/