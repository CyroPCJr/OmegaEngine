#include "Precompiled.h"
#include "MetaClass.h"
#include "MetaField.h"

#include "DebugUtil.h"

using namespace Omega::Core::Meta;

MetaClass::MetaClass(std::string_view name,
	size_t size,
	const MetaClass* parent,
	std::vector<MetaField> fields,
	CreateFunc create) noexcept
	: MetaType(MetaType::Category::Class, name, size)
	, mParent(parent)
	, mFields(std::move(fields))
	, mCreate(std::move(create))
{
}

const MetaClass* MetaClass::GetParent() const noexcept
{
	return mParent;
}

const MetaField* MetaClass::FindField(std::string_view name) const
{
	for (const auto& field : mFields)
	{
		if (!field.GetName().compare(name))
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

size_t MetaClass::GetFieldCount() const noexcept
{
	const size_t size = mFields.size();
	return size + GetParentFieldCount();
}

void* MetaClass::Create() const
{
	OMEGAASSERT(mCreate, "[MetaClass] -- No creation callable registered for '%s'.", GetName());
	return mCreate();
}

void MetaClass::Deserialize(void* classInstance, const rapidjson::Value& jsonValue) const
{
	for (const auto& member : jsonValue.GetObjectW())
	{
		if (const auto& metaField = FindField(member.name.GetString()); metaField)
		{
			auto metaType = metaField->GetMetaType();
			metaType->Deserialize(metaField->GetFieldInstance(classInstance), member.value);
		}
	}
}

constexpr size_t MetaClass::GetParentFieldCount() const noexcept
{
	return mParent ? mParent->GetFieldCount() : 0u;
}