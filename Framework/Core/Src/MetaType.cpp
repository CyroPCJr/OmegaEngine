#include "Precompiled.h"
#include "MetaType.h"

using namespace Omega::Core::Meta;

MetaType::MetaType(Category category, const char* name, size_t size)
	: mCategory(category), mName(name), mSize(size)
{}