#include "Precompiled.h"
#include "Entity.h"

#include "AIWorld.h"

using namespace Omega::AI;
using namespace Omega::Math;

Entity::Entity(AIWorld & world, uint32_t typeId) noexcept
	: world(world)
	, mUniqueId((static_cast<uint64_t>(typeId) << 32u) | world.GetNextId())
{
	world.RegisterEntity(this);
}

Entity::~Entity()
{
	world.UnRegisterEntity(this);
}

Matrix3 Entity::LocalToWorld() const
{
	auto f = Normalize(heading);
	auto s = PerpendicularRH(f);
	auto p = position;
	return
	{
		s.x, s.y, 0.0f,
		f.x, f.y, 0.0f,
		p.x, p.y, 1.0f
	};
}