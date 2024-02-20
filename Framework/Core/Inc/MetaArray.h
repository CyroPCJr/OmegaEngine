#pragma once

#include "MetaType.h"

namespace Omega::Core::Meta
{
	class MetaArray final : public MetaType
	{
	public:
		MetaArray(const MetaType* element) noexcept;

		//copy constructor
		MetaArray(const MetaArray&) = delete;
		//copy assignment
		MetaArray& operator=(const MetaArray&) = delete;
		//move constructor
		MetaArray(MetaArray&&) = delete;
		//move assigment
		MetaArray& operator=(MetaArray&&) = delete;

		const MetaType* GetElementType() const noexcept { return mElementType; }

	private:
		const MetaType* const mElementType;
		int mPadding{};
	};

}
