#include "Precompiled.h"
#include "SkeletonIO.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

namespace
{
	void WriteMatrix(FILE* file, const Matrix4& m)
	{
		fprintf_s(file, "%f %f %f %f\n", m._11, m._12, m._13, m._14);
		fprintf_s(file, "%f %f %f %f\n", m._21, m._22, m._23, m._24);
		fprintf_s(file, "%f %f %f %f\n", m._31, m._32, m._33, m._34);
		fprintf_s(file, "%f %f %f %f\n", m._41, m._42, m._43, m._44);
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
	const uint32_t skeletonCount = static_cast<uint32_t>(skeleton.bones.size());
	fprintf_s(file, "BonesCount: %d\n", skeletonCount);
	for (auto& bone : skeleton.bones)
	{
		fprintf_s(file, "%s\n", bone->name.c_str());
		fprintf_s(file, "Index: %d\n", bone->index);
		fprintf_s(file, "Parent Index: %d\n", bone->parentIndex);
		WriteMatrix(file, bone->toParentTransform);
		fprintf_s(file, "ChildCount: %d\n", bone->children.size());
		for (auto& child : bone->children)
		{
			fprintf_s(file, "Child index: %d\n", child->index);
		}
	}
}

void SkeletonIO::Read(FILE* file, Skeleton& skeleton)
{
	uint32_t skeletonCount = static_cast<uint32_t>(skeleton.bones.size());
	for (size_t i = 0; i < skeletonCount; ++i)
	{
		auto bone = std::make_unique<Bone>();
		char name[128];
		fscanf_s(file, "%s\n", &name, sizeof(name));
		bone->name = name;
		fscanf_s(file, "Index: %d\n", &bone->index);
		fscanf_s(file, "Parent Index: %d\n", &bone->parentIndex);
		ReadMatrix(file, bone->toParentTransform);
		uint32_t childCount = 0;
		fscanf_s(file, "ChildCount: %d\n", &childCount);
		for (uint32_t i = 0; i < childCount; ++i)
		{
			uint32_t idx = 0;
			fscanf_s(file, "Child index: %d\n", &idx);
			bone->childIndices.push_back(idx);
		}
		skeleton.bones[i] = std::move(bone);
	}
}