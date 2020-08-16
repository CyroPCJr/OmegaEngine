#include "Precompiled.h"
#include "GameObjectFactory.h"

#include "Component.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

using namespace Omega;

GameObject* GameObjectFactory::Create(GameObjectAllocator& allocator, std::filesystem::path templateFileName)
{
	using namespace rapidjson;

	auto newObject = allocator.New();

	FILE* file = nullptr;
	fopen_s(&file, templateFileName.u8string().c_str(), "r");

	char readBuffer[16384];
	FileReadStream is(file, readBuffer, sizeof(readBuffer));

	Document document;
	document.ParseStream(is);

	if (document.HasMember("GameObject"))
	{
		auto obj = document["GameObject"].GetObjectW();
		if (obj.HasMember("Components"))
		{
			auto comp = obj["Components"].GetObjectW();
			if (comp.HasMember("TransformComponent"))
			{
				float position[3]{ 0 };
				auto transformComponent = comp["TransformComponent"].GetObjectW();
				OMEGAASSERT(transformComponent.HasMember("Position"), "[RapidJSON] -- Position.");
				const Value& jsonPos = transformComponent["Position"];
				int i = 0;
				for (Value::ConstMemberIterator iter = jsonPos.MemberBegin();
					iter != jsonPos.MemberEnd(); ++iter)
				{
					position[i] = iter->value.GetFloat();
					i++;
				}
				auto transform = newObject->AddComponent<TransformComponent>();
				transform->position = Math::Vector3{ position[0], position[1], position[2] };
			}

			if (comp.HasMember("ColliderComponent"))
			{
				float position[3]{ 0 };
				// Center
				auto colliderComponentJson = comp["ColliderComponent"].GetObjectW();
				OMEGAASSERT(colliderComponentJson.HasMember("Center"), "[RapidJSON] -- Center.");
				Value& valueJson = colliderComponentJson["Center"];
				int i = 0;
				for (Value::ConstMemberIterator iter = valueJson.MemberBegin();
					iter != valueJson.MemberEnd(); ++iter)
				{
					position[i] = iter->value.GetFloat();
					i++;
				}
				auto collider = newObject->AddComponent<ColliderComponent>();
				collider->center = { position[0], position[1], position[2] };
				// Extend
				colliderComponentJson = comp["ColliderComponent"].GetObjectW();
				OMEGAASSERT(colliderComponentJson.HasMember("Extend"), "[RapidJSON] -- Extend.");
				valueJson = colliderComponentJson["Extend"];
				i = 0;
				for (Value::ConstMemberIterator iter = valueJson.MemberBegin();
					iter != valueJson.MemberEnd(); ++iter)
				{
					position[i] = iter->value.GetFloat();
					i++;
				}
				collider->extend = { position[0], position[1], position[2] };
			}
		}
	}

	// TODO:
	// Contruct the game object based on the data in the template file
	// read a json file
	// add component as described in the file
	// initialize component with values from the file

	//if (templateFileName == "tallBox")
	//{
	//	// TODO
	//	// Add TransformComponent class, add setters/getters, and a function to return a Matrix 4
	//	// Add ColliderComponent class, add setters/getters for an AABB, add Render to draw the aabb
	//	auto transform = newObject->AddComponent<TransformComponent>();
	//	transform->position = Math::Vector3{ -5.0f, 0.0f, 0.0f };

	//	auto collider = newObject->AddComponent<ColliderComponent>();
	//	collider->center = { 0.0f, 3.0f, 0.0f };
	//	collider->extend = { 1.0f, 3.0f, 1.0f };
	//}
	//else if (templateFileName == "longBox")
	//{
	//	auto transform = newObject->AddComponent<TransformComponent>();
	//	transform->position = Math::Vector3{ 0.0f, 0.0f, 0.0f };

	//	auto collider = newObject->AddComponent<ColliderComponent>();
	//	collider->center = { 0.0f, 1.0f, 0.0f };
	//	collider->extend = { 1.0f, 1.0f, 4.0f };
	//}
	//else if (templateFileName == "fatBox")
	//{
	//	auto transform = newObject->AddComponent<TransformComponent>();
	//	transform->position = Math::Vector3{ 5.0f, 0.0f, 0.0f };

	//	auto collider = newObject->AddComponent<ColliderComponent>();
	//	collider->center = { 0.0f, 1.0f, 0.0f };
	//	collider->extend = { 3.0f, 1.0f, 1.0f };
	//}

	return newObject;
}

void GameObjectFactory::Destroy(GameObjectAllocator& allocator, GameObject* gameObject)
{
	allocator.Delete(gameObject);
}