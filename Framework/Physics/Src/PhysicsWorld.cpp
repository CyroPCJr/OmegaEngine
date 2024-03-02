#include "Precompiled.h"
#include "PhysicsWorld.h"

using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace Omega::Physics;

//TODO: Olhar sobre Arena Allocator
//Reference: https://rosettacode.org/wiki/Arena_storage_pool#C.2B.2B

void PhysicsWorld::Initilize(const Settings& settings) noexcept
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

void PhysicsWorld::InitializeParticles(size_t numParticles)
{
	Clear(true);
	mParticles.reserve(numParticles);
	const size_t total = mParticles.capacity();
	for (size_t i{ 0 }; i < total; ++i)
	{
		auto particles = std::make_unique<Particle>();
		AddParticle(particles);
	}
}

void PhysicsWorld::AddParticle(const Particle& particle)
{
	mParticles.push_back(std::make_unique<Particle>(particle));
}

void PhysicsWorld::AddParticle(std::unique_ptr<Particle>& particle)
{
	mParticles.push_back(std::move(particle));
}

void PhysicsWorld::AddParticle(std::initializer_list<const Particle> listParticles)
{
	for (const auto& p : listParticles)
	{
		AddParticle(p);
	}
}

void PhysicsWorld::AddStaticOBB(const Math::OBB& obb)
{
	mOBBs.emplace_back(obb);
}

void PhysicsWorld::AddSpring(Particle& particle1, Particle& particle2)
{

	std::unique_ptr<Constraint> spring = std::make_unique<Spring>(&particle1, &particle1);
	mConstraints.push_back(std::move(spring));
}

void PhysicsWorld::AddSpring(std::unique_ptr<Constraint>& c)
{
	mConstraints.push_back(std::move(c));
}

void PhysicsWorld::AddConstraint(std::unique_ptr<Constraint>& c)
{
	mConstraints.push_back(std::move(c));
}

void PhysicsWorld::AddStaticPlane(const Math::Plane& plane)
{
	mPlanes.emplace_back(plane);
}

void PhysicsWorld::AddStaticPlane(std::initializer_list<Math::Plane> planes)
{
	mPlanes.insert(mPlanes.end(), planes);
}

void PhysicsWorld::Clear(bool onlyDynamic) noexcept
{
	for (auto& p : mParticles)
	{
		p.reset();
	}
	mParticles.clear();

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

void PhysicsWorld::Integrate()
{
	const float timeStepSqr = Math::Sqr(mSettings.timeStep);
	for (auto& p : mParticles)
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
		for (const auto& p : mParticles)
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