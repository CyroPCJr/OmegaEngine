#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Math;

namespace MathTest
{
	TEST_CLASS(Matrix4Test)
	{
	public:

		TEST_METHOD(IdentityMatrixTest)
		{
			Matrix4 ide = Matrix4::Identity;
			Assert::AreEqual(ide._11, 1.f);
			Assert::AreEqual(ide._12, 0.f);
			Assert::AreEqual(ide._13, 0.f);
			Assert::AreEqual(ide._14, 0.f);
			Assert::AreEqual(ide._21, 0.f);
			Assert::AreEqual(ide._22, 1.f);
			Assert::AreEqual(ide._23, 0.f);
			Assert::AreEqual(ide._24, 0.f);
			Assert::AreEqual(ide._31, 0.f);
			Assert::AreEqual(ide._32, 0.f);
			Assert::AreEqual(ide._33, 1.f);
			Assert::AreEqual(ide._34, 0.f);
			Assert::AreEqual(ide._41, 0.f);
			Assert::AreEqual(ide._42, 0.f);
			Assert::AreEqual(ide._43, 0.f);
			Assert::AreEqual(ide._44, 1.f);
		}

		TEST_METHOD(MultiplicationTest)
		{
			Matrix4 A{ 9.f, 2.f, 1.f, 9.f,
					5.f, 5.f, 7.f, 8.f,
					9.f, 7.f, 5.f, 10.f,
					1.f, 1.f, 2.f, 7.f };
			Matrix4 B{ 2.f, 3.f, 1.f, 9.f,
					1.f, 4.f, 9.f, 6.f,
					5.f, 9.f, 10.f, 7.f,
					7.f, 10.f, 6.f, 5.f };
			// operator *
			Matrix4 C =A* B;
			Assert::AreEqual(C._11, 88.f);
			Assert::AreEqual(C._12, 134.f);
			Assert::AreEqual(C._13, 91.f);
			Assert::AreEqual(C._14, 145.f);
							 
			Assert::AreEqual(C._21, 106.f);
			Assert::AreEqual(C._22, 178.f);
			Assert::AreEqual(C._23, 168.f);
			Assert::AreEqual(C._24, 164.f);

			Assert::AreEqual(C._31, 120.f);
			Assert::AreEqual(C._32, 200.f);
			Assert::AreEqual(C._33, 182.f);
			Assert::AreEqual(C._34, 208.f);

			Assert::AreEqual(C._41, 62.f);
			Assert::AreEqual(C._42, 95.f);
			Assert::AreEqual(C._43, 72.f);
			Assert::AreEqual(C._44, 64.f);

			// operator *=
			A *= B;
			Assert::AreEqual(A._11, 88.f);
			Assert::AreEqual(A._12, 134.f);
			Assert::AreEqual(A._13, 91.f);
			Assert::AreEqual(A._14, 145.f);
							 
			Assert::AreEqual(A._21, 106.f);
			Assert::AreEqual(A._22, 178.f);
			Assert::AreEqual(A._23, 168.f);
			Assert::AreEqual(A._24, 164.f);
							 
			Assert::AreEqual(A._31, 120.f);
			Assert::AreEqual(A._32, 200.f);
			Assert::AreEqual(A._33, 182.f);
			Assert::AreEqual(A._34, 208.f);
							 
			Assert::AreEqual(A._41, 62.f);
			Assert::AreEqual(A._42, 95.f);
			Assert::AreEqual(A._43, 72.f);
			Assert::AreEqual(A._44, 64.f);
		}

		TEST_METHOD(AdditionTest)
		{
			Matrix4 A{ 9.f, 2.f, 1.f, 9.f,
					5.f, 5.f, 7.f, 8.f,
					9.f, 7.f, 5.f, 10.f,
					1.f, 1.f, 2.f, 7.f };
			Matrix4 B{ 2.f, 3.f, 1.f, 9.f,
					1.f, 4.f, 9.f, 6.f,
					5.f, 9.f, 10.f, 7.f,
					7.f, 10.f, 6.f, 5.f };
			// operator +
			Matrix4 C = A + B;
			Assert::AreEqual(C._11, 11.f);
			Assert::AreEqual(C._12, 5.f);
			Assert::AreEqual(C._13, 2.f);
			Assert::AreEqual(C._14, 18.f);

			Assert::AreEqual(C._21, 6.f);
			Assert::AreEqual(C._22, 9.f);
			Assert::AreEqual(C._23, 16.f);
			Assert::AreEqual(C._24, 14.f);

			Assert::AreEqual(C._31, 14.f);
			Assert::AreEqual(C._32, 16.f);
			Assert::AreEqual(C._33, 15.f);
			Assert::AreEqual(C._34, 17.f);

			Assert::AreEqual(C._41, 8.f);
			Assert::AreEqual(C._42, 11.f);
			Assert::AreEqual(C._43, 8.f);
			Assert::AreEqual(C._44, 12.f);
			// operator +=
			A += B;
			Assert::AreEqual(A._11, 11.f);
			Assert::AreEqual(A._12, 5.f);
			Assert::AreEqual(A._13, 2.f);
			Assert::AreEqual(A._14, 18.f);
							 
			Assert::AreEqual(A._21, 6.f);
			Assert::AreEqual(A._22, 9.f);
			Assert::AreEqual(A._23, 16.f);
			Assert::AreEqual(A._24, 14.f);
							 
			Assert::AreEqual(A._31, 14.f);
			Assert::AreEqual(A._32, 16.f);
			Assert::AreEqual(A._33, 15.f);
			Assert::AreEqual(A._34, 17.f);
							 
			Assert::AreEqual(A._41, 8.f);
			Assert::AreEqual(A._42, 11.f);
			Assert::AreEqual(A._43, 8.f);
			Assert::AreEqual(A._44, 12.f);
		}

		TEST_METHOD(SubtractionTest)
		{
			Matrix4 A{ 9.f, 2.f, 1.f, 9.f,
					5.f, 5.f, 7.f, 8.f,
					9.f, 7.f, 5.f, 10.f,
					1.f, 1.f, 2.f, 7.f };
			Matrix4 B{ 2.f, 3.f, 1.f, 9.f,
					1.f, 4.f, 9.f, 6.f,
					5.f, 9.f, 10.f, 7.f,
					7.f, 10.f, 6.f, 5.f };
			// operator -
			Matrix4 C = A - B;
			Assert::AreEqual(C._11, 7.f);
			Assert::AreEqual(C._12, -1.f);
			Assert::AreEqual(C._13, 0.f);
			Assert::AreEqual(C._14, 0.f);

			Assert::AreEqual(C._21, 4.f);
			Assert::AreEqual(C._22, 1.f);
			Assert::AreEqual(C._23, -2.f);
			Assert::AreEqual(C._24, 2.f);

			Assert::AreEqual(C._31, 4.f);
			Assert::AreEqual(C._32, -2.f);
			Assert::AreEqual(C._33, -5.f);
			Assert::AreEqual(C._34, 3.f);

			Assert::AreEqual(C._41, -6.f);
			Assert::AreEqual(C._42, -9.f);
			Assert::AreEqual(C._43, -4.f);
			Assert::AreEqual(C._44, 2.f);

			// operator -=
			A -= B;
			Assert::AreEqual(A._11, 7.f);
			Assert::AreEqual(A._12, -1.f);
			Assert::AreEqual(A._13, 0.f);
			Assert::AreEqual(A._14, 0.f);
							 
			Assert::AreEqual(A._21, 4.f);
			Assert::AreEqual(A._22, 1.f);
			Assert::AreEqual(A._23, -2.f);
			Assert::AreEqual(A._24, 2.f);
							 
			Assert::AreEqual(A._31, 4.f);
			Assert::AreEqual(A._32, -2.f);
			Assert::AreEqual(A._33, -5.f);
			Assert::AreEqual(A._34, 3.f);
							 
			Assert::AreEqual(A._41, -6.f);
			Assert::AreEqual(A._42, -9.f);
			Assert::AreEqual(A._43, -4.f);
			Assert::AreEqual(A._44, 2.f);
		}

	};
}