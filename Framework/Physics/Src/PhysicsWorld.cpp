#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "Particle.h"

using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace Omega::Physics;
using namespace Omega::Core;

void PhysicsWorld::Initilize(const Settings& settings) noexcept(false)
{
	mSettings = settings;
}

void PhysicsWorld::Update(float deltaTime)
{
	mTimer += deltaTime;
	while (mTimer >= mSettings.timeStep)
	{
		mTimer -= mSettings.timeStep;

		Integrate();
		SatisfyConstraints();
	}
}

void PhysicsWorld::DebugDraw() const
{
	for (const auto& p : mParticleManager.GetAllParticles())
	{
		SimpleDraw::AddSphere(p->position, p->radius, 4, 5, Colors::Cyan);
	}

	for (const auto& c : mParticleManager.GetConstraints())
	{
		c->DebugDraw();
	}

	for (const auto& obb : mOBBs)
	{
		SimpleDraw::AddOBB(obb, Colors::Red);
	}
}

#pragma region For Enviroment

void PhysicsWorld::AddStaticPlane(const Math::Plane& plane)
{
	mPlanes.emplace_back(plane);
}

void PhysicsWorld::AddStaticPlane(std::initializer_list<Math::Plane> planes)
{
	mPlanes.insert(mPlanes.end(), planes);
}

void PhysicsWorld::AddStaticOBB(const Math::OBB& obb)
{
	mOBBs.emplace_back(obb);
}

void PhysicsWorld::AddStaticOBB(std::initializer_list<Math::OBB> obbs)
{
	mOBBs.insert(mOBBs.end(), obbs);
}

#pragma endregion

void PhysicsWorld::Clear(bool onlyDynamic) noexcept(false)
{
	mParticleManager.Clear();

	if (!onlyDynamic)
	{
		mPlanes.clear();
		mOBBs.clear();
	}
}

void PhysicsWorld::Integrate()
{
	const float timeStepSqr = Math::Sqr(mSettings.timeStep);
	for (auto& p : mParticleManager.GetAllParticles())
	{
		// Accumulate Forces
		p->acceleration = mSettings.gravity;
		const Math::Vector3 displacement = (p->position - p->lastPosition) + (p->acceleration * timeStepSqr);
		p->lastPosition = p->position;
		p->position += displacement;
	}
}

void PhysicsWorld::SatisfyConstraints()
{
	for (int n{ 0 }; n < mSettings.iterations; ++n)
	{
		for (const auto& c : mParticleManager.GetConstraints())
		{
			c->Apply();
		}
	}

	for (const auto& plane : mPlanes)
	{
		for (const auto& p : mParticleManager.GetAllParticles())
		{
			if ((Math::Dot(p->position, plane.n) <= plane.d &&
				Math::Dot(p->lastPosition, plane.n) > plane.d))
			{
				const auto velocity = p->position - p->lastPosition;
				const auto velocityPerpendicular = plane.n * Math::Dot(velocity, plane.n);
				const auto velocityParallel = velocity - velocityPerpendicular;
				const auto newVelocity = (velocityParallel * (1.0f - mSettings.drag)) - (velocityPerpendicular * p->bounce);
				p->SetPosition(p->position - velocityPerpendicular);
				p->SetVelocity(newVelocity);
			}
		
		}
	}

	for (const auto& obb : mOBBs)
	{
		for (const auto& p : mParticleManager.GetAllParticles())
		{
			if (IsContained(p->position, obb))
			{
				const auto velocity = p->position - p->lastPosition;
				const auto direction = Normalize(velocity);
				const Ray ray{ p->lastPosition, direction };
				Vector3 point, normal;
				GetContactPoint(ray, obb, point, normal);

				const auto velocityPerpendicular = normal * Math::Dot(velocity, normal);
				const auto velocityParallel = velocity - velocityPerpendicular;
				const auto newVelocity = (velocityParallel * (1.0f - mSettings.drag)) - (velocityPerpendicular * p->bounce);
				p->SetPosition(p->position - velocityPerpendicular);
				p->SetVelocity(newVelocity);
			}
		}
	}
}
