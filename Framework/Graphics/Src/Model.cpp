#include "Precompiled.h"
#include "Model.h"

#include "MeshIO.h"
#include "SkeletonIO.h"
#include "AnimationIO.h"

using namespace Omega::Graphics;

void ModelLoader::LoadModel(std::filesystem::path fileName, Model& model)
{
	fileName.replace_extension("model");

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	uint32_t numMeshes = 0;
	fscanf_s(file, "MeshCount: %d\n", &numMeshes);

	model.meshData.resize(numMeshes);
	for (uint32_t i = 0; i < numMeshes; ++i)
	{
		fscanf_s(file, "MaterialIndex: %d\n", &model.meshData[i].materialIndex);
		MeshIO::Read(file, model.meshData[i].mesh);
	}

	fclose(file);

	fileName.replace_extension("materialData");
	fopen_s(&file, fileName.u8string().c_str(), "r");

	uint32_t numMaterial = 0;
	fscanf_s(file, "MaterialCount: %d\n", &numMaterial);

	model.materialData.resize(numMaterial);

	for (uint32_t i = 0; i < numMaterial; ++i)
	{
		// Reference:
		// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c4473?view=vs-2019
		char name[128]{};
		fscanf_s(file, "DiffuseMapName %s\n", &name, static_cast<uint32_t>(sizeof(name)));
		model.materialData[i].diffuseMapName = name;
		MeshIO::Read(file, model.materialData[i].material);
	}

	fclose(file);

	for (auto& data : model.meshData)
	{
		data.meshBuffer.Initialize(data.mesh);
	}

	for (auto& data : model.materialData)
	{
		if (!data.diffuseMapName.empty())
		{
			std::string fullFileName = fileName.u8string().c_str();
			fullFileName = fullFileName.substr(0, fullFileName.rfind('/') + 1);
			data.diffuseMap = std::make_unique<Texture>();
			data.diffuseMap->Initialize(fullFileName + data.diffuseMapName);
		}
	}
}

void ModelLoader::LoadSkeleton(std::filesystem::path fileName, Skeleton& skeleton)
{
	fileName.replace_extension("skeleton");
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	uint32_t numBones = 0;
	fscanf_s(file, "BonesCount: %d\n", &numBones);
	skeleton.bones.resize(numBones);
	SkeletonIO::Read(file, skeleton);
	fclose(file);
	for (auto& bone : skeleton.bones)
	{
		if (bone->parentIndex != -1)
		{
			bone->parent = skeleton.bones[bone->parentIndex].get();
		}
		else
		{
			skeleton.root = bone.get();
		}
		bone->children.reserve(bone->childIndices.size());
		for (int childIndex : bone->childIndices)
		{
			bone->children.push_back(skeleton.bones[childIndex].get());
		}
	}

}

void ModelLoader::LoadAnimationSet(std::filesystem::path fileName, AnimationSet& animationSet)
{
	fileName.replace_extension("animset");

	FILE* file = nullptr;
	int fileErr = fopen_s(&file, fileName.u8string().c_str(), "r");
	OMEGAASSERT(fileErr == 0, "[Model] File not found.");

	uint32_t numClipCount = 0;

	fscanf_s(file, "ClipCount: %d\n", &numClipCount);
	animationSet.clips.resize(numClipCount);

	for (uint32_t i = 0; i < numClipCount; ++i)
	{
		auto clip = std::make_unique<AnimationClip>();
		char name[20];
		fscanf_s(file, "Name: %s\n", &name, static_cast<uint32_t>(sizeof(name)));
		clip->name = name;
		fscanf_s(file, "Duration: %f\n", &clip->duration);
		fscanf_s(file, "TickPerSecond: %f\n", &clip->tickPerSecond);
		animationSet.clips[i] = std::move(clip);
		AnimationIO::Read(file, *animationSet.clips[i]);
	}

	fclose(file);
}

void Model::Initialize(const std::filesystem::path& fileName)
{
	ModelLoader::LoadModel(fileName, *this);
	ModelLoader::LoadSkeleton(fileName, skeleton);
	ModelLoader::LoadAnimationSet(fileName, animationSet);
}

void Model::Terminate()
{
	for (auto& data : meshData)
	{
		data.meshBuffer.Terminate();
	}

	for (auto& material : materialData)
	{
		material.diffuseMap->Terminate();
	}
}

void Model::Draw() const
{
	for (size_t i = 0; i < meshData.size(); ++i)
	{
		auto& data = meshData[i];
		materialData[data.materialIndex].diffuseMap->BindVS();
		materialData[data.materialIndex].diffuseMap->BindPS();
		data.meshBuffer.Draw();
	}

}