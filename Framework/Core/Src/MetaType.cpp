#include "Precompiled.h"
#include "MetaType.h"
#include "MetaArray.h"
#include "MetaClass.h"
#include "MetaPointer.h"

#include "DebugUtil.h"

using namespace Omega::Core::Meta;

MetaType::MetaType(Category category, const char* name, size_t size, DeserializeFunc deserialize)
	: mCategory(category)
	, mName(name)
	, mSize(size)
	, mDeserialize(std::move(deserialize))
{}

const MetaClass* MetaType::AsMetaClass() const
{
	OMEGAASSERT(mCategory == Category::Class, "[MetaType] -- MetaType is not a class type!");
	return static_cast<const MetaClass*>(this);
}

const MetaArray* MetaType::AsMetaArray() const
{
	OMEGAASSERT(mCategory == Category::Array, "[MetaType] -- MetaType is not an array type!");
	return static_cast<const MetaArray*>(this);
}

const MetaPointer* MetaType::AsMetaPointer() const
{
	OMEGAASSERT(mCategory == Category::Pointer, "[MetaType] -- MetaType is not a pointer type!");
	return static_cast<const MetaPointer*>(this);
}

void MetaType::Deserialize(void* instance, const rapidjson::Value& jsonValue) const
{
	OMEGAASSERT(mDeserialize, "[MetaType] -- No deserialize callable registered for '%s'.", GetName());
	mDeserialize(instance, jsonValue);
}
