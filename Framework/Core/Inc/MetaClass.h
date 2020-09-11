#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaField;

	class MetaClass : public MetaType
	{
	public:
		using CreateFunc = std::function<void* ()>;

		MetaClass(const char* name, size_t size,
			const MetaClass* parent,
			std::vector<MetaField> fields,
			CreateFunc create);

		const MetaClass* GetParent() const;
		const MetaField* FindField(const char* name) const;
		const MetaField* GetField(size_t index) const;
		size_t GetFieldCount() const;

		void* Create() const;
		void Deserialize(void* classInstance, const rapidjson::Value& jsonValue) const override;

	private:
		size_t GetParentFieldCount() const;

		const MetaClass* mParent;
		const std::vector<MetaField> mFields;

		const CreateFunc mCreate;
	};
}