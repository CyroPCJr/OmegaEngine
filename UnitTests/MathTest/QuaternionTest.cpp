#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Omega::Math;

namespace MathTest
{
	TEST_CLASS(QuaterionTest)
	{
	public:

		const float tolerance = 0.000001f;

		TEST_METHOD(TestConstructor)
		{
			Quaternion q0;
			Assert::AreEqual(q0.x, 0.0f);
			Assert::AreEqual(q0.y, 0.0f);
			Assert::AreEqual(q0.z, 0.0f);
			Assert::AreEqual(q0.w, 1.0f);

			Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
			Assert::AreEqual(q1.x, 1.0f);
			Assert::AreEqual(q1.y, 2.0f);
			Assert::AreEqual(q1.z, 3.0f);
			Assert::AreEqual(q1.w, 4.0f);
		}

		TEST_METHOD(TestStatics)
		{
			Quaternion zero = Quaternion::Zero;
			Assert::AreEqual(zero.x, 0.0f);
			Assert::AreEqual(zero.y, 0.0f);
			Assert::AreEqual(zero.z, 0.0f);
			Assert::AreEqual(zero.w, 0.0f);

			Quaternion identity = Quaternion::Identity;
			Assert::AreEqual(identity.x, 0.0f);
			Assert::AreEqual(identity.y, 0.0f);
			Assert::AreEqual(identity.z, 0.0f);
			Assert::AreEqual(identity.w, 1.0f);
		}

		TEST_METHOD(TestNegation)
		{
			Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
			Quaternion q1 = -q0;

			Assert::AreEqual(q1.x, -1.0f);
			Assert::AreEqual(q1.y, -2.0f);
			Assert::AreEqual(q1.z, -3.0f);
			Assert::AreEqual(q1.w, -4.0f);
		}

		TEST_METHOD(TestAddition)
		{
			Quaternion q0(1.0f, 1.0f, 1.0f, 1.5f);
			Quaternion q1(1.0f, -1.0f, 0.0f, -0.5f);
			Quaternion q2 = q0 + q1;

			Assert::AreEqual(q2.x, 2.0f);
			Assert::AreEqual(q2.y, 0.0f);
			Assert::AreEqual(q2.z, 1.0f);
			Assert::AreEqual(q2.w, 1.0f);
		}

		TEST_METHOD(TestSubtraction)
		{
			Quaternion q0(1.0f, 1.0f, 1.0f, 1.5f);
			Quaternion q1(1.0f, -1.0f, 0.0f, -0.5f);
			Quaternion q2 = q0 - q1;

			Assert::AreEqual(q2.x, 0.0f);
			Assert::AreEqual(q2.y, 2.0f);
			Assert::AreEqual(q2.z, 1.0f);
			Assert::AreEqual(q2.w, 2.0f);
		}

		TEST_METHOD(TestScalarMultiply)
		{
			Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
			Quaternion q1 = q0 * 0.5f;

			Assert::AreEqual(q1.x, 0.5f);
			Assert::AreEqual(q1.y, 1.0f);
			Assert::AreEqual(q1.z, 1.5f);
			Assert::AreEqual(q1.w, 2.0f);
		}

		TEST_METHOD(TestMultiply)
		{
			Quaternion q0(1.0f, 1.0f, 1.0f, 1.5f);
			Quaternion q1(1.0f, -1.0f, 0.0f, -0.5f);
			Quaternion q2 = q0 * q1;

			Assert::AreEqual(q2.x, 2.0f);
			Assert::AreEqual(q2.y, -1.0f);
			Assert::AreEqual(q2.z, -2.5f);
			Assert::AreEqual(q2.w, -0.75f);
		}

		TEST_METHOD(TestConjugate)
		{
			Quaternion q(1.0f, 1.0f, 1.0f, 1.5f);
			Quaternion result = q.Conjugate();

			Assert::AreEqual(result.x, -1.0f);
			Assert::AreEqual(result.y, -1.0f);
			Assert::AreEqual(result.z, -1.0f);
			Assert::AreEqual(result.w, 1.5f);
		}

		TEST_METHOD(TestFromAxisAngle)
		{
			Quaternion q0 = Quaternion::RotationAxis({ 1.0f, -1.0f, 2.0f }, 1.5f);

			Assert::AreEqual(q0.x, 0.2782779f, tolerance);
			Assert::AreEqual(q0.y, -0.2782779f, tolerance);
			Assert::AreEqual(q0.z, 0.5565557f, tolerance);
			Assert::AreEqual(q0.w, 0.7316889f, tolerance);
		}

		TEST_METHOD(TestFromMatrix)
		{
			Quaternion qx = Quaternion::RotationMatrix(Matrix4::RotationX(0.72f));
			Quaternion qy = Quaternion::RotationMatrix(Matrix4::RotationY(0.84f));
			Quaternion qz = Quaternion::RotationMatrix(Matrix4::RotationZ(0.96f));
			Quaternion qa = Quaternion::RotationMatrix(Matrix4::RotationAxis({ 3.0f, -2.0f, 1.0f }, 0.44f));

			Assert::AreEqual(qx.x, 0.3522742f, tolerance);
			Assert::AreEqual(qx.y, 0.0f, tolerance);
			Assert::AreEqual(qx.z, 0.0f, tolerance);
			Assert::AreEqual(qx.w, 0.9358968f, tolerance);

			Assert::AreEqual(qy.x, 0.0f, tolerance);
			Assert::AreEqual(qy.y, 0.4077605f, tolerance);
			Assert::AreEqual(qy.z, 0.0f, tolerance);
			Assert::AreEqual(qy.w, 0.9130889f, tolerance);

			Assert::AreEqual(qz.x, 0.0f, tolerance);
			Assert::AreEqual(qz.y, 0.0f, tolerance);
			Assert::AreEqual(qz.z, 0.4617792f, tolerance);
			Assert::AreEqual(qz.w, 0.8869949f, tolerance);

			Assert::AreEqual(qa.x, 0.174973f, tolerance);
			Assert::AreEqual(qa.y, -0.1166486f, tolerance);
			Assert::AreEqual(qa.z, 0.0583243f, tolerance);
			Assert::AreEqual(qa.w, 0.9758974f, tolerance);
		}

		TEST_METHOD(TestFromLook)
		{
			Quaternion q0 = Quaternion::RotationLook({ 1.0f, 1.0f, 1.0f });

			Assert::AreEqual(q0.x, -0.279848129f, 0.000001f);
			Assert::AreEqual(q0.y, 0.364705175f, 0.000001f);
			Assert::AreEqual(q0.z, 0.115916900f, 0.000001f);
			Assert::AreEqual(q0.w, 0.880476236f, 0.000001f);
		}

		TEST_METHOD(TestFromFromTo)
		{
			Quaternion q0 = Quaternion::RotationFromTo({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });

			Assert::AreEqual(q0.x, -0.325057596f, tolerance);
			Assert::AreEqual(q0.y, 0.325057596f, tolerance);
			Assert::AreEqual(q0.z, 0.000000000f, tolerance);
			Assert::AreEqual(q0.w, 0.888073862f, tolerance);
		}

		TEST_METHOD(TestToMatrix)
		{
			Vector3 axis{ -1.0f, 1.0f, 1.0f };
			float angle = 0.45f;
			Matrix4 m0 = Matrix4::RotationQuaternion(Quaternion::RotationAxis(axis, angle));
			Matrix4 m1 = Matrix4::RotationAxis(axis, angle);

			Assert::AreEqual(m0._11, m1._11, tolerance);
			Assert::AreEqual(m0._12, m1._12, tolerance);
			Assert::AreEqual(m0._13, m1._13, tolerance);
			Assert::AreEqual(m0._14, m1._14, tolerance);

			Assert::AreEqual(m0._21, m1._21, tolerance);
			Assert::AreEqual(m0._22, m1._22, tolerance);
			Assert::AreEqual(m0._23, m1._23, tolerance);
			Assert::AreEqual(m0._24, m1._24, tolerance);

			Assert::AreEqual(m0._31, m1._31, tolerance);
			Assert::AreEqual(m0._32, m1._32, tolerance);
			Assert::AreEqual(m0._33, m1._33, tolerance);
			Assert::AreEqual(m0._34, m1._34, tolerance);

			Assert::AreEqual(m0._41, m1._41, tolerance);
			Assert::AreEqual(m0._42, m1._42, tolerance);
			Assert::AreEqual(m0._43, m1._43, tolerance);
			Assert::AreEqual(m0._44, m1._44, tolerance);

			for (size_t i = 0; i < std::size(m0.v); ++i)
			{
				Assert::AreEqual(m0.v[i], m1.v[i], tolerance);
			}
		}

		TEST_METHOD(TestMagitude)
		{
			Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
			float magnitude = Magnitude(q0);

			Assert::AreEqual(magnitude, 5.47722578f, tolerance);
		}

		TEST_METHOD(TestNormalize)
		{
			// Case 1
			Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
			Quaternion q1 = Normalize(q0);

			Assert::AreEqual(q1.x, 0.1825742f, tolerance);
			Assert::AreEqual(q1.y, 0.3651484f, tolerance);
			Assert::AreEqual(q1.z, 0.5477226f, tolerance);
			Assert::AreEqual(q1.w, 0.7302967f, tolerance);

			// Case 2
			q0 = Quaternion(0.4f, 0.2f, -1.3f, -0.5f);
			q1 = Normalize(q0);
			Assert::AreEqual(q1.x, 0.2734343708f, tolerance);
			Assert::AreEqual(q1.y, 0.1367171854f, tolerance);
			Assert::AreEqual(q1.z, -0.888661705f, tolerance);
			Assert::AreEqual(q1.w, -0.3417929635f, tolerance);

			// Case 3
			q0 = Quaternion(0.f, 0.f, 0.f, 0.2f);
			q1 = Normalize(q0);
			Assert::AreEqual(q1.x, 0.f, tolerance);
			Assert::AreEqual(q1.y, 0.f, tolerance);
			Assert::AreEqual(q1.z, 0.f, tolerance);
			Assert::AreEqual(q1.w, 1.f, tolerance);

			// Case 4
			q0 = Quaternion(0.5f, 0.5f, -0.5f, 0.5f);
			q1 = Normalize(q0);
			Assert::AreEqual(q1.x, 0.5f, tolerance);
			Assert::AreEqual(q1.y, 0.5f, tolerance);
			Assert::AreEqual(q1.z, -0.5f, tolerance);
			Assert::AreEqual(q1.w, 0.5f, tolerance);
		}

		TEST_METHOD(TestLerp)
		{
			// Case 1
			Quaternion q1(-27.0f, 83.0f, 32.0f, -153.0f);
			Quaternion q2(36.0f, -64.0f, 12.0f, 24.0f);
			Quaternion q = Lerp(q1, q2, 0.25f);

			Assert::AreEqual(q.x, -0.1972026f, tolerance);
			Assert::AreEqual(q.y, 0.5275592f, tolerance);
			Assert::AreEqual(q.z, 0.1415814f, tolerance);
			Assert::AreEqual(q.w, -0.8140929f, tolerance);

			// Case 2
			q1 = Quaternion(0.3535534f, -0.1464466f, 0.3535534f, 0.8535535f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = Lerp(q1, q2, 1.38f);
			Assert::AreEqual(q.x, 0.3919183f, tolerance);
			Assert::AreEqual(q.y, 0.3196269f, tolerance);
			Assert::AreEqual(q.z, -0.8430416f, tolerance);
			Assert::AreEqual(q.w, -0.1830837f, tolerance);

			// Case 3
			q1 = Quaternion(0.3535534f, -0.1464466f, 0.3535534f, 0.8535535f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = Lerp(q1, q2, 0.f);
			Assert::AreEqual(q.x, 0.3535534f, tolerance);
			Assert::AreEqual(q.y, -0.1464466f, tolerance);
			Assert::AreEqual(q.z, 0.3535534f, tolerance);
			Assert::AreEqual(q.w, 0.8535534f, tolerance);

			// Case 4
			q1 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q2 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q = Lerp(q1, q2, -0.32f);
			Assert::AreEqual(q.x, 0.f, tolerance);
			Assert::AreEqual(q.y, 0.7071068f, tolerance);
			Assert::AreEqual(q.z, 0.f, tolerance);
			Assert::AreEqual(q.w, 0.7071068f, tolerance);
		}

		TEST_METHOD(TestLerpUnclamped)
		{
			// Case 1
			Quaternion q1 = Quaternion(-27.f, 83.f, 32.f, -153.f);
			Quaternion q2 = Quaternion(36.f, -64.f, 12.f, 24.f);
			Quaternion q = LerpUnclamped(q1, q2, 0.25f);

			Assert::AreEqual(q.x, -0.1972026f, tolerance);
			Assert::AreEqual(q.y, 0.5275592f, tolerance);
			Assert::AreEqual(q.z, 0.1415814f, tolerance);
			Assert::AreEqual(q.w, -0.8140929f, tolerance);

			// Case 2
			q1 = Quaternion(0.3535534f, -0.1464466f, 0.3535534f, 0.8535535f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = LerpUnclamped(q1, q2, 1.38f);
			Assert::AreEqual(q.x, -0.5227136f, tolerance);
			Assert::AreEqual(q.y, -0.2983902f, tolerance);
			Assert::AreEqual(q.z, 0.7966512f, tolerance);
			Assert::AreEqual(q.w, -0.05550352f, tolerance);

			// Case 3
			q1 = Quaternion(0.3535534f, -0.1464466f, 0.3535534f, 0.8535535f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = LerpUnclamped(q1, q2, 0.f);
			Assert::AreEqual(q.x, 0.3535534f, tolerance);
			Assert::AreEqual(q.y, -0.1464466f, tolerance);
			Assert::AreEqual(q.z, 0.3535534f, tolerance);
			Assert::AreEqual(q.w, 0.8535534f, tolerance);

			// Case 4
			q1 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q2 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q = LerpUnclamped(q1, q2, -0.32f);
			Assert::AreEqual(q.x, 0.f, tolerance);
			Assert::AreEqual(q.y, 0.7071068f, tolerance);
			Assert::AreEqual(q.z, 0.f, tolerance);
			Assert::AreEqual(q.w, 0.7071068f, tolerance);

			// Case 5
			q1 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = LerpUnclamped(q1, q2, -1.73f);
			Assert::AreEqual(q.x, -0.219588f, tolerance);
			Assert::AreEqual(q.y, 0.4461099f, tolerance);
			Assert::AreEqual(q.z, 0.4723479f, tolerance);
			Assert::AreEqual(q.w, 0.7277737f, tolerance);
		}

		TEST_METHOD(TestSlerp)
		{
			// Case 1
			Quaternion q1 = Quaternion::RotationAxis({ 1.0f, 2.0f, 3.0f }, 4.0f);
			Quaternion q2 = Quaternion::RotationAxis({ 1.0f, -1.0f, 2.0f }, -2.0f);
			Quaternion q = Slerp(q1, q2, 0.47f);

			Assert::AreEqual(q.x, 0.320419908f, tolerance);
			Assert::AreEqual(q.y, 0.104300126f, tolerance);
			Assert::AreEqual(q.z, 0.782413125f, tolerance);
			Assert::AreEqual(q.w, -0.523719609f, tolerance);

			// Case 2
			q1 = Quaternion(-27.0f, 83.0f, 32.0f, -153.0f);
			q2 = Quaternion(36.0f, -64.0f, 12.0f, 24.0f);
			q = Slerp(q1, q2, 0.25f);

			Assert::AreEqual(q.x, -0.1972026f, tolerance);
			Assert::AreEqual(q.y, 0.5275592f, tolerance);
			Assert::AreEqual(q.z, 0.1415814f, tolerance);
			Assert::AreEqual(q.w, -0.8140929f, tolerance);

			// Case 3
			q1 = Quaternion(0.3535534f, -0.1464466f, 0.3535534f, 0.8535535f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = Slerp(q1, q2, 1.38f);

			Assert::AreEqual(q.x, 0.3919183f, tolerance);
			Assert::AreEqual(q.y, 0.3196269f, tolerance);
			Assert::AreEqual(q.z, -0.8430416f, tolerance);
			Assert::AreEqual(q.w, -0.1830837f, tolerance);

			// Case 4
			q1 = Quaternion(0.3535534f, -0.1464466f, 0.3535534f, 0.8535535f);
			q2 = Quaternion(0.3919183f, 0.3196269f, -0.8430416f, -0.1830837f);
			q = Slerp(q1, q2, 0.f);

			Assert::AreEqual(q.x, 0.3535534f, tolerance);
			Assert::AreEqual(q.y, -0.1464466f, tolerance);
			Assert::AreEqual(q.z, 0.3535534f, tolerance);
			Assert::AreEqual(q.w, 0.8535534f, tolerance);

			// Case 5
			q1 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q2 = Quaternion(0.f, 0.7071068f, 0.f, 0.7071068f);
			q = Slerp(q1, q2, -0.32f);

			Assert::AreEqual(q.x, 0.f, tolerance);
			Assert::AreEqual(q.y, 0.7071068f, tolerance);
			Assert::AreEqual(q.z, 0.f, tolerance);
			Assert::AreEqual(q.w, 0.7071068f, tolerance);

		}
	};
}