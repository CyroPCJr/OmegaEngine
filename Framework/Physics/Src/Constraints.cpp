#include "Precompiled.h"
#include "Constraints.h"

using namespace Omega;
using namespace Omega::Physics;

#pragma region Fixed Constraint

Fixed::Fixed(Particle* p)
	: Fixed(p, p->position)
{}

Fixed::Fixed(Particle* p, const Math::Vector3& position)
	: mParticle(p)
	, mPosition(position)
{}

void Fixed::Apply() const
{
	mParticle->SetPosition(mPosition);
}

void Fixed::DebugDraw() const
{
	Graphics::SimpleDraw::AddAABB({ mPosition, mParticle->radius }, Graphics::Colors::Cyan);
}

void Fixed::SetPosition(const Math::Vector3& position)
{
	mPosition = position;
}

#pragma endregion

#pragma region Spring Contraint

Spring::Spring(Particle* a, Particle* b, float restLength)
	:mParticleA(a)
	, mParticleB(b)
	, mRestLength(restLength)
{
	if (restLength <= 0.0f)
	{
		mRestLength = Math::Magnitude(a->position - b->position);
	}
}

void Spring::Apply() const
{
	Math::Vector3 delta = mParticleB->position - mParticleA->position;
	float dist = Math::Magnitude(delta);
	float diff = (dist - mRestLength) / (dist * (mParticleA->invMass + mParticleB->invMass));
	mParticleA->position += delta * diff * mParticleA->invMass;
	mParticleB->position -= delta * diff * mParticleB->invMass;
}

void Spring::DebugDraw() const
{
	Graphics::SimpleDraw::AddLine(mParticleA->position, mParticleB->position, Graphics::Colors::Green);
}

#pragma endregion

// For Homework:
// Add the following:
// - Tetrahedrons!
// - Cubes! (how many constraints do you need?)
// - Balls and chains
// - Cloth
// - And if you are up for the challenge, build a figure (may more constraints)
// - Build whatever you want