#pragma once
#include <Core/Inc/ObjectPool.h>
#include "ParticleManager.h"

namespace Omega::Physics
{

	class PhysicsWorld final
	{
	public:

		struct Settings
		{
			Math::Vector3 gravity{ 0.0f, -9.8f, 0.0f };
			float timeStep = 1.0f / 60.0f;
			float drag = 0.0f;
			int iterations = 1;
		};

		PhysicsWorld() noexcept = default;
		~PhysicsWorld() = default;

		PhysicsWorld(const PhysicsWorld&) = delete;
		PhysicsWorld(PhysicsWorld&&) = delete;
		PhysicsWorld& operator=(const PhysicsWorld&) = delete;
		PhysicsWorld& operator=(PhysicsWorld&&) = delete;

		void Initilize(const Settings& settings) noexcept(false);

		void Update(float deltaTime);
		void DebugDraw() const;

		// For simulation
		ParticleManager& GetParticleManager() noexcept { return mParticleManager; }

		// For enviroment
		void AddStaticPlane(const Math::Plane& plane);
		void AddStaticPlane(std::initializer_list<Math::Plane> planes);
		void AddStaticOBB(const Math::OBB& obb);
		void AddStaticOBB(std::initializer_list<Math::OBB> obbs);

		void Clear(bool onlyDynamic = false) noexcept(false);

	private:
		void Integrate();
		void SatisfyConstraints();

		ParticleManager mParticleManager;
		Settings mSettings;
		std::vector<Math::Plane> mPlanes;
		std::vector<Math::OBB> mOBBs;
		float mTimer = 0.0f;
	};

}