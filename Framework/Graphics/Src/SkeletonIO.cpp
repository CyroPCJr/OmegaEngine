#include "Precompiled.h"
#include "SkeletonIO.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

namespace
{
	void WriteMatrix(FILE* file, const Matrix4& m)
	{
		const Vector3 vec3 = GetTranslation(m);
		fprintf_s(file, "%f %f %f %f\n", m._11, m._12, m._13, m._14);
		fprintf_s(file, "%f %f %f %f\n", m._21, m._22, m._23, m._24);
		fprintf_s(file, "%f %f %f %f\n", m._31, m._32, m._33, m._34);
		fprintf_s(file, "%f %f %f %f\n", vec3.x, vec3.y, vec3.z, 1.0f);
	}

	void ReadMatrix(FILE* file, Matrix4& m)
	{
		fscanf_s(file, "%f %f %f %f\n", &m._11, &m._12, &m._13, &m._14);
		fscanf_s(file, "%f %f %f %f\n", &m._21, &m._22, &m._23, &m._24);
		fscanf_s(file, "%f %f %f %f\n", &m._31, &m._32, &m._33, &m._34);
		fscanf_s(file, "%f %f %f %f\n", &m._41, &m._42, &m._43, &m._44);
	}

}

void SkeletonIO::Write(FILE* file, const Skeleton& skeleton)
{
	// Homeworkd
	uint32_t skeletonCount = static_cast<uint32_t>(skeleton.bones.size());
	fprintf_s(file, "SkeletonCount: %d\n", skeletonCount);
	for (size_t i = 0; i < skeletonCount; ++i)
	{
	}
}

void SkeletonIO::Read(FILE* file, Skeleton& skeleton)
{
	// Homeworkd
}