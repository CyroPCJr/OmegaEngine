#pragma once
#include "Common.h"

namespace Omega::Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(size_t blockSize, size_t capacity);
		~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;

		BlockAllocator(BlockAllocator&&) = delete;
		BlockAllocator& operator=(BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);

		size_t GetCapacity() const { return mCapacity; }

	protected:
		void* mData;
		size_t mBlockSize;
		size_t mCapacity;
		std::vector<size_t> mFreeSlots;
	};

}