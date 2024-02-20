#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaPointer final : public MetaType
	{
	public:
		MetaPointer(const MetaType* pointerType) noexcept;

		//copy constructor
		MetaPointer(const MetaPointer&) = delete;
		//copy assignment
		MetaPointer& operator=(const MetaPointer&) = delete;
		//move constructor
		MetaPointer(MetaPointer&&) = delete;
		//move assigment
		MetaPointer& operator=(MetaPointer&&) = delete;

		const MetaType* GetPointerType() const noexcept { return mPointerType; }
	private:
		const MetaType* const mPointerType;
		int mPadding{};
	};
}