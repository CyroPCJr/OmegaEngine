#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Core;

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
		
	};
}
