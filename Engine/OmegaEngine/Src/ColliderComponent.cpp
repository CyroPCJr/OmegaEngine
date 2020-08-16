#include "Precompiled.h"
#include "ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include <ImGui\Inc\imgui.h>

using namespace Omega;
using namespace Omega::Graphics;

void ColliderComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void ColliderComponent::Terminate()
{
}

void ColliderComponent::Update(float deltaTime)
{
}

void ColliderComponent::Render()
{
	//SimpleDraw::AddAABB(mAABB, Colors::Blue);
}

void ColliderComponent::DebugUI()
{
	/*if (mIsDebugActivated)
	{
		ImGui::Begin("Transform", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Position");
		ImGui::Text("Rotation");
		ImGui::Text("Scale");
		ImGui::End();
	}*/
	auto aabb = GetAABB();
	SimpleDraw::AddAABB(aabb, Colors::LightGreen);
}

Math::AABB ColliderComponent::GetAABB() const
{
	auto translation = mTransformComponent->position;
	// this is incorrect if we have orientation as well
	return { translation + center, extend };
}
