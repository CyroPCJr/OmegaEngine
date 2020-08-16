#include "Precompiled.h"
#include "GameObject.h"

#include "Component.h"

using namespace Omega;

void GameObject::Initialize()
{
	OMEGAASSERT(!mInitialized, "[GameObject] -- Game object already initialized!");
	for (auto& component : mComponents)
	{
		component->Initialize();
	}
	mInitialized = true;
}

void GameObject::Terminate()
{
	for (auto& component : mComponents)
	{
		component->Terminate();
	}
}

void GameObject::Update(float deltaTime) 
{
	for (auto& component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void GameObject::Render() 
{
	for (auto& component : mComponents)
	{
		component->Render();
	}
}

void GameObject::DebugUI() 
{
	for (auto& component : mComponents)
	{
		component->DebugUI();
	}
}