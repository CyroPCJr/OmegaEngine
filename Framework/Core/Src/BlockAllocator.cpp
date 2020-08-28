#include "Precompiled.h"
#include "BlockAllocator.h"
#include "DebugUtil.h"

using namespace Omega;
using namespace Omega::Core;

BlockAllocator::BlockAllocator(size_t blockSize, size_t capacity)
	: mData(nullptr)
	, mBlockSize(blockSize)
	, mCapacity(capacity)
{
	OMEGAASSERT(capacity > 0, "[BlockAllocator] Invalid capacity.");
	mFreeSlots.reserve(capacity);
	mData = malloc(blockSize * capacity);
	for (size_t i = 0; i < capacity; ++i)
	{
		mFreeSlots.push_back(i);
	}
}

BlockAllocator::~BlockAllocator()
{
	mFreeSlots.clear();
	free(mData);
}

void* BlockAllocator::Allocate()
{
	if (mFreeSlots.empty()) return nullptr;
	const size_t key = mFreeSlots.back();
	mFreeSlots.pop_back();
	return static_cast<uint8_t*>(mData) + key * mBlockSize;
}

void BlockAllocator::Free(void* ptr)
{
	auto giveBackSlot = sizeof(&ptr - &mData) / mBlockSize;
	mFreeSlots.push_back(giveBackSlot);
}
