#include "Precompiled.h"
#include "MetaRegistration.h"

namespace Omega::Core::Meta
{
	template<>
	void Deserialize<int>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			//*(int*)instance = value.GetInt();
			*static_cast<int*>(instance) = value.GetInt();
		}
	}

	template<>
	void Deserialize<float>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			//*(float*)instance = value.GetFloat();
			*static_cast<float*>(instance) = value.GetFloat();
		}
	}

	template<>
	void Deserialize<bool>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			//*(bool*)instance = value.GetBool();
			*static_cast<bool*>(instance) = value.GetBool();
		}
	}

	template<>
	void Deserialize<std::string_view>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			//*(std::string*)instance = value.GetString();
			*static_cast<std::string_view*>(instance) = value.GetString();
		}
	}
}

// Primitive Type Definitions
META_TYPE_DEFINE(int, Integer)
META_TYPE_DEFINE(float, Number)
META_TYPE_DEFINE(bool, Boolean)
META_TYPE_DEFINE(std::string_view, String)

void Omega::Core::StaticMetaRegister() noexcept
{
	// MetaClass registration here...
	//e.g META_REGISTER(Foo);
}