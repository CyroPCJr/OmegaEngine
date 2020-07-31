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
			// TODO 
			// allocate capacity + 1 entries (we dont use slot 0)
			// add freeslots to mFreeSlots (excluding 0)
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

			// TODO
			// Get the next free slots
			// Set entry instance pointer
			// Return a handle to this entry (set index and generation)
			return HandleType();
		}

		void Unregister(HandleType handle)
		{
			// TODO 
			// Skip is handle is invalid
			// Find the entry and increment the generation ( this invalidade all existing handles to this slot)
			// Recycle the slot ( add the index back to mFreeSlots)
		}

		void Flush()
		{
			// TODO
			// Loop thought all entries and increment generation ( invalidates all existing handles)
			// Re-add all slot indices to mFreeSlots
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