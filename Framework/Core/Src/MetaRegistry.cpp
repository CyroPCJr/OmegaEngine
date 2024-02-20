#include "Precompiled.h"
#include "MetaRegistry.h"

#include "DebugUtil.h"
#include "MetaClass.h"

using namespace Omega::Core;

namespace
{
	inline auto& GetRegistry()
	{
		using MetaClassMap = std::map<std::string_view, const Meta::MetaClass*>;
		static MetaClassMap sMetaClassMap;
		return sMetaClassMap;
	}
}

void Meta::Register(const Meta::MetaClass* metaClass)
{
	if (metaClass)
	{
		GetRegistry().emplace(metaClass->GetName(), metaClass);
	}
}

const Meta::MetaClass* Meta::FindMetaClass(std::string_view className)
{
	const auto iter = GetRegistry().find(className);
	OMEGAASSERT(iter != GetRegistry().end(), "[MetaRegistry] --- Meta class for %s not found.", className);
	return iter->second;
}