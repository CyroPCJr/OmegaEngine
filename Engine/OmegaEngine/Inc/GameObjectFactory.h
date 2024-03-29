#pragma once

#include "GameObject.h"

namespace Omega::GameObjectFactory
{
	GameObject* Create(GameObjectAllocator& allocator, const std::filesystem::path& templateFileName);
	void Destroy(GameObjectAllocator& allocator, GameObject* gameObject);
}