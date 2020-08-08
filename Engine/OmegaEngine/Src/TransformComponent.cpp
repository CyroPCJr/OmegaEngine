#include "Precompiled.h"
#include "TransformComponent.h"

#include <ImGui\Inc\imgui.h>

using namespace Omega;

void TransformComponent::Initialize()
{
}

void TransformComponent::Terminate()
{
}

void TransformComponent::Update(float deltaTime)
{
}

void TransformComponent::Render()
{
}

void TransformComponent::DebugUI()
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

void TransformComponent::SetPosition(const Math::Matrix4& transform)
{
	mPosition = GetTranslation(transform);

}

Math::Vector3 Omega::TransformComponent::Up(const Math::Matrix4& transform)
{
	return GetUp(transform);
}

Math::Vector3 Omega::TransformComponent::Right(const Math::Matrix4& transform)
{
	return GetRight(transform);
}
