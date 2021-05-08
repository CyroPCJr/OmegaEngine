#pragma once
#include "Particle.h"
#include "Constraints.h"

namespace Omega::Physics
{

	class PhysicsWorld
	{
	public:

		struct Settings
		{
			Math::Vector3 gravity{ 0.0f, -9.8f, 0.0f };
			float timeStep = 1.0f / 60.0f;
			float drag = 0.0f;
			int iterations = 1;
		};

		void Initilize(const Settings& settings);

		void Update(float deltaTime);
		void DebugDraw() const;

		// For simulation
		void AddParticle(std::unique_ptr<Particle>& p);
		void AddConstraint(std::unique_ptr<Constraint>& c);

		// For enviroment
		void AddStaticPlane(const Math::Plane& plane);
		void AddStaticOBB(const Math::OBB& obb);

		void Clear(bool onlyDynamic = false);

		inline auto& GetParticles() const { return mParticles; }
	private:

		void AccumulatedForces();
		void Integrate();
		void SatisfyConstraints();

		//TODO: change to unique_ptr
		//TODO: create pooling system to save memory
		//possible references: 
		// https://stackoverflow.com/questions/27827923/c-object-pool-that-provides-items-as-smart-pointers-that-are-returned-to-pool
		// https://sourcemaking.com/design_patterns/object_pool/cpp/1
		// https://gameprogrammingpatterns.com/object-pool.html

		std::vector<std::unique_ptr<Particle>> mParticles;
		std::vector<std::unique_ptr<Constraint>> mConstraints; 
		std::vector<Math::Plane> mPlanes;
		std::vector<Math::OBB> mOBBs;

		Settings mSettings;
		float mTimer = 0.0f;
	};

}