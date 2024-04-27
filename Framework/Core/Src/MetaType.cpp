#include "Precompiled.h"
#include "MetaType.h"
#include "MetaArray.h"
#include "MetaClass.h"
#include "MetaPointer.h"
#include "DebugUtil.h"

using namespace Omega::Core::Meta;

MetaType::MetaType(Category category, std::string_view name, size_t size, DeserializeFunc deserialize) noexcept
	: mCategory(category)
	, mName(name)
	, mSize(size)
	, mDeserialize(std::move(deserialize))
{}

const MetaClass* MetaType::AsMetaClass() const
{
	OMEGAASSERT(mCategory == Category::Class, "[MetaType] -- MetaType is not a class type!");
	return dynamic_cast<const MetaClass*>(this);
}

const MetaArray* MetaType::AsMetaArray() const
{
	OMEGAASSERT(mCategory == Category::Array, "[MetaType] -- MetaType is not an array type!");
	return dynamic_cast<const MetaArray*>(this);
}

const MetaPointer* MetaType::AsMetaPointer() const
{
	OMEGAASSERT(mCategory == Category::Pointer, "[MetaType] -- MetaType is not a pointer type!");
	return dynamic_cast<const MetaPointer*>(this);
}

void MetaType::Deserialize(void* instance, const rapidjson::Value& jsonValue) const
{
	OMEGAASSERT(mDeserialize == nullptr, "[MetaType] -- No deserialize callable registered for '%s'.", GetName());
	mDeserialize(instance, jsonValue);
}
