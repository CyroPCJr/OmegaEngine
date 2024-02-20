#include "pch.h"
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
			const Vector3 zero = Vector3::Zero;
			Assert::AreEqual(zero.x, 0.0f);
			Assert::AreEqual(zero.y, 0.0f);
			Assert::AreEqual(zero.z, 0.0f);

			const Vector3 one = Vector3::One;
			Assert::AreEqual(one.x, 1.0f);
			Assert::AreEqual(one.y, 1.0f);
			Assert::AreEqual(one.z, 1.0f);

			const Vector3 XAxis = Vector3::XAxis;
			Assert::AreEqual(XAxis.x, 1.0f);
			Assert::AreEqual(XAxis.y, 0.0f);
			Assert::AreEqual(XAxis.z, 0.0f);

			const Vector3 YAxis = Vector3::YAxis;
			Assert::AreEqual(YAxis.x, 0.0f);
			Assert::AreEqual(YAxis.y, 1.0f);
			Assert::AreEqual(YAxis.z, 0.0f);

			const Vector3 ZAxis = Vector3::ZAxis;
			Assert::AreEqual(ZAxis.x, 0.0f);
			Assert::AreEqual(ZAxis.y, 0.0f);
			Assert::AreEqual(ZAxis.z, 1.0f);
		}

		TEST_METHOD(TestAdditions)
		{
			// operator +
			const Vector3 a{ 1.0f, 2.0f, 3.0f };
			Vector3 b{ 4.0f, 5.0f, 6.0f };
			const Vector3 c = a + b;
			Assert::AreEqual(c.x, 5.0f);
			Assert::AreEqual(c.y, 7.0f);
			Assert::AreEqual(c.z, 9.0f);

			// operator +=
			b += a;
			Assert::AreEqual(b.x, 5.0f);
			Assert::AreEqual(b.y, 7.0f);
			Assert::AreEqual(b.z, 9.0f);
		}

		TEST_METHOD(TestSubraction)
		{
			// operator -
			Vector3 a{ 1.0f, 2.0f, 3.0f };
			const Vector3 b{ 4.0f, 5.0f, 6.0f };
			const Vector3 c = a - b;
			Assert::AreEqual(c.x, -3.0f);
			Assert::AreEqual(c.y, -3.0f);
			Assert::AreEqual(c.z, -3.0f);

			// operator -=
			a -= b;
			Assert::AreEqual(a.x, -3.0f);
			Assert::AreEqual(a.y, -3.0f);
			Assert::AreEqual(a.z, -3.0f);

		}

		TEST_METHOD(TestMultiplication)
		{
			// operator *
			Vector3 a{ 1.0f, 2.0f, 3.0f };
			const Vector3 b{ 4.0f, 5.0f, 6.0f };
			const Vector3 c = a * b;
			Assert::AreEqual(c.x, 4.0f);
			Assert::AreEqual(c.y, 10.0f);
			Assert::AreEqual(c.z, 18.0f);

			const Vector3 result = a * 2.0f;
			Assert::AreEqual(result.x, 2.0f);
			Assert::AreEqual(result.y, 4.0f);
			Assert::AreEqual(result.z, 6.0f);

			// operator *=
			a *= b;
			Assert::AreEqual(c.x, 4.0f);
			Assert::AreEqual(c.y, 10.0f);
			Assert::AreEqual(c.z, 18.0f);
		}

		TEST_METHOD(TestDivision)
		{
			// operator / 
			Vector3 a{ 1.0f, 2.0f, 3.0f };
			const Vector3 b{ 4.0f, 5.0f, 6.0f };
			const Vector3 c = a / b;
			Assert::AreEqual(c.x, 0.25f);
			Assert::AreEqual(c.y, 0.4f);
			Assert::AreEqual(c.z, 0.5f);

			const Vector3 result = a / 1.f;
			Assert::AreEqual(result.x, 1.f);
			Assert::AreEqual(result.y, 2.f);
			Assert::AreEqual(result.z, 3.f);

			// operator /=
			a /= b;
			Assert::AreEqual(a.x, 0.25f);
			Assert::AreEqual(a.y, 0.4f);
			Assert::AreEqual(a.z, 0.5f);
		}

	};
}