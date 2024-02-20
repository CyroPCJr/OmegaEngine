#include "Precompiled.h"
#include "MetaField.h"

using namespace Omega::Core::Meta;

MetaField::MetaField(const MetaType* type,
	std::string_view name,
	size_t offset) noexcept :
	mType(type), mName(name), mOffset(offset)
{
}

void* MetaField::GetFieldInstance(void* classInstance) const noexcept
{
	return static_cast<uint8_t*>(classInstance) + mOffset;
}

