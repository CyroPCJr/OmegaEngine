#include "Precompiled.h"
#include "ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include <ImGui\Inc\imgui.h>

using namespace Omega;
using namespace Omega::Graphics;

META_DERIVED_BEGIN(ColliderComponent, Component)
META_FIELD_BEGIN
META_FIELD(center, "Center")
META_FIELD(extend, "Extend")
META_FIELD_END
META_CLASS_END

void Omega::ColliderComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	SetAABB({ mTransformComponent->position + center, extend });
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
	auto aabb = Math::AABB({ mTransformComponent->position + center, extend });
	SimpleDraw::AddAABB(aabb, Colors::LightGreen);
}

const Math::AABB& ColliderComponent::GetAABB() const
{
	return mAABB;
}
