#pragma once

#include "Colors.h"

namespace Omega::Graphics { class Camera; }

namespace Omega::Graphics::SimpleDraw
{
	void StaticInitialize(uint32_t maxVertexCount = 10000);
	void StaticTerminate();

	void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
	void AddFace(const Math::Vector3& v0, const  Math::Vector3& v1, const  Math::Vector3& v2, const Color& color);
	void AddDisplacement(float length);
	void AddBox(float length, const Color& color);
	void AddSphere(const Math::Vector3& position, float radius, int rings, int slices, const Color& color);
	void AddGroundPlane(float size, const Color& color = Colors::DarkGray);
	void AddBone(const Math::Vector3& position, const Math::Matrix4& transform);
	void AddTransform(const Math::Matrix4& transform);

	// TODO: need to be implemented
	void AddAABB(const Math::Vector3& center, const Math::Vector3& extend, const Color& color);
	void AddCone(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color);
	void AddCylinder(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color);



	void Render(const Camera& camera);
}