#include "Precompiled.h"
#include "MetaRegistration.h"

// Primitive Type Definitions
META_TYPE_DEFINE(int, Integer)
META_TYPE_DEFINE(float, Number)
META_TYPE_DEFINE(bool, Boolean)
META_TYPE_DEFINE(std::string, String)

void Omega::Core::StaticMetaRegister()
{
	// MetaClass registration here...
	//e.g META_REGISTER(Foo);
}