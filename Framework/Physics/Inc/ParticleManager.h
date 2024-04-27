#pragma once
#include "Constraints.h"
#include <Core/Inc/ObjectPool.h>

namespace Omega::Physics
{
	struct Particle;

	class ParticleManager
	{
	public:
		explicit ParticleManager() noexcept(false);
		~ParticleManager() noexcept(false);

		ParticleManager(const ParticleManager&) = delete;
		ParticleManager(ParticleManager&&) = delete;
		ParticleManager& operator=(const ParticleManager&) = delete;
		ParticleManager& operator=(ParticleManager&&) = delete;

		std::vector<std::shared_ptr<Particle>> GetAllParticles() const;
		Omega::Core::ObjectPool<Particle, 20u>& GetPoolParticle() noexcept { return mParticlesPool; }
		std::vector<std::unique_ptr<Constraint>>& GetConstraints() noexcept { return mVecConstraints; }
		const std::vector<std::unique_ptr<Constraint>>& GetConstraints() const noexcept { return mVecConstraints; }

		void ShotSingleParticles();
		void ShotStickParticles();
		void ShotTetrahedronParticles();
		void BurstParticles();
		void Clear() noexcept(false);

	private:
		void InitializeParticle(Particle& particle, const Omega::Math::Vector3& position);

		std::vector<std::unique_ptr<Constraint>> mVecConstraints;
		Omega::Core::ObjectPool<Particle, 20u> mParticlesPool;
	};

}