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

		void AddParticle(Particle* p);
		void AddConstraint(Constraint* c);
		void AddPlane(const Math::Plane& plane);

		void Clear(bool onlyDynamic = false);
	private:

		void AccumulatedForces();
		void Integrate();
		void SatisfyConstraints();

		//TODO: change to unique_ptr
		//TODO create pooling system to save memory
		std::vector<Particle*> mParticles;
		std::vector<Constraint*> mConstraints;
		std::vector<Math::Plane> mPlanes;

		Settings mSettings;
		float mTimer = 0.0f;
	};

}