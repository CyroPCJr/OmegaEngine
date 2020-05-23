#include "Precompiled.h"
#include "PhysicsWorld.h"

using namespace Omega;
using namespace Omega::Physics;


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
	for (auto p : mParticles)
	{
		Graphics::SimpleDraw::AddSphere(p->radius, 4, 5, Graphics::Colors::BlueViolet);
	}
}

void PhysicsWorld::AddParticle(Particle* p)
{
	mParticles.push_back(p);
}

void PhysicsWorld::Clear()
{
	for (auto p : mParticles)
	{
		delete p;
	}
	mParticles.clear();
}

void PhysicsWorld::AccumulatedForces()
{
	for (auto p : mParticles)
	{
		p->acceleration = mSettings.gravity;
	}

}

void PhysicsWorld::Integrate()
{
	const float timeStepSqr = Math::Sqr(mSettings.timeStep);
	for (auto p : mParticles)
	{
		Math::Vector3 displacement = (p->position - p->lastPosition) + (p->acceleration * timeStepSqr);
		p->lastPosition = p->position;
		p->position += displacement;
	}
}

void PhysicsWorld::SatisfyConstraints()
{
	// TODO
}