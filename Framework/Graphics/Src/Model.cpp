#include "Precompiled.h"
#include "Model.h"

#include "MeshIO.h"
#include "SkeletonIO.h"

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

	// For homework, save out model.materialData as well ...
	// if diffuseMapName is empty  string, write <none>
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
		char name[20];
		fscanf_s(file, "DiffuseMapName %s\n", &name, sizeof(name));
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
	// Homework:
	// Do loading
	// Resolve link here

}

void Model::Initialize(const std::filesystem::path& fileName)
{
	ModelLoader::LoadModel(fileName, *this);
	ModelLoader::LoadSkeleton(fileName, skeleton);
}

void Model::Terminate()
{
	for (auto& data : meshData)
	{
		data.meshBuffer.Terminate();
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