#include "Precompiled.h"
#include "GameObjectFactory.h"

#include "Component.h"

using namespace Omega;

GameObject* GameObjectFactory::Create(GameObjectAllocator& allocator, std::filesystem::path templateFileName)
{
	auto newObject = allocator.New();
	// TODO:
	// Contruct the game object based on the data in the template file
	if (templateFileName == "../Assets/Templates/player.json")
	{
		// TODO
		// Add TransformComponent class, add setters/getters, and a function to return a Matrix 4
		// Add ColliderComponent class, add setters/getters for an AABB, add Render to draw the aabb
		/*auto transform = newObject->AddComponent<TransformComponent>();
		transform->SetPosition({1.0f, 2.0f,3.0f});

		auto collider = newObject->AddComponent<ColliderComponent>();
		collider->SetAABB({ Math::Vector3::Zero, Math::Vector3::One });*/
	}
	return newObject;
}

void GameObjectFactory::Destroy(GameObjectAllocator& allocator, GameObject* gameObject)
{
	allocator.Delete(gameObject);
}