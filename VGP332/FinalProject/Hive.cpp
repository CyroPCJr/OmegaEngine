#include <XEngine.h>
#include "Hive.h"

using namespace FinalProject;

void Hive::Initialize(AI::AIWorld& world)
{
	position = { static_cast<float>(X::GetScreenWidth()), static_cast<float>(X::GetScreenHeight()) };

	for (size_t i = 0; i < maxInterceptor; ++i)
	{
		auto interceptor = mInterceptorList.emplace_back(std::make_unique<Interceptor>(world)).get();
		interceptor->Load();
		interceptor->position = { position.x * 0.5f , position.y * 0.5f };//{ X::RandomFloat(0, mSettings.worldSize.x), X::RandomFloat(0, mSettings.worldSize.y) };
	}
}

void Hive::Terminate()
{
	for (const auto& inter : mInterceptorList)
	{
		inter->Unload();
	}
}

void Hive::Update(float deltaTime)
{
	for (const auto& inter : mInterceptorList)
	{
		inter->Update(deltaTime);
		inter->Render();
	}
}

void Hive::Render()
{
	X::DrawScreenCircle({ position.x * 0.5f , position.y * 0.5f }, 50.0f, X::Colors::Red);
}