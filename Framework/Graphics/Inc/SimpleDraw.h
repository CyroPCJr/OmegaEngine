#pragma once

#include "Colors.h"

namespace Omega::Graphics { class Camera; }

namespace Omega::Graphics::SimpleDraw
{
	void StaticInitialize(uint32_t maxVertexCount = 100'000);
	void StaticTerminate();

#pragma region 3D Render

	void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
	void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color);
	void AddDisplacement(float length);
	void AddBox(float length, const Color& color);
	void AddSphere(const Math::Vector3& position, float radius, int rings, int slices, const Color& color);
	void AddGroundPlane(float size, const Color& color = Colors::DarkGray);
	void AddBone(const Math::Matrix4& transform, const Color& color, bool fill);
	void AddTransform(const Math::Matrix4& transform);
	void AddOBB(const Math::OBB& obb, const Color& color);
	void AddAABB(const Math::AABB& aabb, const Color& color);
	void AddCylinder(const Math::Vector3& base, const Math::Vector3& direction, float height, float radius, const Color& color, bool fill = false);
	void AddCone(float height, float radius, const Color& color, bool fill = false);
	void AddCone(const Math::Vector3& base, const Math::Vector3& direction, float height, float radius, const Color& color, bool fill = false);

#pragma endregion

#pragma region 2D Render

	void AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Color& color);
	void AddScreenLine(float x0, float y0, float x1, float y1, const Color& color);
	void AddScreenCircle(const Math::Circle& circle, const Color& color);
	void AddScreenCircle(const Math::Vector2& center, float radius, const Color& color);
	void AddScreenCircle(float centerX, float centerY, float radius, const Color& color);
	void AddScreenRect(const Math::Rect& rect, const Color& color);
	void AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Color& color);
	void AddScreenRect(float left, float top, float right, float bottom, const Color& color);
	void AddScreenArc(const Math::Vector2& center, float radius, float fromAngle, float toAngle, const Math::Vector4& color);
#pragma endregion


	void Render(const Camera& camera);
}