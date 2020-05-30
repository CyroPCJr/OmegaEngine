#pragma once


namespace Omega::Math
{
	struct Plane
	{
		Vector3 n = Vector3::YAxis;
		float d = 0.0f;
	};
}