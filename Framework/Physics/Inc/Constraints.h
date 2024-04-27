#pragma once

namespace Omega::Physics
{

	struct Particle;

	class Constraint
	{
	public:
		Constraint() noexcept = default;
		virtual ~Constraint() noexcept = default;

		virtual void Apply() const = 0;
		virtual void DebugDraw() const{}
	};

	class Fixed final : public Constraint
	{
	public:
		explicit Fixed(Particle* p) noexcept;
		Fixed(Particle* p, const Math::Vector3& position) noexcept;

		void Apply() const noexcept override;
		void DebugDraw() const override;

		void SetPosition(const Math::Vector3& position) noexcept;

	private:
		Particle* mParticle;
		Math::Vector3 mPosition;
	};

	class Spring final : public Constraint
	{
	public:
		Spring(Particle* particleA, Particle* particleB, float restLength = 0.0f);

		void Apply() const override;
		void DebugDraw() const override;
	private:
		Particle* mParticleA;
		Particle* mParticleB;
		float mRestLength{ 0.0f };
	};
}