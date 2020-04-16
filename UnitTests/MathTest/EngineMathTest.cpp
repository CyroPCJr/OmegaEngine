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
			Vector3 a{ 3.0f, 5.0f, 4.0f };
			Vector3 b{ 2.0f, 7.0f, 5.0f };
			const Vector3 res = Cross(a, b);
			Assert::AreEqual(res.x, -3.0f);
			Assert::AreEqual(res.y, -7.0f);
			Assert::AreEqual(res.z, 11.0f);
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

		TEST_METHOD(InverseMatrixTest)
		{
			/*
				actual:
				3 7 3 6
				7 1 9 9
				9 8 3 6
				6 8 2 10

				expected:
				-19/94	1/94	15/94	3/188
				10/47	-3/47	2/47	-9/94
				193/846	23/282	1/846	-119/564
				-40/423	4/141	-55/423	59/282
			*/
			Matrix4 matrix{ 3.f, 7.f, 3.f, 6.f,
							7.f, 1.f, 9.f, 9.f,
							9.f, 8.f, 3.f, 6.f,
							6.f, 8.f, 2.f, 10.f };
			const Matrix4 inverseResult = Inverse(matrix);
			Assert::AreEqual(inverseResult._11, -0.202127665f);
			Assert::AreEqual(inverseResult._12, 0.0106382975f);
			Assert::AreEqual(inverseResult._13, 0.159574464f);
			Assert::AreEqual(inverseResult._14, 0.0159574468f);

			Assert::AreEqual(inverseResult._21, 0.212765962f);
			Assert::AreEqual(inverseResult._22, -0.0638297871f);
			Assert::AreEqual(inverseResult._23, 0.0425531901f);
			Assert::AreEqual(inverseResult._24, -0.0957446843f);

			Assert::AreEqual(inverseResult._31, 0.228132382f);
			Assert::AreEqual(inverseResult._32, 0.0815602839f);
			Assert::AreEqual(inverseResult._33, 0.00118203310f);
			Assert::AreEqual(inverseResult._34, -0.210992903f);

			Assert::AreEqual(inverseResult._41, -0.0945626497f);
			Assert::AreEqual(inverseResult._42, 0.0283687934f);
			Assert::AreEqual(inverseResult._43, -0.130023643f);
			Assert::AreEqual(inverseResult._44, 0.209219858f);
		}
	};
}
