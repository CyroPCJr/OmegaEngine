#pragma once

namespace Omega::Core::Meta
{

	class MetaClass;

	// Register meta class so we can look it up later by name
	void Register(const MetaClass* metaClass);

	// Look up meta class by name
	const MetaClass* FindMetaClass(std::string_view className);

}

#define META_REGISTER(Class)\
	Omega::Core::Meta::Register(Class::StaticGetMetaClass())