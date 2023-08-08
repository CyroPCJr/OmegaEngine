#pragma once

namespace Omega::AI
{
	class AIWorld;
	class Entity;

	using EntitieList = std::vector<Entity*>;

	class Entity
	{
	public:
		Entity(AIWorld& world, uint32_t typeId) noexcept;
		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&&) = delete;

		Omega::Math::Matrix3 LocalToWorld() const;

		uint32_t GetTypeId() const { return mUniqueId >> 32u; }
		uint64_t GetUniqueId() const { return mUniqueId; }

		AIWorld& world;
		Omega::Math::Vector2 position = Omega::Math::Vector2::Zero;
		Omega::Math::Vector2 heading = Omega::Math::Vector2::YAxis;
		float radius = 1.0f;

	private:
		const uint64_t mUniqueId = 0u;
	};

}