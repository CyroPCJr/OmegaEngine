#pragma once

namespace Omega
{
    // Object pool class
    template <typename T, size_t PoolSize>
    class ObjectPool
    {
    public:
        std::shared_ptr<T> AcquireObject()
        {
            for (size_t i{ 0 }; i < PoolSize; ++i)
            {
                if (!inUse[i])
                {
                    inUse[i] = true;
                    return std::shared_ptr<T>(&objects[i], [](T*) {}); // Custom deleter to prevent deletion
                }
            }
            return nullptr; // Pool is full
        }

        std::array<T, PoolSize>& GetAllObjects() const
        {
            return objects;
        }

        void ReleaseObject(const std::shared_ptr<T>& obj)
        {
            for (size_t i{ 0 }; i < PoolSize; ++i)
            {
                if (obj.get() == &objects[i])
                {
                    inUse[i] = false;
                    return;
                }
            }
            throw std::invalid_argument("Object does not belong to this pool.");
        }

    private:
        std::array<T, PoolSize> objects;
        std::array<bool, PoolSize> inUse = { false }; // Indicates whether each object slot is in use
    };
}