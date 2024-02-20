#pragma once

#include "BlockAllocator.h"

namespace Omega::Core
{
	template<class DataType>
	class TypedAllocator final : private BlockAllocator
	{
	public:
		TypedAllocator(size_t capacity) noexcept
			: BlockAllocator(sizeof(DataType), capacity)
		{}

		template<class... Args>
		DataType* New(Args&&... args)
		{
			// Modify New() so its is using variadic template and perfect forwarding
			DataType* dataAlloc = static_cast<DataType*>(Allocate());
			if (dataAlloc)
			{
				new (dataAlloc) DataType(std::forward<Args>(args)...);
			}
			return dataAlloc;
		}

		void Delete(DataType* ptr)
		{
			if (!ptr) return; // ptr == nullptr
			ptr->~DataType(); // Call destructor on ptr
			Free(ptr); // Return ptr to BlockAllocator
		}
	};
}