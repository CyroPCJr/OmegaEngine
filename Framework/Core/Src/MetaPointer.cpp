#include "Precompiled.h"
#include "MetaPointer.h"

using namespace Omega::Core::Meta;
using namespace std::literals::string_view_literals;

MetaPointer::MetaPointer(const MetaType* pointerType) noexcept
	: MetaType(MetaType::Category::Pointer, "Pointer"sv, sizeof(nullptr))
	, mPointerType(pointerType)
{
}
