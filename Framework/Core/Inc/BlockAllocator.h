#pragma once
#include "Common.h"

namespace Omega::Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(size_t blockSize, size_t capacity) noexcept;
		virtual ~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;

		BlockAllocator(BlockAllocator&&) = delete;
		BlockAllocator& operator=(BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);

		size_t GetCapacity() const noexcept { return mCapacity; }

	protected:
		std::vector<size_t> mFreeSlots;
		void* mData;
		size_t mBlockSize;
		size_t mCapacity;
	};

}