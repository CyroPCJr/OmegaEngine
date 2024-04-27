#pragma once

namespace Omega::Core
{
	template <typename T, size_t PoolSize>
	class ObjectPool
	{
	public:
		ObjectPool() noexcept(false)
		{
			pool.reserve(PoolSize);
			for (size_t i{ 0u }; i < PoolSize; ++i)
			{
				pool.push_back(std::make_shared<T>());
			}
		}

		std::weak_ptr<T> AcquireObject()
		{
			if (numObjectsInUse == PoolSize)
			{
				throw std::runtime_error("Pool is full. Cannot acquire more objects.");
			}

			auto obj = pool.at(nextIndex);
			++numObjectsInUse;
			nextIndex = (nextIndex + 1u) % PoolSize;
			return obj;
		}

		void ReleaseObject(std::shared_ptr<T> obj)
		{
			if (std::find(pool.begin(), pool.end(), obj) != pool.end())
			{
				--numObjectsInUse;
			}
			else
			{
				throw std::invalid_argument("Object does not belong to this pool.");
			}
		}

		void ReleaseAllObjects() noexcept
		{
			numObjectsInUse = 0u;
			nextIndex = 0u;
		}

		const std::vector<std::shared_ptr<T>>& GetAllObjects() const noexcept
		{
			return pool;
		}

		constexpr size_t Size() const noexcept { return PoolSize; }
		
		constexpr size_t ObjectInUse() const noexcept { return numObjectsInUse; }

	private:
		std::vector<std::shared_ptr<T>> pool;
		size_t nextIndex = 0u;
		size_t numObjectsInUse = 0u;
	};
}