#pragma once
// reference: https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4201?view=msvc-170
#pragma warning(disable : 4201)

namespace Omega::Math
{
	struct Vector3;
	struct Quaternion;

	struct Matrix4
	{
		union
		{
			struct // row + collum subscripts
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			std::array<float, 16> v;
		};

		const static Matrix4 Identity;
		const static Matrix4 Zero;

		static Matrix4 RotationAxis(const Vector3& axis, float rad);
		static Matrix4 RotationQuaternion(const Quaternion& q) noexcept;
		static Matrix4 Transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept;

#pragma region operator overload

		//constexpr Matrix4& operator=(const Matrix4& m)
		//{
		//	_11 = m._11;
		//	_12 = m._12;
		//	_13 = m._13;
		//	_14 = m._14;

		//	_21 = m._21;
		//	_22 = m._22;
		//	_23 = m._23;
		//	_24 = m._24;

		//	_31 = m._31;
		//	_32 = m._32;
		//	_33 = m._33;
		//	_34 = m._34;

		//	_41 = m._41;
		//	_42 = m._42;
		//	_43 = m._43;
		//	_44 = m._44;
		//	return *this;
		//}

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

		constexpr Matrix4 operator*(const Matrix4& m) noexcept
		{
			Matrix4 aux{};
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

		constexpr Matrix4 operator*=(const Matrix4& m) noexcept
		{
			Matrix4 aux{};
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

		constexpr Matrix4 operator*(const float p)
		{
			_11 *= p; _12 *= p; _13 *= p; _14 *= p;
			_21 *= p; _22 *= p; _23 *= p; _24 *= p;
			_31 *= p; _32 *= p; _33 *= p; _34 *= p;
			_41 *= p; _42 *= p; _43 *= p; _44 *= p;
			return *this;
		}

		constexpr Matrix4 operator+(const Matrix4& m) noexcept
		{
			Matrix4 aux{};
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

		constexpr Matrix4 operator-(const Matrix4& m) noexcept
		{
			Matrix4 aux{};
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

		constexpr Matrix4 Adjoint(const Matrix4& m)
		{
			return	{
				(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
				-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
				(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
				-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

				-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
				(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
				-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
				(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

				(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
				-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
				(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
				-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

				-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
				(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
				-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
				(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
			};
		}

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

		static constexpr Matrix4 Translation(const Vector3& d) noexcept
		{
			Matrix4 translation = Identity;
			translation._41 = d.x;
			translation._42 = d.y;
			translation._43 = d.z;
			return translation;
		}

		static Matrix4 RotationX(float radian) noexcept
		{
			const float cos = cosf(radian);
			const float sin = sinf(radian);
			Matrix4 rotX = Identity;
			rotX._22 = cos; rotX._23 = sin;
			rotX._32 = -sin; rotX._33 = cos;
			return rotX;
		}

		static Matrix4 RotationY(float radian) noexcept
		{
			const float cos = cosf(radian);
			const float sin = sinf(radian);
			Matrix4 rotY = Identity;
			rotY._11 = cos; rotY._13 = -sin;
			rotY._31 = sin; rotY._33 = cos;
			return rotY;
		}

		static Matrix4 RotationZ(float radian) noexcept
		{
			const float cos = cosf(radian);
			const float sin = sinf(radian);
			Matrix4 rotZ = Identity;
			rotZ._11 = cos; rotZ._12 = sin;
			rotZ._21 = -sin; rotZ._22 = cos;
			return rotZ;
		}

		static constexpr Matrix4 Scaling(float scale) noexcept
		{
			// scaling diagonal
			Matrix4 sca = Identity;
			sca._11 *= scale;
			sca._22 *= scale;
			sca._33 *= scale;
			return sca;
		}

		static constexpr Matrix4 Scaling(const Vector3& v) noexcept
		{
			Matrix4 m = Identity;
			m._11 *= v.x;
			m._22 *= v.y;
			m._33 *= v.z;
			return m;
		}

	};
}