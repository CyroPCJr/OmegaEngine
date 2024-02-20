#pragma once

#include "Meta.h"

// Primitive Type Declarations
META_TYPE_DECLARE(int);
META_TYPE_DECLARE(float);
META_TYPE_DECLARE(bool);
META_TYPE_DECLARE(std::string_view);

namespace Omega::Core
{
	void StaticMetaRegister() noexcept;
}