#pragma once

namespace AI
{
	using Property = std::variant<int, float, Omega::Math::Vector2>;

	struct MemoryRecord
	{
		std::unordered_map<std::string, Property> properties;
		uint64_t uniqueId = 0;
		float lastRecordedTime = 0.0f;
		float importance = 0.0f;
	};

	using MemoryRecords = std::list<MemoryRecord>;

}