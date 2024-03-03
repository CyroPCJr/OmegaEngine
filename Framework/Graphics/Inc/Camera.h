#pragma once

namespace Omega::Graphics
{

	// This camera assumes Yaxis as up direction You cannot
	// look straight up nor straight down
	class Camera final
	{
	public:
		void SetPosition(const Math::Vector3& position);
		void SetDirection(const Math::Vector3& direction);
		void SetLookAt(const Math::Vector3& target);

		// 2 degrees of freedom for translation
		void Walk(float distance);
		void Strafe(float distance);
		void Rise(float distance);

		// 2 degrees of freedom for rotations
		void Yaw(float radian); // left and right
		void Pitch(float radian); // top and down

		void SetFov(float fov);
		void SetAspectRatio(float ratio);
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

		const Math::Vector3& GetPosition() const { return mPosition; }
		const Math::Vector3& GetDirection() const { return mDirection; }

		Math::Matrix4 GetViewMatrix() const;
		Math::Matrix4 GetOrthoGraphiMatrix(float width, float height) const;

		Math::Matrix4 GetPerspectiveMatrix() const;

	private:
		Math::Vector3 mPosition = Math::Vector3::Zero;
		Math::Vector3 mDirection = Math::Vector3::ZAxis;

		float mFov{ 60.0f * Math::Constants::DegToRad };
		float mAspectRatio{ 0.0f };
		float mNearPlane{ 1.0f };
		float mFarPlane{ 10000.0f };
	};
}