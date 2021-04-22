#pragma once

namespace Omega::AI
{
	using Property = std::variant<int, float, Omega::Math::Vector2>;

	struct MemoryRecord
	{
		std::unordered_map<std::string, Property> properties;
		uint64_t uniqueId = 0;
		float lastRecordedTime = 0.0f;
		float importance = 0.0f;

		bool operator==(const MemoryRecord& rhs) const
		{
			return this->uniqueId == rhs.uniqueId;
		}

		friend bool operator==(const MemoryRecord& lhs, const MemoryRecord& rhs)
		{
			return lhs.uniqueId == rhs.uniqueId;
		}
	};

	using MemoryRecords = std::list<MemoryRecord>;
	MemoryRecord& FindOrCreate(MemoryRecords& records, uint32_t uniqueID); // Work with this function later
}