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
	//for (uint32_t i = 0; i < skeletonCount; ++i)
	//{
	//	fprintf_s(file, "%s\n", skeleton.bones[i]->name.c_str());
	//	fprintf_s(file, "Index: %d\n", skeleton.bones[i]->index);
	//	Matrix4 matTransform = skeleton.bones[i]->toParentTransform;
	//	WriteMatrix(file, matTransform);
	//	Bone* bone = skeleton.bones[i]->parent;
	//	while (bone && bone->parent)
	//	{
	//		//TODO: continuar daqui
	//		fprintf_s(file, "%s\n", bone->name.c_str());
	//		fprintf_s(file, "Index: %d\n", bone->index);
	//		WriteMatrix(file, bone->toParentTransform);
	//		bone = skeleton.bones[i]->parent->parent;
	//	}
	//}
	//TODO: testar isso aqui
	for (auto& bone : skeleton.bones)
	{
		fprintf_s(file, "%s\n", bone->name.c_str());
		fprintf_s(file, "Index: %d\n", bone->index);
		WriteMatrix(file, bone->toParentTransform);
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
		fscanf_s(file, "Index: %d\n", &bone->index);
		ReadMatrix(file, bone->toParentTransform);
		skeleton.bones[i] = std::move(bone);
	}
}