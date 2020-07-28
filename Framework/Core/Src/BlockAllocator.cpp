#include "Precompiled.h"
#include "BlockAllocator.h"
#include "Debug.h"

using namespace Omega;
using namespace Omega::Core;

BlockAllocator::BlockAllocator(size_t blockSize, size_t capacity)
	: mData(nullptr)
	, mBlockSize(blockSize)
	, mCapacity(capacity)
{
	OMEGAASSERT(capacity > 0, "[BlockAllocator] Invalid capacity.");
	mFreeSlots.reserve(capacity);
	for (size_t i = 0; i < capacity; ++i)
	{
		mFreeSlots.push_back(sizeof(blockSize));
	}
}

BlockAllocator::~BlockAllocator()
{
	mFreeSlots.clear();
	mData = nullptr;
}

void* BlockAllocator::Allocate()
{
	/*if (mFreeSlots.size() == mCapacity) return nullptr;
	mData = reinterpret_cast<size_t*>(malloc(mBlockSize * sizeof(size_t)));
	return (void*)mFreeSlots.emplace_back(reinterpret_cast<size_t>(mData));*/

	// novo teste
	if (mFreeSlots.empty()) return nullptr;
	size_t key = mFreeSlots.front();
	mFreeSlots.pop_back();
	mData = reinterpret_cast<size_t*>(malloc(sizeof(size_t) + key * mBlockSize));
	return mData;
}

void BlockAllocator::Free(void* ptr)
{
	/*std::vector<size_t>::iterator iter = mFreeSlots.begin();
	for (; iter < mFreeSlots.end(); ++iter)
	{
		if (*iter == reinterpret_cast<size_t>(ptr))
		{
			mFreeSlots.erase(iter);
			break;
		}
	}

	free(ptr);*/
	// novo codigo
	auto giveBackSlot = (&ptr - &mData) / mBlockSize;
	mFreeSlots.push_back(sizeof(giveBackSlot));
}
