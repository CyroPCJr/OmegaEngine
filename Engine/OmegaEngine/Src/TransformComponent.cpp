#include "Precompiled.h"
#include "TransformComponent.h"

#include <ImGui\Inc\imgui.h>

using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;

META_DERIVED_BEGIN(TransformComponent, Component)
	META_FIELD_BEGIN
		META_FIELD(position, "Position")
		META_FIELD(rotation, "Rotation")
		META_FIELD(scale, "Scale")
	META_FIELD_END
META_CLASS_END

void Omega::TransformComponent::Initialize()
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
	/*if (mIsDebugActivated)
	{
		ImGui::Begin("Transform", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Position");
		ImGui::Text("Rotation");
		ImGui::Text("Scale");
		ImGui::End();
	}*/
	const Matrix4& m = Matrix4::Transform(position, rotation, scale);
	SimpleDraw::AddTransform(m);
}