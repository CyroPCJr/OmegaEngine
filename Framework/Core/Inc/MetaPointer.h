#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaPointer : public MetaType
	{
	public:
		MetaPointer(const MetaType* pointerType);

		const MetaType* GetPointerType() const { return mPointerType; }
	private:
		const MetaType* const mPointerType;
	};
}