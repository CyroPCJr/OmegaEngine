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

		//TODO: Fazer mais testes
		DataType* New()
		{
			// Get a new block from BlockAllocator
			// this return the block of memory from Allocator
			DataType* dataAlloc = (DataType*)Allocate();
			if (!dataAlloc) return nullptr;
			// User placement new on the returned block
			// use the block from allocator and call the construtor from DataType(new)
			DataType* datatypePtr = new (dataAlloc) DataType;
			return datatypePtr;
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
			if (!ptr) return; // ptr == nullptr
			ptr->~DataType(); // Call destructor on ptr
			Free(ptr); // Return ptr to BlockAllocator
		}
	};
}