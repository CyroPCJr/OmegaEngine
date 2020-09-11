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

		const MetaClass* AsMetaClass() const;
		const MetaArray* AsMetaArray() const;
		const MetaPointer* AsMetaPointer() const;

		MetaType(Category category, 
			const char* name, 
			size_t size,
			DeserializeFunc deserialize = nullptr);

		Category GetCategory() const { return mCategory; }
		const char* GetName() const { return mName.c_str(); }
		size_t GetSize() const { return mSize; }

		virtual void Deserialize(void* instance, const rapidjson::Value& jsonValue) const;

	private:
		const Category mCategory;
		const std::string mName;
		const size_t mSize;
		const DeserializeFunc mDeserialize;
	};
}