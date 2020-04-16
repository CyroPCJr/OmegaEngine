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
			Assert::AreEqual(q0.w, 0.0f);

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
			//TODO TEstar
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
			Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
			Quaternion q1 = Normalize(q0);

			Assert::AreEqual(q1.x, 0.1825742f, tolerance);
			Assert::AreEqual(q1.y, 0.3651484f, tolerance);
			Assert::AreEqual(q1.z, 0.5477226f, tolerance);
			Assert::AreEqual(q1.w, 0.7302967f, tolerance);
		}

		TEST_METHOD(TestSlerp)
		{
			Quaternion q0 = Quaternion::RotationAxis({ 1.0f, 2.0f, 3.0f }, 4.0f);
			Quaternion q1 = Quaternion::RotationAxis({ 1.0f, -1.0f, 2.0f }, -2.0f);
			Quaternion q2 = Slerp(q0, q1, 0.47f);

			Assert::AreEqual(q2.x, 0.320419908f, tolerance);
			Assert::AreEqual(q2.y, 0.104300126f, tolerance);
			Assert::AreEqual(q2.z, 0.782413125f, tolerance);
			Assert::AreEqual(q2.w, -0.523719609f, tolerance);
		}
	};
}