#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Math;

namespace MathTest
{
	TEST_CLASS(EngineMathTest)
	{
	public:

		TEST_METHOD(DotTest)
		{
			Vector3 a{ 3.f,5.f,4.f };
			Vector3 b{ 2.f,7.f,5.f };
			const float res = Dot(a, b);
			Assert::AreEqual(res, 61.f);
		}

		TEST_METHOD(CrossTest)
		{
			Vector3 a{ 3.f,5.f,4.f };
			Vector3 b{ 2.f,7.f,5.f };
			const Vector3 res = Cross(a, b);
			Assert::AreEqual(res.x, -3.f);
			Assert::AreEqual(res.y, 7.f);
			Assert::AreEqual(res.z, 11.f);
		}

		TEST_METHOD(MagnitudeTest)
		{
			Vector3 a{ 2.f,5.f,4.f };
			const float mag = Magnitude(a);
			Assert::AreEqual(mag, 6.70820379f);
		}

		TEST_METHOD(MagnitudeSqrTest)
		{
			Vector3 a{ 2.f,5.f,4.f };
			const float mag = MagnitudeSqr(a);
			Assert::AreEqual(mag, 45.f);
		}

		TEST_METHOD(NormalizeTest)
		{
			Vector3 a{ 2.f,5.f,4.f };
			const Vector3 b = Normalize(a);
			Assert::AreEqual(b.x, 0.29814240f);
			Assert::AreEqual(b.y, 0.745356023f);
			Assert::AreEqual(b.z, 0.596284807f);
		}

		TEST_METHOD(TransposeTest)
		{
			Matrix4 originalMatrix = { 1.f, 2.f, 3.f, 4.f,
									  5.f, 6.f, 7.f, 8.f,
									  9.f, 10.f, 11.f, 12.f,
									  13.f, 14.f, 15.f, 16.f };
			Matrix4 matrixTransposed = Transpose(originalMatrix);
			Assert::AreEqual(matrixTransposed._11, 1.f);
			Assert::AreEqual(matrixTransposed._12, 5.f);
			Assert::AreEqual(matrixTransposed._13, 9.f);
			Assert::AreEqual(matrixTransposed._14, 13.f);

			Assert::AreEqual(matrixTransposed._21, 2.f);
			Assert::AreEqual(matrixTransposed._22, 6.f);
			Assert::AreEqual(matrixTransposed._23, 10.f);
			Assert::AreEqual(matrixTransposed._24, 14.f);

			Assert::AreEqual(matrixTransposed._31, 3.f);
			Assert::AreEqual(matrixTransposed._32, 7.f);
			Assert::AreEqual(matrixTransposed._33, 11.f);
			Assert::AreEqual(matrixTransposed._34, 15.f);

			Assert::AreEqual(matrixTransposed._41, 4.f);
			Assert::AreEqual(matrixTransposed._42, 8.f);
			Assert::AreEqual(matrixTransposed._43, 12.f);
			Assert::AreEqual(matrixTransposed._44, 16.f);
		}

		TEST_METHOD(DeterminantTest)
		{
			Matrix4 A{ 1.f, 0.f, 2.f, -1.f,
						3.f, 0.f, 0.f, 5.f,
						2.f, 1.f, 4.f, -3.f,
						1.f, 0.f, 5.f, 0.f };
			const float det = Determinant(A);
			Assert::AreEqual(det, 30.f);

		}
	};
}
