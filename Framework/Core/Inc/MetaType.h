#pragma once

namespace Omega::Core::Meta
{
	class MetaClass;
	class MetaArray;
	class MetaPointer;

	class MetaType
	{
	public:
		using DeserializeFunc = std::function<void(void* instance, const rapidjson::Value& jsongValue)>;

		enum class Category
		{
			Primitive,
			Class,
			Array,
			Pointer
		};

		MetaType(Category category, 
			std::string_view name, 
			size_t size,
			DeserializeFunc deserialize = nullptr) noexcept;

		// copy constructor
		MetaType(const MetaType&) = delete;
		// copy assignment
		MetaType& operator=(const MetaType&) = delete;

		virtual ~MetaType() = default;
		virtual void Deserialize(void* instance, const rapidjson::Value& jsonValue) const;

		const MetaClass* AsMetaClass() const;
		const MetaArray* AsMetaArray() const;
		const MetaPointer* AsMetaPointer() const;

		constexpr Category GetCategory() const noexcept { return mCategory; }
		constexpr std::string_view GetName() const noexcept { return mName; }
		constexpr size_t GetSize() const noexcept { return mSize; }

	private:
		const DeserializeFunc mDeserialize;
		const std::string_view mName;
		const Category mCategory;
		const size_t mSize;
	};
}