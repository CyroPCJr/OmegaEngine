#pragma once

namespace Omega::Core::Meta
{
	class MetaType;

	class MetaField final
	{
	public:

		MetaField(const MetaType* type, std::string_view name, size_t offset) noexcept;

		void* GetFieldInstance(void* classInstance) const noexcept;

		const MetaType* GetMetaType() const noexcept { return mType; }
		const std::string& GetName() const noexcept { return mName; }
		constexpr size_t GetOffset() const noexcept { return mOffset; }

	private:
		const MetaType* mType;
		const std::string mName;
		const size_t mOffset;
	};
}