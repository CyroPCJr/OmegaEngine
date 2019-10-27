#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Math;

namespace MathTest
{
	TEST_CLASS(Vector3Test)
	{
	public:

		TEST_METHOD(TestStatics)
		{
			Vector3 zero = Vector3::Zero;
			Assert::AreEqual(zero.x, 0.0f);
			Assert::AreEqual(zero.y, 0.0f);
			Assert::AreEqual(zero.z, 0.0f);

			Vector3 one = Vector3::One;
			Assert::AreEqual(one.x, 1.0f);
			Assert::AreEqual(one.y, 1.0f);
			Assert::AreEqual(one.z, 1.0f);

			Vector3 XAxis = Vector3::XAxis;
			Assert::AreEqual(XAxis.x, 1.0f);
			Assert::AreEqual(XAxis.y, 0.0f);
			Assert::AreEqual(XAxis.z, 0.0f);

			Vector3 YAxis = Vector3::YAxis;
			Assert::AreEqual(YAxis.x, 0.0f);
			Assert::AreEqual(YAxis.y, 1.0f);
			Assert::AreEqual(YAxis.z, 0.0f);

			Vector3 ZAxis = Vector3::ZAxis;
			Assert::AreEqual(ZAxis.x, 0.0f);
			Assert::AreEqual(ZAxis.y, 0.0f);
			Assert::AreEqual(ZAxis.z, 1.0f);
		}

		TEST_METHOD(TestAdditions)
		{
			Vector3 a{ 1.0f, 2.0f, 3.0f };
			Vector3 b{ 4.0f, 5.0f, 6.0f };
			Vector3 c = a + b;
			Assert::AreEqual(c.x, 5.0f);
			Assert::AreEqual(c.y, 7.0f);
			Assert::AreEqual(c.z, 9.0f);
		}

	};
}