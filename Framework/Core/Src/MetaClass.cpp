#include "Precompiled.h"
#include "MetaClass.h"

#include "DebugUtil.h"
#include "MetaField.h"

using namespace Omega::Core::Meta;

MetaClass::MetaClass(const char* name,
	size_t size,
	const MetaClass* parent,
	std::vector<MetaField> fields,
	CreateFunc create)
	: MetaType(MetaType::Category::Class, name, size)
	, mParent(parent)
	, mFields(std::move(fields))
	, mCreate(std::move(create))
{
}

const MetaClass* MetaClass::GetParent() const
{
	return mParent;
}

const MetaField* MetaClass::FindField(const char* name) const
{
	for (auto& field : mFields)
	{
		if (strcmp(field.GetName(), name) == 0)
		{
			return &field;
		}
	}
	// If The field is not found, try the parent
	if (mParent != nullptr)
	{
		return mParent->FindField(name);
	}
	return nullptr;
}

const MetaField* MetaClass::GetField(size_t index) const
{
	OMEGAASSERT(index < GetFieldCount(), "[MetaClass] --  Subscript out of range!");
	const size_t parentCount = GetParentFieldCount();
	if (index < parentCount)
	{
		return mParent->GetField(index);
	}
	return mFields.data() + (index - parentCount);
}

size_t MetaClass::GetFieldCount() const
{
	return mFields.size() + GetParentFieldCount();
}

void* MetaClass::Create() const
{
	OMEGAASSERT(mCreate, "[MetaClass] -- No creation callable registered for '%s'.", GetName());
	return mCreate();
}

void MetaClass::Deserialize(void* classInstance, const rapidjson::Value& jsonValue) const
{
	for (auto& member : jsonValue.GetObjectW())
	{
		auto metaField = FindField(member.name.GetString());
		auto metaType = metaField->GetMetaType();
		metaType->Deserialize(metaField->GetFieldInstance(classInstance), member.value);
	}
}

size_t MetaClass::GetParentFieldCount() const
{
	return mParent ? mParent->GetFieldCount() : 0u;
}