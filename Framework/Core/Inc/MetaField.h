#pragma once

namespace Omega::Core::Meta
{
	class MetaType;

	class MetaField
	{
	public:

		MetaField(const MetaType* type, const char* name, size_t offset);

		void* GetFieldInstance(void* classInstance) const;

		const MetaType* GetMetaType() const noexcept { return mType; }
		const char* GetName() const noexcept { return mName.c_str(); }
		size_t GetOffset() const noexcept { return mOffset; }

	private:
		const MetaType* mType;
		const std::string mName;
		const size_t mOffset;
	};
}