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
			// Get a new block from BlockAllocator
			// User placement new on the returned block
			DataType* dataAlloc = (DataType*)Allocate();
			if (!dataAlloc) return nullptr;
			dataAlloc = new DataType;
			return dataAlloc;
		}

		//// Part 2!
		//template<class... Args>
		//DataType* New()
		//{
		//	// TODO
		//	// Modify New() so its is using variadic template and perfect forwarding
		//}

		//TODO: corrigir 
		void Delete(DataType* ptr)
		{
			if (ptr == nullptr) return;
			// Call destructor on ptr
			delete ptr;
			// Return ptr to BlockAllocator
			Free(ptr);
		}
	};
}