#include "Precompiled.h"
#include "MetaRegistration.h"

#include "Constants.h"

using namespace Omega::Math;

namespace Omega::Core::Meta
{
	template<>
	void Deserialize<Vector2>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			auto object = value.GetObjectW();
			auto vec2 = static_cast<Vector2*>(instance);
			vec2->x = object.FindMember("x")->value.GetFloat();
			vec2->y = object.FindMember("y")->value.GetFloat();
		}
	}

	template<>
	void Deserialize<Vector3>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			auto object = value.GetObjectW();
			auto vec3 = static_cast<Vector3*>(instance);
			vec3->x = object.FindMember("x")->value.GetFloat();
			vec3->y = object.FindMember("y")->value.GetFloat();
			vec3->z = object.FindMember("z")->value.GetFloat();
		}
	}

	template<>
	void Deserialize<Vector4>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			auto object = value.GetObjectW();
			auto vec4 = static_cast<Vector4*>(instance);
			vec4->x = object.FindMember("x")->value.GetFloat();
			vec4->y = object.FindMember("y")->value.GetFloat();
			vec4->z = object.FindMember("z")->value.GetFloat();
			vec4->w = object.FindMember("w")->value.GetFloat();
		}
	}

	template<>
	void Deserialize<Quaternion>(void* instance, const rapidjson::Value& value)
	{
		if (instance)
		{
			const auto object = value.GetObjectW();
			const float eulerX = object.FindMember("XDegree")->value.GetFloat();
			const float eulerY = object.FindMember("YDegree")->value.GetFloat();
			const float eulerZ = object.FindMember("ZDegree")->value.GetFloat();

			auto quat = static_cast<Quaternion*>(instance);

			*quat = Quaternion::RotationAxis(Vector3::XAxis, eulerX * Constants::DegToRad) *
				Quaternion::RotationAxis(Vector3::YAxis, eulerY * Constants::DegToRad) *
				Quaternion::RotationAxis(Vector3::ZAxis, eulerZ * Constants::DegToRad);
		}
	}
}

META_TYPE_DEFINE(Vector2, Vector2);
META_TYPE_DEFINE(Vector3, Vector3);
META_TYPE_DEFINE(Vector4, Vector4);
META_TYPE_DEFINE(Quaternion, Quaternion);

void Omega::Math::StaticMetaRegister() noexcept
{
	// Add MetaClass registration here...
	// e.g. META_REGISTER(Foo);
}