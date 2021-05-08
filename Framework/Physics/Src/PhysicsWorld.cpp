#include "Precompiled.h"
#include "PhysicsWorld.h"

using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace Omega::Physics;

//TODO: Olhar sobre Arena Allocator
//Reference: https://rosettacode.org/wiki/Arena_storage_pool#C.2B.2B

void PhysicsWorld::Initilize(const Settings& settings)
{
	mSettings = settings;
}

void PhysicsWorld::Update(float deltaTime)
{
	mTimer += deltaTime;
	while (mTimer >= mSettings.timeStep)
	{
		mTimer -= mSettings.timeStep;

		AccumulatedForces();
		Integrate();
		SatisfyConstraints();
	}
}

void PhysicsWorld::DebugDraw() const
{
	for (const auto& p : mParticles)
	{
		SimpleDraw::AddSphere(p->position, p->radius, 4, 5, Colors::Cyan);
	}

	for (const auto& c : mConstraints)
	{
		c->DebugDraw();
	}

	for (const auto& obb : mOBBs)
	{
		SimpleDraw::AddOBB(obb, Colors::Red);
	}
}

void PhysicsWorld::AddParticle(std::unique_ptr<Particle>& p)
{
	mParticles.push_back(std::move(p));
}

void PhysicsWorld::AddStaticOBB(const Math::OBB& obb)
{
	mOBBs.push_back(obb);
}

void PhysicsWorld::AddConstraint(std::unique_ptr<Constraint>& c)
{
	mConstraints.push_back(std::move(c));
}

void PhysicsWorld::AddStaticPlane(const Math::Plane& plane)
{
	mPlanes.push_back(plane);
}

void PhysicsWorld::Clear(bool onlyDynamic)
{
	/*for (auto p : mParticles)
	{
		delete p;
	}*/

	for (auto& p : mParticles)
	{
		p.reset();	
	}
	mParticles.clear();

	/*for (auto c : mConstraints)
	{
		delete c;
	}*/
	for (auto& c : mConstraints)
	{
		c.reset();
	}
	mConstraints.clear();

	if (!onlyDynamic)
	{
		mPlanes.clear();
		mOBBs.clear();
	}
}

void PhysicsWorld::AccumulatedForces()
{
	for (auto& p : mParticles)
	{
		p->acceleration = mSettings.gravity;
	}
}

void PhysicsWorld::Integrate()
{
	const float timeStepSqr = Math::Sqr(mSettings.timeStep);
	for (auto& p : mParticles)
	{
		Math::Vector3 displacement = (p->position - p->lastPosition) + (p->acceleration * timeStepSqr);
		p->lastPosition = p->position;
		p->position += displacement;
	}
}

void PhysicsWorld::SatisfyConstraints()
{
	for (int n = 0; n < mSettings.iterations; ++n)
	{
		for (const auto& c : mConstraints)
		{
			c->Apply();
		}
	}

	for (const auto& plane : mPlanes)
	{
		for (const auto& p : mParticles)
		{
			if (Math::Dot(p->position, plane.n) <= plane.d &&
				Math::Dot(p->lastPosition, plane.n) > plane.d)
			{
				auto velocity = p->position - p->lastPosition;
				auto velocityPerpendicular = plane.n * Math::Dot(velocity, plane.n);
				auto velocityParallel = velocity - velocityPerpendicular;
				auto newVelocity = (velocityParallel * (1.0f - mSettings.drag)) - (velocityPerpendicular * p->bounce);
				p->SetPosition(p->position - velocityPerpendicular);
				p->SetVelocity(newVelocity);
			}
		}
	}

	for (const auto& obb : mOBBs)
	{
		for (const auto& p : mParticles)
		{
			if (IsContained(p->position, obb))
			{
				auto velocity = p->position - p->lastPosition;
				auto direction = Normalize(velocity);
				Ray ray{ p->lastPosition, direction };
				Vector3 point, normal;
				GetContactPoint(ray, obb, point, normal);

				auto velocityPerpendicular = normal * Math::Dot(velocity, normal);
				auto velocityParallel = velocity - velocityPerpendicular;
				auto newVelocity = (velocityParallel * (1.0f - mSettings.drag)) - (velocityPerpendicular * p->bounce);
				p->SetPosition(p->position - velocityPerpendicular);
				p->SetVelocity(newVelocity);
			}
		}
	}
}