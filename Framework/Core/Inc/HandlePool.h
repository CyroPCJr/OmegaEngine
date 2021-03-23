#pragma once

#include "Common.h"
#include "DebugUtil.h"

namespace Omega::Core
{
	template<class DataType>
	class Handle;

	template<class DataType>
	class HandlePool
	{
	public:
		using HandleType = Handle<DataType>;

		HandlePool(size_t capacity)
		{
			OMEGAASSERT(capacity > 0, "[HandlePool] -- Invalid capacity.");
			// allocate capacity + 1 entries (we dont use slot 0)
			// add freeslots to mFreeSlots (excluding 0)
			mEntries.resize(capacity + 1);
			mFreeSlots.reserve(capacity);
			for (size_t i = 1; i <= capacity; ++i)
			{
				mFreeSlots.push_back(i);
			}
			OMEGAASSERT(HandleType::sPool == nullptr, "[HandlePool] -- Cannot have more than one pool of this type!");
			HandleType::sPool = this;
		}

		~HandlePool()
		{
			OMEGAASSERT(HandleType::sPool == this, "[HandlePool] -- Something is wrong ...");
			HandleType::sPool = nullptr;
		}

		HandleType Register(DataType* instance)
		{
			OMEGAASSERT(instance != nullptr, "[HandlePool] -- Invalid instance.");
			OMEGAASSERT(!mFreeSlots.empty(), "[HandlePool] -- No more free slots available.");

			// Get the next free slots
			// Set entry instance pointer
			// Return a handle to this entry (set index and generation)
			size_t key = mFreeSlots.back();
			mFreeSlots.pop_back();

			mEntries[key].instance = std::move(instance);

			HandleType handle;
			handle.mIndex = key;
			handle.mGeneration = mEntries[key].generation;

			return handle;
		}

		void Unregister(HandleType handle)
		{
			// Skip is handle is invalid
			// Find the entry and increment the generation ( this invalidade all existing handles to this slot)
			// Recycle the slot ( add the index back to mFreeSlots)
			if (!handle.IsValid()) return;

			mEntries[handle.mIndex].generation++;
			mFreeSlots.push_back(handle.mIndex);
		}

		void Flush()
		{
			// Loop thought all entries and increment generation ( invalidates all existing handles)
			// Re-add all slot indices to mFreeSlots
			const size_t size = mEntries.size();
			for (size_t i = 0; i < size; ++i)
			{
				mEntries[i].generation++;
				mFreeSlots.push_back(i + 1);
			}
		}

		bool IsValid(HandleType handle) const
		{
			return handle != HandleType() && mEntries[handle.mIndex].generation == handle.mGeneration;
		}

		DataType* Get(HandleType handle)
		{
			return IsValid(handle) ? mEntries[handle.mIndex].instance : nullptr;
		}

	private:
		struct Entry
		{
			DataType* instance = nullptr;
			uint32_t generation = 0;
		};

		std::vector<Entry> mEntries;
		std::vector<size_t> mFreeSlots;
	};

}