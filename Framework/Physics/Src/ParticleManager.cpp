#include "Precompiled.h"
#include "Particle.h"
#include "ParticleManager.h"
#include <Math/Inc/RandomHelper.h>

using namespace Omega::Physics;

ParticleManager::ParticleManager() noexcept(false)
{
	mVecConstraints.reserve(20u);
}

ParticleManager::~ParticleManager() noexcept(false)
{
	Clear();
}

std::vector<std::shared_ptr<Particle>> ParticleManager::GetAllParticles() const
{
	return mParticlesPool.GetAllObjects();
}

void ParticleManager::ShotSingleParticles()
{

	if (auto& tempPool = GetPoolParticle();
		tempPool.ObjectInUse() < tempPool.Size())
	{
		const auto& particle = tempPool.AcquireObject().lock();
		InitializeParticle(*particle, { 0.0f, 5.0f, 0.0f });
	}
}

void ParticleManager::ShotStickParticles()
{
	if (auto& pool = GetPoolParticle();
		pool.ObjectInUse() <= pool.Size() - 2u)
	{
		auto particle1 = pool.AcquireObject().lock();
		auto particle2 = pool.AcquireObject().lock();

		InitializeParticle(*particle1, { 0.5f, 5.0f, 0.0f });
		InitializeParticle(*particle2, { -0.5f, 5.0f, 0.0f });

		mVecConstraints.push_back(std::make_unique<Spring>(particle1.get(), particle2.get()));
	}
}

void ParticleManager::ShotTetrahedronParticles()
{
	if (auto& pool = GetPoolParticle();
		pool.ObjectInUse() <= pool.Size() - 4u)
	{
		auto particle1 = pool.AcquireObject().lock();
		auto particle2 = pool.AcquireObject().lock();
		auto particle3 = pool.AcquireObject().lock();
		auto particle4 = pool.AcquireObject().lock();

		InitializeParticle(*particle1, { -0.5f, 5.0f, 0.0f });
		InitializeParticle(*particle2, { 0.0f, 5.0f, 1.0f });
		InitializeParticle(*particle3, { 0.5f, 5.0f, 0.0f });
		InitializeParticle(*particle4, { 0.0f, 6.0f, 0.0f });

		mVecConstraints.push_back(std::make_unique<Spring>(particle1.get(), particle2.get()));
		mVecConstraints.push_back(std::make_unique<Spring>(particle2.get(), particle3.get()));
		mVecConstraints.push_back(std::make_unique<Spring>(particle3.get(), particle1.get()));

		mVecConstraints.push_back(std::make_unique<Spring>(particle1.get(), particle4.get()));
		mVecConstraints.push_back(std::make_unique<Spring>(particle2.get(), particle4.get()));
		mVecConstraints.push_back(std::make_unique<Spring>(particle3.get(), particle4.get()));
	}

}

void ParticleManager::BurstParticles()
{
	for (auto& particle : mParticlesPool.GetAllObjects())
	{
		InitializeParticle(*particle, { -0.5f, 5.0f, 0.0f });
	}

}

void ParticleManager::Clear() noexcept(false)
{
	mParticlesPool.ReleaseAllObjects();
	for (auto& c : mVecConstraints)
	{
		c.reset();
	}
	mVecConstraints.clear();
}

void ParticleManager::InitializeParticle(Particle& particle, const Omega::Math::Vector3& position)
{
	Omega::Math::RandomHelper randomHelper;
	particle.SetPosition(position);
	particle.SetVelocity({ randomHelper.RandomVector3({-0.05f, 0.1f, -0.05f},{0.05f, 0.5f, 0.05f}) });
	particle.radius = 0.1f;
	particle.bounce = 0.3f;
}
