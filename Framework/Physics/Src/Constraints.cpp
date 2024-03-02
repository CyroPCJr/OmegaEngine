#include "Precompiled.h"
#include "Constraints.h"

#include "Particle.h"

using namespace Omega;
using namespace Omega::Physics;
using namespace Omega::Graphics;

#pragma region Fixed Constraint

Fixed::Fixed(Particle* p) noexcept
	: Fixed(p, p->position)
{}

Fixed::Fixed(Particle* p, const Math::Vector3& position) noexcept
	: mParticle(p)
	, mPosition(position)
{}

void Fixed::Apply() const noexcept
{
	mParticle->SetPosition(mPosition);
}

void Fixed::DebugDraw() const
{
	SimpleDraw::AddAABB({ mPosition, mParticle->radius }, Colors::Cyan);
}

void Fixed::SetPosition(const Math::Vector3& position) noexcept
{
	mPosition = position;
}

#pragma endregion

#pragma region Spring Contraint

Spring::Spring(Particle* particleA, Particle* particleB, float restLength)
	:mParticleA(particleA)
	, mParticleB(particleB)
	, mRestLength(restLength)
{
	if (restLength <= 0.0f)
	{
		mRestLength = Math::Magnitude(particleA->position - particleB->position);
	}
}

void Spring::Apply() const
{
	const Math::Vector3 delta = mParticleB->position - mParticleA->position;
	const float dist = Math::Magnitude(delta);
	const float diff = (dist - mRestLength) / (dist * (mParticleA->invMass + mParticleB->invMass));
	mParticleA->position += delta * diff * mParticleA->invMass;
	mParticleB->position -= delta * diff * mParticleB->invMass;
}

void Spring::DebugDraw() const
{
	SimpleDraw::AddLine(mParticleA->position, mParticleB->position, Colors::Green);
}

#pragma endregion