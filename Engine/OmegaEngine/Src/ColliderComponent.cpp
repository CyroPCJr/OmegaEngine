#include "Precompiled.h"
#include "ColliderComponent.h"

#include <ImGui\Inc\imgui.h>

using namespace Omega;
using namespace Omega::Graphics;

void ColliderComponent::Initialize()
{
}

void ColliderComponent::Terminate()
{
}

void ColliderComponent::Update(float deltaTime)
{
}

void ColliderComponent::Render()
{
	SimpleDraw::AddAABB(mAABB, Colors::Blue);
}

void ColliderComponent::DebugUI()
{
	if (mIsDebugActivated)
	{
		ImGui::Begin("Transform", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Position");
		ImGui::Text("Rotation");
		ImGui::Text("Scale");
		ImGui::End();
	}
}
