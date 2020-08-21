#pragma once

#include "MetaType.h"
#include "MetaUtil.h"

#define META_TYPE_DECLARE(Type)\
	template<> const Omega::Core::Meta::MetaType* Omega::Core::Meta::GetMetaType<Type>();

#define META_TYPE_DEFINE(Type, Name)\
	template<> const Omega::Core::Meta::MetaType* Omega::Core::Meta::GetMetaType<Type>()\
	{\
		static const Omega::Core::Meta::MetaType sMetaType(Omega::Core::Meta::MetaType::Category::Primitive, #Name, sizeof(Type));\
		return &sMetaType;\
	}