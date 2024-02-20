#include "Precompiled.h"
#include "MetaArray.h"

using namespace Omega::Core::Meta;
using namespace std::literals::string_view_literals;

MetaArray::MetaArray(const MetaType* elementType) noexcept
	: MetaType(MetaType::Category::Array, "Array"sv, sizeof(std::vector<int>))
	, mElementType(elementType)
{}