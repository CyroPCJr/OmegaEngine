#pragma once
// const for PI
constexpr float M_PI = 3.14159265358979323846264338327950288f;

namespace Omega::Math
{

	struct Matrix4
	{
		// row + collum subscripts
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;

		const static Matrix4 Identity;

#pragma region operator overload

		constexpr Matrix4& operator=(const Matrix4& m)
		{
			_11 = m._11;
			_12 = m._12;
			_13 = m._13;
			_14 = m._14;

			_21 = m._21;
			_22 = m._22;
			_23 = m._23;
			_24 = m._24;

			_31 = m._31;
			_32 = m._32;
			_33 = m._33;
			_34 = m._34;

			_41 = m._41;
			_42 = m._42;
			_43 = m._43;
			_44 = m._44;
			return *this;
		}

		constexpr bool operator==(const Matrix4& m) const
		{
			return (_11 == m._11) &&
				(_12 == m._12) &&
				(_13 == m._13) &&
				(_14 == m._14) &&
				(_21 == m._21) &&
				(_22 == m._22) &&
				(_23 == m._23) &&
				(_24 == m._24) &&
				(_31 == m._31) &&
				(_32 == m._32) &&
				(_33 == m._33) &&
				(_34 == m._34) &&
				(_41 == m._41) &&
				(_42 == m._42) &&
				(_43 == m._43) &&
				(_44 == m._44);
		}

		inline Matrix4 operator*(const Matrix4& m)
		{
			Matrix4 aux;
			aux._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31) + (_14 * m._41);
			aux._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32) + (_14 * m._42);
			aux._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33) + (_14 * m._43);
			aux._14 = (_11 * m._14) + (_12 * m._24) + (_13 * m._34) + (_14 * m._44);

			aux._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31) + (_24 * m._41);
			aux._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32) + (_24 * m._42);
			aux._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33) + (_24 * m._43);
			aux._24 = (_21 * m._14) + (_22 * m._24) + (_23 * m._34) + (_24 * m._44);

			aux._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31) + (_34 * m._41);
			aux._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32) + (_34 * m._42);
			aux._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33) + (_34 * m._43);
			aux._34 = (_31 * m._14) + (_32 * m._24) + (_33 * m._34) + (_34 * m._44);

			aux._41 = (_41 * m._11) + (_42 * m._21) + (_43 * m._31) + (_44 * m._41);
			aux._42 = (_41 * m._12) + (_42 * m._22) + (_43 * m._32) + (_44 * m._42);
			aux._43 = (_41 * m._13) + (_42 * m._23) + (_43 * m._33) + (_44 * m._43);
			aux._44 = (_41 * m._14) + (_42 * m._24) + (_43 * m._34) + (_44 * m._44);

			return aux;
		}

		inline Matrix4 operator*=(const Matrix4& m)
		{
			Matrix4 aux;
			aux._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31) + (_14 * m._41);
			aux._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32) + (_14 * m._42);
			aux._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33) + (_14 * m._43);
			aux._14 = (_11 * m._14) + (_12 * m._24) + (_13 * m._34) + (_14 * m._44);

			aux._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31) + (_24 * m._41);
			aux._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32) + (_24 * m._42);
			aux._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33) + (_24 * m._43);
			aux._24 = (_21 * m._14) + (_22 * m._24) + (_23 * m._34) + (_24 * m._44);

			aux._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31) + (_34 * m._41);
			aux._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32) + (_34 * m._42);
			aux._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33) + (_34 * m._43);
			aux._34 = (_31 * m._14) + (_32 * m._24) + (_33 * m._34) + (_34 * m._44);

			aux._41 = (_41 * m._11) + (_42 * m._21) + (_43 * m._31) + (_44 * m._41);
			aux._42 = (_41 * m._12) + (_42 * m._22) + (_43 * m._32) + (_44 * m._42);
			aux._43 = (_41 * m._13) + (_42 * m._23) + (_43 * m._33) + (_44 * m._43);
			aux._44 = (_41 * m._14) + (_42 * m._24) + (_43 * m._34) + (_44 * m._44);

			_11 = aux._11; _12 = aux._12; _13 = aux._13; _14 = aux._14;
			_21 = aux._21; _22 = aux._22; _23 = aux._23; _24 = aux._24;
			_31 = aux._31; _32 = aux._32; _33 = aux._33; _34 = aux._34;
			_41 = aux._41; _42 = aux._42; _43 = aux._43; _44 = aux._44;
			return *this;
		}

		constexpr Matrix4 operator*(const float v)
		{
			_11 *= v; _12 *= v; _13 *= v; _14 *= v;
			_21 *= v; _22 *= v; _23 *= v; _24 *= v;
			_31 *= v; _32 *= v; _33 *= v; _34 *= v;
			_41 *= v; _42 *= v; _43 *= v; _44 *= v;
			return *this;
		}

		inline Matrix4 operator+(const Matrix4& m)
		{
			Matrix4 aux;
			aux._11 = (_11 + m._11); aux._12 = (_12 + m._12); aux._13 = (_13 + m._13); aux._14 = (_14 + m._14);
			aux._21 = (_21 + m._21); aux._22 = (_22 + m._22); aux._23 = (_23 + m._23); aux._24 = (_24 + m._24);
			aux._31 = (_31 + m._31); aux._32 = (_32 + m._32); aux._33 = (_33 + m._33); aux._34 = (_34 + m._34);
			aux._41 = (_41 + m._41); aux._42 = (_42 + m._42); aux._43 = (_43 + m._43); aux._44 = (_44 + m._44);
			return aux;
		}

		constexpr Matrix4 operator+=(const Matrix4& m)
		{
			_11 += m._11; _12 += m._12; _13 += m._13; _14 += m._14;
			_21 += m._21; _22 += m._22; _23 += m._23; _24 += m._24;
			_31 += m._31; _32 += m._32; _33 += m._33; _34 += m._34;
			_41 += m._41; _42 += m._42; _43 += m._43; _44 += m._44;
			return *this;
		}

		inline Matrix4 operator-(const Matrix4& m)
		{
			Matrix4 aux;
			aux._11 = (_11 - m._11); aux._12 = (_12 - m._12); aux._13 = (_13 - m._13); aux._14 = (_14 - m._14);
			aux._21 = (_21 - m._21); aux._22 = (_22 - m._22); aux._23 = (_23 - m._23); aux._24 = (_24 - m._24);
			aux._31 = (_31 - m._31); aux._32 = (_32 - m._32); aux._33 = (_33 - m._33); aux._34 = (_34 - m._34);
			aux._41 = (_41 - m._41); aux._42 = (_42 - m._42); aux._43 = (_43 - m._43); aux._44 = (_44 - m._44);
			return aux;
		}

		constexpr Matrix4 operator-=(const Matrix4& m)
		{
			_11 -= m._11; _12 -= m._12; _13 -= m._13; _14 -= m._14;
			_21 -= m._21; _22 -= m._22; _23 -= m._23; _24 -= m._24;
			_31 -= m._31; _32 -= m._32; _33 -= m._33; _34 -= m._34;
			_41 -= m._41; _42 -= m._42; _43 -= m._43; _44 -= m._44;
			return *this;
		}

#pragma endregion

		constexpr bool isIdentity() const
		{
			return (_11 == 1.f) && (_22 == 1.f) && (_33 == 1.f) && (_44 == 1.f) &&
				(_12 == 0.f) &&
				(_13 == 0.f) &&
				(_14 == 0.f) &&
				(_21 == 0.f) &&
				(_23 == 0.f) &&
				(_24 == 0.f) &&
				(_31 == 0.f) &&
				(_32 == 0.f) &&
				(_34 == 0.f) &&
				(_41 == 0.f) &&
				(_42 == 0.f) &&
				(_43 == 0.f);
		}

		static Matrix4 Translation(const Vector3& d)
		{
			Matrix4 translation = Identity;
			translation._14 = d.x;
			translation._24 = d.y;
			translation._34 = d.z;
			return translation;
		}

		/*
			convert radian to degree
		*/
		static float rad2deg(float rad)
		{
			return rad * (180.f / M_PI);
		}

		static Matrix4 RotationX(float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			Matrix4 rotX = Identity;
			rotX._22 = cos; rotX._23 = -sin;
			rotX._32 = sin; rotX._33 = cos;
			return rotX;
		}

		static Matrix4 RotationY(float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			Matrix4 rotY = Identity;
			rotY._11 = cos; rotY._13 = sin;
			rotY._31 = -sin; rotY._33 = cos;
			return rotY;
		}

		static Matrix4 RotationZ(float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			Matrix4 rotZ = Identity;
			rotZ._11 = cos; rotZ._12 = -sin;
			rotZ._21 = sin; rotZ._22 = cos;
			return rotZ;
		}

		static Matrix4 RotationAxis(const Vector3& axis, float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			const float oneMinusCos = (1 - cos);
			Matrix4 rot = Identity;
			rot._11 = oneMinusCos + cos; rot._12 = oneMinusCos - sin; rot._13 = oneMinusCos + sin;
			rot._21 = oneMinusCos + sin; rot._22 = oneMinusCos + cos; rot._23 = oneMinusCos - sin;
			rot._31 = oneMinusCos - sin; rot._32 = oneMinusCos + sin; rot._33 = oneMinusCos + cos;
			return rot;
		}

		static Matrix4 Scaling(float scale)
		{
			// scaling diagonal
			Matrix4 sca = Identity;
			sca._11 *= scale;
			sca._22 *= scale;
			sca._33 *= scale;
			sca._44 *= scale;
			return sca;
		}
	};
}