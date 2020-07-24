#pragma once

#include "BlockAllocator.h"

namespace Omega::Core
{
	template<class DataType>
	class TypedAllocator : private BlockAllocator
	{
	public:
		TypedAllocator(size_t capacity)
			: BlockAllocator(sizeof(DataType), capacity)
		{}

		DataType* New()
		{
			// TODO
			// Get a new block from BlockAllocator
			// User placement new on the returned block
			return nullptr;
		}

		//// Part 2!
		//template<class... Args>
		//DataType* New()
		//{
		//	// TODO
		//	// Modify New() so its is using variadic template and perfect forwarding
		//}

		void Delete(DataType* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}

			// TODO
			// Call destructor on ptr
			// Return ptr to BlockAllocator
		}
	};
}