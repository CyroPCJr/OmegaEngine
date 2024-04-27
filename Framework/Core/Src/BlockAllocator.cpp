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
	OMEGAASSERT(capacity > 0u, "Invalid capacity.");
	mFreeSlots.resize(capacity);
	mData = malloc(blockSize * capacity);
	int i = 0;
	std::generate(mFreeSlots.begin(), mFreeSlots.end(), [&i]() {
		return ++i; });
}

BlockAllocator::~BlockAllocator()
{
	mFreeSlots.clear();
	free(mData);
}

void* BlockAllocator::Allocate() noexcept
{
	if (mFreeSlots.empty()) return nullptr;
	const size_t key = mFreeSlots.back();
	mFreeSlots.pop_back();
	return static_cast<uint8_t*>(mData) + key * mBlockSize;
}

void BlockAllocator::Free(void* ptr)
{
	constexpr int sizePtr = sizeof(&ptr);
	constexpr int sizeData = sizeof(&mData);
	auto giveBackSlot = (sizePtr - sizeData) / mBlockSize;
	mFreeSlots.emplace_back(giveBackSlot);
}
