#include "Precompiled.h"
#include "Camera.h"
#include "GraphicsSystem.h"

using namespace Omega;
using namespace Omega::Graphics;


void Camera::SetPosition(const Math::Vector3& position)
{
	mPosition = position;
}
void Camera::SetDirection(const Math::Vector3& direction)
{
	mDirection = Math::Normalize(direction);
}

void Camera::SetLookAt(const Math::Vector3& target)
{
	mDirection = Math::Normalize(target - mPosition);
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}
void Camera::Strafe(float distance)
{
	const Math::Vector3 right = Math::Normalize(Math::Cross(Math::Vector3::YAxis, mDirection));
	mPosition += right * distance;
}

void Camera::Rise(float distance)
{
	// World wide screen
	mPosition += Math::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
	const Math::Matrix4 matRot = Math::Matrix4::RotationY(radian);
	mDirection = Math::TransformNormal(mDirection, matRot);
}

void Camera::Pitch(float radian)
{
	const Math::Vector3 right = Math::Normalize(Math::Cross(Math::Vector3::YAxis, mDirection));
	const Math::Matrix4 matRot = Math::Matrix4::RotationAxis(right, radian);
	const Math::Vector3 newLook = Math::TransformNormal(mDirection, matRot);

	// Check to prevent our newlook direction from being colinear with the Y axis
	const float dot = Math::Dot(newLook, Math::Vector3::YAxis);

	if (Math::Abs(dot) < 0.995f)
	{
		mDirection = newLook;
	}
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * Math::Constants::DegToRad;
	constexpr float kMaxFov = 170.0f * Math::Constants::DegToRad;
	mFov = Math::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

Math::Matrix4 Camera::GetViewMatrix() const
{
	const Math::Vector3 l = mDirection;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis, l));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));
	const float dx = -Math::Dot(r, mPosition);
	const float dy = -Math::Dot(u, mPosition);
	const float dz = -Math::Dot(l, mPosition);
	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		dx, dy, dz, 1.0f
	};
}

Math::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const auto width = GraphicsSystem::Get()->GetBackBufferWidth();
	const auto height = GraphicsSystem::Get()->GetBackBufferHeight();
	const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	const float h = 1.0f / tan(mFov*0.5f);
	const float w = h / aspectRatio;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float d = zf / (zf - zn);
	return
	{
		w,    0.0f, 0.0f,   0.0f,
		0.0f, h,    0.0f,   0.0f,
		0.0f, 0.0f, d,      1.0f,
		0.0f, 0.0f, -zn * d,0.0f
	};
}