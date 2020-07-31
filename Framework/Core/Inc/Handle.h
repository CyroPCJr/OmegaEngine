#pragma once

#include "Common.h"

namespace Omega::Core
{
	template<class DataType>
	class HandlePool;

	template<class DataType>
	class Handle
	{
	public:
		Handle()
			: mIndex(0),  // slot 0 will be unused, in other word handle at 0 is an invalidate handle
			mGeneration(0)
		{}


		bool IsValid() const
		{
			return sPool && sPool->IsValid(*this);
		}

		void Invalidate()
		{
			*this == Handle();
		}

		DataType* Get() const
		{
			return sPool ? sPool->Get(*this) : nullptr;
		}

		DataType* operator->() const
		{
			return sPool ? sPool->Get(*this) : nullptr;
		}

		DataType& operator*() const
		{
			return *(sPool->Get(*this)); // dereference
		}

		bool operator==(Handle rhs) const { return mIndex == rhs.mIndex && mGeneration == rhs.mGeneration; }
		bool operator!=(Handle rhs) const { return !(*this == rhs); }

	private:
		friend class HandlePool<DataType>;

		static HandlePool<DataType>* sPool;

		uint32_t mIndex : 16; // bit packing
		uint32_t mGeneration : 16;
	};

	// Initialize static outside
	template<class DataType>
	HandlePool<DataType>* Handle<DataType>::sPool = nullptr;
}