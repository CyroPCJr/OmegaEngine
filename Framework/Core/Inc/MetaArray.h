#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaArray : public MetaType
	{
	public:
		MetaArray(const MetaType* element);

		const MetaType* GetElementType() const { return mElementType; }

	private:
		const MetaType* const mElementType;
	};

}
