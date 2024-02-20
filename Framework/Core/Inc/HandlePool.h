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

		HandlePool() noexcept = default;

		// copy ctor and assignment
		HandlePool(const HandlePool&) = delete;
		HandlePool& operator=(const HandlePool&) = delete;
		//move constructor and assigment
		HandlePool(HandlePool&&) = delete;
		HandlePool& operator=(HandlePool&&) = delete;

		~HandlePool()
		{
			OMEGAASSERT(HandleType::sPool == this, "[%s] -- Something is wrong ...", __FUNCTION__);
			HandleType::sPool = nullptr;
		}

		HandlePool(size_t capacity)
		{
			OMEGAASSERT(capacity > 0, "[%s] -- Invalid capacity.", __FUNCTION__);
			// allocate capacity + 1 entries (we dont use slot 0)
			// add freeslots to mFreeSlots (excluding 0)
			mEntries.resize(capacity + 1);
			mFreeSlots.reserve(capacity);
			for (size_t i = 1; i <= capacity; ++i)
			{
				mFreeSlots.push_back(i);
			}
			OMEGAASSERT(HandleType::sPool == nullptr, "[%s] -- Cannot have more than one pool of this type!", __FUNCTION__);
			HandleType::sPool = this;
		}

		HandleType Register(DataType* instance)
		{
			OMEGAASSERT(instance != nullptr, "[%s] -- Invalid instance.", __FUNCTION__);
			OMEGAASSERT(!mFreeSlots.empty(), "[%s] -- No more free slots available.", __FUNCTION__);

			// Get the next free slots
			// Set entry instance pointer
			// Return a handle to this entry (set index and generation)
			const size_t key = mFreeSlots.back();
			mFreeSlots.pop_back();
			Entry& entry = mEntries[key];
			entry.instance = std::move(instance);

			HandleType handle;
			handle.mIndex = key;
			handle.mGeneration = entry.generation;

			return handle;
		}

		void Unregister(const HandleType& handle)
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
			for (size_t i = 0, size = mEntries.size() ; i < size; ++i)
			{
				mEntries[i].generation++;
				mFreeSlots.push_back(i + 1);
			}
		}

		bool IsValid(const HandleType& handle) const
		{
			return handle != HandleType() && mEntries[handle.mIndex].generation == handle.mGeneration;
		}

		DataType* Get(const HandleType& handle)
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