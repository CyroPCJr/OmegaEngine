#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Core;


class Car
{
public:
	META_CLASS_DECLARE

public:
	void Move() { mPosition += 1.0f; }
protected:
	float mPosition = 0.0f;
	bool mAutomatic = true;
};

META_CLASS_BEGIN(Car)
	META_FIELD_BEGIN
		META_FIELD(mPosition, "Position")
		META_FIELD(mAutomatic, "Automatic")
	META_FIELD_END
META_CLASS_END

namespace CoreTest
{
	TEST_CLASS(MetaTest)
	{
	public:

		TEST_METHOD(TestMetaType)
		{
			auto intType = Meta::GetMetaType<int>();
			Assert::IsTrue(intType->GetCategory() == Meta::MetaType::Category::Primitive);
			Assert::AreEqual(intType->GetName(), "Integer");
			Assert::AreEqual(intType->GetSize(), sizeof(int));
		}

		TEST_METHOD(TestMetaClass)
		{
			auto metaClass = Car::StaticGetMetaClass();
			Assert::IsNull(metaClass->GetParent());
			Assert::IsTrue(metaClass->GetFieldCount() == 2);

			auto metaField0 = metaClass->GetField(0);
			Assert::IsTrue(metaField0->GetMetaType() == Meta::GetMetaType<float>());
			Assert::AreEqual(metaField0->GetName(), "Position");
			Assert::IsTrue(metaField0 == metaClass->FindField("Position"));

			auto metaField1 = metaClass->GetField(1);
			Assert::IsTrue(metaField1->GetMetaType() == Meta::GetMetaType<bool>());
			Assert::AreEqual(metaField1->GetName(), "Automatic");
			Assert::IsTrue(metaField1 == metaClass->FindField("Automatic"));
		}

	};
}
