#pragma once

#include "MetaArray.h"
#include "MetaClass.h"
#include "MetaField.h"
#include "MetaPointer.h"
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

#define META_CLASS_DECLARE\
	static const Omega::Core::Meta::MetaClass* StaticGetMetaClass();\
	virtual const Omega::Core::Meta::MetaClass* GetMetaClass() const { return StaticGetMetaClass(); }

#define META_CLASS_BEGIN(ClassType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const Omega::Core::Meta::MetaClass* parentMetaClass = nullptr;

#define META_DERIVED_BEGIN(ClassType, ParentType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const Omega::Core::Meta::MetaClass* parentMetaClass = ParentType::StaticGetMetaClass();

#define META_CLASS_BEGIN_INTERNAL(ClassType)\
	template <> const Omega::Core::Meta::MetaType* Omega::Core::Meta::GetMetaType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const Omega::Core::Meta::MetaClass* ClassType::StaticGetMetaClass()\
	{\
		using Class = ClassType;\
		const char* className = #ClassType;

#define META_FIELD_BEGIN\
		static const std::initializer_list<Omega::Core::Meta::MetaField> fields {

#define META_FIELD(Var, Name)\
			{ Omega::Core::Meta::GetFieldType(&Class::Var), Name, Omega::Core::Meta::GetFieldOffset(&Class::Var) },

#define META_FIELD_END\
		};

#define META_NO_FIELD\
		static const std::initializer_list<Omega::Core::Meta::MetaField> fields;

#define META_CLASS_END\
		static const Omega::Core::Meta::MetaClass sMetaClass(\
			className, sizeof(Class),\
			parentMetaClass, fields);\
		return &sMetaClass;\
	}