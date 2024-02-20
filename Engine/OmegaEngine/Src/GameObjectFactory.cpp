#include "Precompiled.h"
#include "GameObjectFactory.h"

#include "Component.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

using namespace Omega;

GameObject* GameObjectFactory::Create(GameObjectAllocator& allocator, const std::filesystem::path& templateFileName)
{
	using namespace rapidjson;

	auto gameObject = allocator.New();
	if (gameObject)
	{
		FILE* file = nullptr;
		fopen_s(&file, templateFileName.u8string().c_str(), "r");

		char readBuffer[65536]{};
		FileReadStream is(file, readBuffer, sizeof(readBuffer));
		
		Document document;
		document.ParseStream(is);

		if (document.HasMember("GameObject") && document["GameObject"].IsObject())
		{
			auto jsonObject = document["GameObject"].GetObjectW();
			if (jsonObject.HasMember("Components") && jsonObject["Components"].IsObject())
			{
				auto components = jsonObject["Components"].GetObjectW();
				for (const auto& component: components)
				{
					auto metaClass = Core::Meta::FindMetaClass(component.name.GetString());
					auto newComponent = gameObject->AddComponent(metaClass);
					metaClass->Deserialize(newComponent, component.value);
				}
			}
		}
		fclose(file);
	}
	return gameObject;
}

void GameObjectFactory::Destroy(GameObjectAllocator& allocator, GameObject* gameObject)
{
	allocator.Delete(gameObject);
}