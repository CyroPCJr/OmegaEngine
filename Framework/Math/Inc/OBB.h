#pragma once

namespace Omega::Math
{
	struct OBB
	{
		Quaternion rot = Quaternion::Identity;  // Rotation
		Vector3 center = Vector3::Zero;			// Translation
		Vector3 extend = Vector3::One;			// Scale
	};
}