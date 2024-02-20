#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Core;


class Car
{
public:
	META_CLASS_DECLARE
public:
	virtual ~Car() noexcept = default;
	void Move() noexcept { mPosition += 1.0f; }
protected:
	float mPosition{ 0.0f };
	bool mAutomatic{ true };
	char mPadding[3]{};
};

class Tesla final : public Car
{
public:
	META_CLASS_DECLARE
		void Move() { mPosition += 10.f; }
protected:
	bool mGPS{ true };
	char mPadding[3]{};
};

META_CLASS_BEGIN(Car)
META_FIELD_BEGIN
META_FIELD(mPosition, "Position")
META_FIELD(mAutomatic, "Automatic")
META_FIELD_END
META_CLASS_END

META_DERIVED_BEGIN(Tesla, Car)
META_FIELD_BEGIN
META_FIELD(mGPS, "GPS")
META_FIELD_END
META_CLASS_END

namespace CoreTest
{

	using namespace std::literals::string_view_literals;
	TEST_CLASS(MetaTest)
	{
	public:

		TEST_METHOD(TestMetaType)
		{
			auto intType = Meta::GetMetaType<int>();
			Assert::IsTrue(intType->GetCategory() == Meta::MetaType::Category::Primitive);
			Assert::AreEqual(intType->GetName(), "Integer"sv);
			Assert::AreEqual(intType->GetSize(), sizeof(int));
		}

		TEST_METHOD(TestMetaPointer)
		{
			float* floatPtr = nullptr;

			auto metaType = Meta::GetMetaType<float*>();
			Assert::IsTrue(metaType->GetCategory() == Meta::MetaType::Category::Pointer);
			Assert::AreEqual(metaType->GetName(), "Pointer"sv);
			Assert::AreEqual(metaType->GetSize(), sizeof(float*));

			auto metaPointer = metaType->AsMetaPointer();
			Assert::IsTrue(metaPointer->GetPointerType() == Meta::GetMetaType<float>());
		}

		TEST_METHOD(TestMetaArray)
		{
			using FloatVec = std::vector<float>;

			auto metaType = Meta::GetMetaType<FloatVec>();
			Assert::IsTrue(metaType->GetCategory() == Meta::MetaType::Category::Array);
			Assert::AreEqual(metaType->GetName(), "Array"sv);
			Assert::AreEqual(metaType->GetSize(), sizeof(FloatVec));

			auto metaArray = metaType->AsMetaArray();
			Assert::IsTrue(metaArray->GetElementType() == Meta::GetMetaType<float>());
		}

		TEST_METHOD(TestMetaClass)
		{
			auto metaType = Meta::GetMetaType<Car>();
			Assert::IsTrue(metaType->GetCategory() == Meta::MetaType::Category::Class);
			Assert::AreEqual(metaType->GetName(), "Car"sv);
			Assert::AreEqual(metaType->GetSize(), sizeof(Car));

			auto metaClass = Car::StaticGetMetaClass();
			Assert::IsTrue(metaClass == metaType->AsMetaClass());
			Assert::IsNull(metaClass->GetParent());
			Assert::IsTrue(metaClass->GetFieldCount() == 2);

			auto metaField0 = metaClass->GetField(0);
			Assert::IsTrue(metaField0->GetMetaType() == Meta::GetMetaType<float>());
			Assert::AreEqual(metaField0->GetName(), "Position"sv);
			Assert::IsTrue(metaField0 == metaClass->FindField("Position"sv));

			auto metaField1 = metaClass->GetField(1);
			Assert::IsTrue(metaField1->GetMetaType() == Meta::GetMetaType<bool>());
			Assert::AreEqual(metaField1->GetName(), "Automatic"sv);
			Assert::IsTrue(metaField1 == metaClass->FindField("Automatic"sv));
		}

		TEST_METHOD(TestMetaDerived)
		{
			auto metaClass = Tesla::StaticGetMetaClass();
			Assert::IsTrue(metaClass->GetParent() == Car::StaticGetMetaClass());
			Assert::IsTrue(metaClass->GetFieldCount() == 3);

			auto metaField0 = metaClass->GetField(0);
			Assert::IsTrue(metaField0->GetMetaType() == Meta::GetMetaType<float>());
			std::string_view sv{ "Position"sv };
			Assert::AreEqual(metaField0->GetName(), sv);
			Assert::IsTrue(metaField0 == metaClass->FindField(sv));

			auto metaField1 = metaClass->GetField(1);
			sv = "Automatic"sv;
			Assert::IsTrue(metaField1->GetMetaType() == Meta::GetMetaType<bool>());
			Assert::AreEqual(metaField1->GetName(), sv);
			Assert::IsTrue(metaField1 == metaClass->FindField(sv));

			auto metaField2 = metaClass->GetField(2);
			sv = "GPS"sv;
			Assert::IsTrue(metaField2->GetMetaType() == Meta::GetMetaType<bool>());
			Assert::AreEqual(metaField2->GetName(), sv);
			Assert::IsTrue(metaField2 == metaClass->FindField(sv));
		}

	};
}
