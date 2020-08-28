#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaField;

	class MetaClass : public MetaType
	{
	public:
		MetaClass(const char* name, size_t size, 
			const MetaClass* parent, std::vector<MetaField> fields);

		const MetaClass* GetParent() const;
		const MetaField* FindField(const char* name) const;
		const MetaField* GetField(size_t index) const;
		size_t GetFieldCount() const;

	private:
		size_t GetParentFieldCount() const;

		const MetaClass* mParent;
		const std::vector<MetaField> mFields;
	};
}