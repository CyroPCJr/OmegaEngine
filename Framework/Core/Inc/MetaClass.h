#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaField;

	class MetaClass final : public MetaType
	{
	public:
		using CreateFunc = std::function<void* ()>;

		MetaClass(std::string_view name, size_t size,
			const MetaClass* parent,
			std::vector<MetaField> fields,
			CreateFunc create) noexcept;

		//copy constructor
		MetaClass(const MetaClass&) = delete;
		//copy assignment
		MetaClass& operator=(const MetaClass&) = delete;
		//move constructor
		//MetaClass(MetaClass&&) = delete;
		////move assigment
		//MetaClass& operator=(MetaClass&&) = delete;

		const MetaClass* GetParent() const noexcept;
		const MetaField* FindField(std::string_view name) const;
		const MetaField* GetField(size_t index) const;
		size_t GetFieldCount() const noexcept;

		void* Create() const;
		void Deserialize(void* classInstance, const rapidjson::Value& jsonValue) const override;

	private:
		constexpr size_t GetParentFieldCount() const noexcept;

		const CreateFunc mCreate;
		const std::vector<MetaField> mFields;
		const MetaClass* mParent;
		const int mPadding{ 0 };
	};
}