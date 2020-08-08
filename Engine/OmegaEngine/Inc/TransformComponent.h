#pragma once

#include "Component.h"

namespace Omega
{
	class TransformComponent final : public Component
	{
	public:
		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void EnableDebugUI(bool isActivated) { mIsDebugActivated = isActivated; }

		void SetPosition(const Math::Vector3& position) { mPosition = position; }
		const Math::Vector3& GetPosition() const { return mPosition; }

		void SetPosition(const Math::Matrix4& transform);

		void SetScale(const Math::Vector3& scale) { mScale = scale; }
		const Math::Vector3& GetScale() const { return mScale; }

		void SetRotation(const Math::Quaternion& rotation) { mRotation = rotation; }
		const Math::Quaternion& GetRotation() const { return mRotation; }

		Math::Vector3 Up(const Math::Matrix4& transform);
		Math::Vector3 Right(const Math::Matrix4& transform);

	private:
		Math::Vector3 mPosition;
		Math::Vector3 mScale;
		Math::Quaternion mRotation;

		bool mIsDebugActivated = false;
	};

}
